#include "gameboardvm.h"
#include "clientmanager.h"

GameBoardVM::GameBoardVM(QObject *parent)
    : QAbstractListModel{parent}
{
    setBoard(ClientManager::instance().board());
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

    return QVariant::fromValue(m_board->tiles({index.row(), index.column()}));
}

void GameBoardVM::setBoard(const GameBoard *newBoard)
{
    beginResetModel();

    if(m_board && m_signalConnected)
        m_board->disconnect(this);

    m_board = newBoard;

    connect(m_board, &GameBoard::dataChanged, this, [=](const Game::Position &from, const Game::Position &to){
        emit dataChanged(createIndex(from.row, from.column), createIndex(to.row, to.column), {Qt::DisplayRole});
    });

    m_signalConnected = true;

    endResetModel();
}
