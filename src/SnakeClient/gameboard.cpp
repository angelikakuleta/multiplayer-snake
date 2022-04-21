#include "gameboard.h"
#include <QDebug>

GameBoard::GameBoard(QObject *parent)
    : QObject{parent}
    , m_rows(Game::boardRows())
    , m_columns(Game::boardColumns())
    , m_tiles(m_rows*m_columns, Tile::Empty)
{
    // to remove
    m_tiles.at(0) = Tile::Snake1;
    m_tiles.at(m_rows * m_columns / 3) = Tile::Food;
}

Tile GameBoard::tiles(const Position &pos) const
{
    try {
        return m_tiles.at(posToIndex(pos));
    } catch (std::out_of_range&) {;
        return Tile::Empty;
    }
}

void GameBoard::setTile(const Position &pos, Tile tile)
{
    try {
        m_tiles.at(posToIndex(pos)) = tile;
        emit dataChanged(pos, pos);
    } catch (std::out_of_range& err) {
        qDebug() << err.what();
    }
}

void GameBoard::clear()
{
    for (std::size_t i = 0; i < m_tiles.size(); i++) {
        m_tiles.at(i) = Tile::Empty;
    }

    emit dataChanged({0,0}, {(int)m_rows - 1, (int)m_columns - 1});
}

int GameBoard::posToIndex(const Position &pos) const
{
    return pos.row * m_columns + pos.column;
}
