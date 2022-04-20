#ifndef PLAYERLISTVM_H
#define PLAYERLISTVM_H

#include <QAbstractListModel>
#include <QObject>
#include <player.h>

class PlayerListVM : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit PlayerListVM(QObject *parent = nullptr);

    enum PLayerRole {
        ClientIdRole,
        IsReadyRole,
        ScoreRole,
        TileRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE bool isRoomMaster(qint16 clientId);

    void setPlayers(const std::vector<Player *> *newPlayers) ;

public slots:
    void onModelChanged();

private:
    const std::vector<Player*> *m_players;
};

#endif // PLAYERLISTVM_H
