#include "playerlistvm.h"
#include <clientmanager.h>

PlayerListVM::PlayerListVM(QObject *parent)
    : QAbstractListModel{parent}
{
    setPlayers(&ClientManager::instance().players());
    connect(&ClientManager::instance(), SIGNAL(playersChanged()),
            this, SLOT(onModelChanged()));

//    connect(&ClientManager::instance(),&ClientManager::playersChanged, this, [=](){
//        const int index = m_players->size();
//        emit dataChanged(QModelIndex(), createIndex(index-1, 0));
//    });
}

int PlayerListVM::rowCount(const QModelIndex&) const
{
    return m_players->size();
}

QVariant PlayerListVM::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= (int)m_players->size())
            return QVariant();

    auto &player = m_players->at(index.row());
    if (role == ClientIdRole)
        return player->clinetId();
    if (role == IsReadyRole)
        return player->isReady();
    if (role == ScoreRole)
        return player->score();
    if (role == TileRole)
        return QVariant::fromValue(player->tile());
    return QVariant();
}

QHash<int, QByteArray> PlayerListVM::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ClientIdRole] = "clientId";
    roles[IsReadyRole] = "isReady";
    roles[ScoreRole] = "score";
    roles[TileRole] = "tile";
    return roles;
}

bool PlayerListVM::isRoomMaster(qint16 clientId)
{
    if (m_players->size() == 0) return false;
    return m_players->at(0)->clinetId() == clientId;
}

void PlayerListVM::setPlayers(const std::vector<Player*> *newPlayers)
{
    beginResetModel();
    m_players = newPlayers;
    endResetModel();
}

void PlayerListVM::onModelChanged()
{
    setPlayers(&ClientManager::instance().players());
}
