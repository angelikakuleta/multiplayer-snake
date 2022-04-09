#include "gameboardvm.h"

GameBoardVM::GameBoardVM(const GameBoard *board, QObject *parent)
    : QAbstractListModel{parent}
    , m_board(board)
{
    connect(m_board, &GameBoard::dataChanged, this, [=](const GameBoard::Pos &from, const GameBoard::Pos &to){
        emit dataChanged(createIndex(from.row, from.column), createIndex(to.row, to.column), {Qt::DisplayRole});
    });
}

int GameBoardVM::rowCount(const QModelIndex&) const
{
    return m_board->rows();
}

int GameBoardVM::columnCount(const QModelIndex&) const
{
    return m_board->columns();
}

QModelIndex GameBoardVM::index(int row, int column, const QModelIndex &) const
{
    return createIndex(row, column);
}

QVariant GameBoardVM::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= this->rowCount())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    return QVariant::fromValue(m_board->tiles({
                static_cast<uint>(index.row()),
                static_cast<uint>(index.column())
            }));
}
