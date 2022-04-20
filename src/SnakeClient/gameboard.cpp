#include "gameboard.h"
#include <QDebug>

const int BOARD_ROWS = 32;
const int BOARD_COLUMNS = 40;

GameBoard::GameBoard(QObject *parent)
    : QObject{parent}
    , m_rows(BOARD_ROWS)
    , m_columns(BOARD_COLUMNS)
    , m_tiles(m_rows*m_columns, Tile::Empty)
{
    // to remove
    m_tiles.at(0) = Tile::Snake1;
    m_tiles.at(BOARD_ROWS * BOARD_COLUMNS / 3) = Tile::Food;
}

Tile GameBoard::tiles(const Pos &pos) const
{
    try {
        return m_tiles.at(posToIndex(pos));
    } catch (std::out_of_range&) {;
        return Tile::Empty;
    }
}

void GameBoard::setTile(const Pos &pos, Tile tile)
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

    emit dataChanged({0,0}, {m_rows - 1, m_columns - 1});
}

int GameBoard::posToIndex(const Pos &pos) const
{
    return pos.row * m_columns + pos.column;
}
