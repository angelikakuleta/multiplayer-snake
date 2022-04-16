#ifndef GAMEBOARDVM_H
#define GAMEBOARDVM_H

#include <qqml.h>
#include <QAbstractListModel>
#include <gameboard.h>

class GameBoardVM : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit GameBoardVM(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setBoard(const GameBoard *newBoard);

private:
    const GameBoard *m_board;
    bool m_signalConnected;
};

#endif // GAMEBOARDVM_H
