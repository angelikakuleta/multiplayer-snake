#include "gamemanager.h"

using ClientCmd = Contract::ClientCmd;
using ServerCmd = Contract::ServerCmd;

GameManager::GameManager(QObject *parent)
    : QObject{parent}
{
    m_socketServer = new SocketServer(this);
    m_messageParser = new MessageParser(this);
    connect(m_socketServer, SIGNAL(clientConnected(qint16)),
            this, SLOT(onClientConnected(qint16)));
    connect(m_socketServer, SIGNAL(clientDisconnected(qint16)),
            this, SLOT(onClientDisconnected(qint16)));
    connect(m_socketServer, SIGNAL(newMessageReceived(QByteArray)),
            this, SLOT(onNewMessageReceived(QByteArray)));
}

GameManager::~GameManager()
{
    m_socketServer->deleteLater();
    m_messageParser->deleteLater();
}

void GameManager::createRoomRequest(qint16 clientId)
{
    if (findRoomByClient(clientId) != -1) return;
    utils::findAndRemove(m_clientInLobby, clientId);

    qint16 roomId;
    do {
        roomId = rand() % 8999 + 1000;
    } while (m_rooms.find(roomId) != m_rooms.end());

    GameRoom* newGameRoom = new GameRoom(roomId, this);
    m_rooms[roomId] = newGameRoom;

    QList<QByteArray> params;
    params.append(QByteArray::number(roomId));
    auto message = m_messageParser->buildMessage(ServerCmd::CreateRoomResponse, params);
    m_socketServer->sendMessageToClient(message, clientId);

    newGameRoom->addClient(clientId);
    readyListUpdated(roomId);
    roomListUpdated();
}

void GameManager::joinRoomRequest(qint16 clientId, qint16 roomId)
{
    QList<QByteArray> params;
    ServerCmd command = ServerCmd::JoinRoomErrResponse;

    if (findRoomByClient(clientId) != -1) return;

    if (m_rooms.find(roomId) == m_rooms.end())
    {
        params.append(QByteArray("Room was not found"));
    } else if (!m_rooms[roomId]->isOpen()) {
        params.append(QByteArray("Room is no longer open"));
    } else {
        command = ServerCmd::JoinRoomResponse;
        utils::findAndRemove(m_clientInLobby, clientId);
        m_rooms[roomId]->addClient(clientId);
        params.append(QByteArray::number(roomId));
    }

    auto message = m_messageParser->buildMessage(command, params);
    m_socketServer->sendMessageToClient(message, clientId);

    readyListUpdated(roomId);
    roomListUpdated();
}

void GameManager::leaveRoomRequest(qint16 clientId, qint16 roomId)
{
    if (m_rooms.find(roomId) == m_rooms.end()) return;
    m_rooms[roomId]->removeClient(clientId);
    m_clientInLobby.push_back(clientId);

    if (m_rooms[roomId]->clients().size() > 0)
        readyListUpdated(roomId);
    else
        m_rooms.erase(roomId);

    roomListUpdated();
}

void GameManager::readyToPlayRequest(qint16 clientId, qint16 roomId)
{
    if (m_rooms.find(roomId) == m_rooms.end()) return;
    m_rooms[roomId]->readyToPlay(clientId);

    readyListUpdated(roomId);
    roomListUpdated();
}

void GameManager::startGameRequest(qint16 clientId, qint16 roomId)
{
    if (m_rooms.find(roomId) == m_rooms.end()) return;

    if (*m_rooms[roomId]->clients().begin() != clientId) return;
    m_rooms[roomId]->startGame();

    roomListUpdated();
}

void GameManager::changeDirectionRequest(qint16 clientId, qint16 roomId, GameEngine::Direction direction)
{
    if (m_rooms.find(roomId) == m_rooms.end()) return;
    m_rooms[roomId]->game()->changeDirection(clientId, direction);
}

void GameManager::onClientConnected(qint16 clientId)
{
    m_clientInLobby.push_back(clientId);

    QList<QByteArray> params;
    params.append(QByteArray::number(clientId));
    auto message = m_messageParser->buildMessage(ServerCmd::ClientIdRegistered, params);

    m_socketServer->sendMessageToClient(message, clientId);
    roomListUpdated();
}

void GameManager::onClientDisconnected(qint16 clientId)
{
    utils::findAndRemove(m_clientInLobby, clientId);
    if (auto roomId = findRoomByClient(clientId)) {
        m_rooms[roomId]->removeClient(clientId);

        if (m_rooms[roomId]->clients().size() > 0)
            readyListUpdated(roomId);
        else
            m_rooms.erase(roomId);

        roomListUpdated();
    }
}

void GameManager::onNewMessageReceived(QByteArray message)
{
    Contract::ClientCmd cmd;
    qint16 clientId;
    QList<QByteArray> params;

    bool isValid = false;

    isValid = m_messageParser->parseMessage(message, cmd, clientId, params);
    if (!isValid) return;

    qint16 roomId;
    if (cmd > ClientCmd::CreateRoom) {
        if (params.length() == 0) return;
        roomId = params.first().toInt(&isValid);
        if (!isValid) return;
    }

    switch (cmd) {
    case ClientCmd::CreateRoom:
        createRoomRequest(clientId);
        break;
    case ClientCmd::JoinRoom:
        joinRoomRequest(clientId, roomId);
        break;
    case ClientCmd::LeaveRoom:
        leaveRoomRequest(clientId, roomId);
        break;
    case ClientCmd::ReadyToPlay:
        readyToPlayRequest(clientId, roomId);
        break;
    case ClientCmd::StartGame:
        startGameRequest(clientId, roomId);
        break;
    case ClientCmd::ChangeDirection:
        params.pop_back();
        GameEngine::Direction direction = (GameEngine::Direction)params.first().toInt(&isValid);
        if (!isValid) return;
        changeDirectionRequest(clientId, roomId, direction);
        break;
    }
}

void GameManager::roomListUpdated()
{
    std::vector<qint16> openRooms;
    for (const auto &room : m_rooms) {
        if (room.second->isOpen())
            openRooms.push_back(room.first);
    }

    QList<QByteArray> params;
    params.append(QByteArray::fromStdString(
                      utils::join(openRooms, ",")));
    auto message = m_messageParser->buildMessage(ServerCmd::RoomListUpdated, params);
    m_socketServer->sendMessageToMultipleClients(message, m_clientInLobby);
}

void GameManager::readyListUpdated(qint16 roomId)
{
    if (m_rooms.find(roomId) == m_rooms.end()) return;

    auto &existingRoom = m_rooms[roomId];
    QList<QByteArray> params;
    params.append(QByteArray::fromStdString(
                      utils::join(existingRoom->clients(), ",")));
    params.append(QByteArray::fromStdString(
                      utils::join(existingRoom->readyClients(), ",")));
    auto message = m_messageParser->buildMessage(ServerCmd::ReadyListUpdated, params);
    m_socketServer->sendMessageToMultipleClients(message, existingRoom->clients());
}

qint16 GameManager::findRoomByClient(qint16 clientId)
{
    for (const auto &room : m_rooms) {
        if (utils::contain(room.second->clients(), clientId)) {
            return room.first;
        }
    }
    return -1;
}
