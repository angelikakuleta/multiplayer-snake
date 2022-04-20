#include "clientmanager.h"

using ClientCmd = Contract::ClientCmd;
using ServerCmd = Contract::ServerCmd;

ClientManager::ClientManager(QObject *parent)
    : QObject{parent}
    , m_roomId(-1)
    , m_direction(Direction::None)
{
    m_client = new SocketClient(this);
    m_messageParser = new MessageParser(this);
    m_board = new GameBoard(this);

    connect(m_client, SIGNAL(newMessageReceived(QByteArray)),
            this, SLOT(onNewMessageReceived(QByteArray)));
}

void ClientManager::setDirection(const Direction &direction)
{
    if (m_direction == direction) return;

    m_direction = direction;

    QList<QByteArray> params;
    params.append(QByteArray::number(direction));
    auto message = m_messageParser->buildMessage(ClientCmd::ChangeDirection, m_client->clientId(), params);
    m_client->sendMessage(message);
}

ClientManager::~ClientManager()
{
    m_client->deleteLater();
    m_board->deleteLater();
}

void ClientManager::createRoomRequest()
{
    auto message = m_messageParser->buildMessage(ClientCmd::CreateRoom, m_client->clientId(), std::nullopt);
    m_client->sendMessage(message);
}

void ClientManager::joinRoomRequest(qint16 roomId)
{
    QList<QByteArray> params;
    params.append(QByteArray::number(roomId));
    auto message = m_messageParser->buildMessage(ClientCmd::JoinRoom, m_client->clientId(), params);
    m_client->sendMessage(message);
}

void ClientManager::leaveRoomRequest()
{
    QList<QByteArray> params;
    params.append(QByteArray::number(m_roomId));
    auto message = m_messageParser->buildMessage(ClientCmd::LeaveRoom, m_client->clientId(), params);
    m_client->sendMessage(message);
}

void ClientManager::readyToPlayRequest()
{
    QList<QByteArray> params;
    params.append(QByteArray::number(m_roomId));
    auto message = m_messageParser->buildMessage(ClientCmd::ReadyToPlay, m_client->clientId(), params);
    m_client->sendMessage(message);
}

void ClientManager::startGameRequest()
{
    QList<QByteArray> params;
    params.append(QByteArray::number(m_roomId));
    auto message = m_messageParser->buildMessage(ClientCmd::StartGame, m_client->clientId(), params);
    m_client->sendMessage(message);
}

void ClientManager::onNewMessageReceived(QByteArray message)
{
    Contract::ServerCmd cmd;
    QList<QByteArray> params;

    bool isValid = false;

    isValid = m_messageParser->parseMessage(message, cmd, params);
    if (!isValid) return;

    qint16 roomId;

    switch (cmd) {
    case ServerCmd::ClientIdRegistered: {
        if (params.length() == 0) return;
        qint16 newClientId = params.first().toInt(&isValid);
        if (!isValid) return;
        m_client->setClientId(newClientId);
        emit connected();
        break;
    }
    case ServerCmd::CreateRoomResponse:
    case ServerCmd::JoinRoomResponse:
        if (params.length() == 0) return;
        roomId = params.first().toInt(&isValid);
        if (!isValid) return;
        m_roomId = roomId;
        emit enteredRoom();
        break;
    case ServerCmd::CreateRoomErrResponse:
    case ServerCmd::JoinRoomErrResponse:
        if (params.length() == 0) return;
        emit errorMessage(params.first());
        break;
    case ServerCmd::RoomListUpdated:
        if (params.length() == 0) return;
        m_openRooms.clear();
        for (auto &room : params.first().split(',')) {
            roomId = room.toInt(&isValid);
            if (isValid) m_openRooms.push_back(roomId);
        }
        emit openRoomsChanged();
        break;
    case ServerCmd::ReadyListUpdated: {
        if (params.length() < 2) return;

        for (auto p : m_players)
            delete p;
        m_players.clear();

        qint16 clientId;
        Player* pl;
        std::vector<qint16> clientList;
        std::vector<qint16> readyClientList;

        for (auto &client : params.first().split(',')) {
            clientId = client.toInt(&isValid);
            if (isValid) clientList.push_back(clientId);
        }
        params.pop_front();
        for (auto &readyClient : params.first().split(',')) {
            clientId = readyClient.toInt(&isValid);
            if (isValid) readyClientList.push_back(clientId);
        }

        auto tile = static_cast<short>(Tile::Snake1);
        for (auto &clientId : clientList) {
            pl = new Player(clientId, static_cast<Tile>(tile));
            if (std::find(readyClientList.begin(), readyClientList.end(), clientId) != readyClientList.end())
                pl->setIsReady(true);
            m_players.push_back(pl);
            ++tile;
        }

        emit playersChanged();
        break;
    }
    case ServerCmd::GameTick:
        break;
    case ServerCmd::GameWinner:
        break;
    }
}
