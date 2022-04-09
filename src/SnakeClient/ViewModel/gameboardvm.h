#ifndef GAMEBOARDVM_H
#define GAMEBOARDVM_H

#include <QObject>
#include <QAbstractListModel>
#include <gameboard.h>

class GameBoardVM : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit GameBoardVM(const GameBoard *board, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    const GameBoard *m_board;
};

#endif // GAMEBOARDVM_H
