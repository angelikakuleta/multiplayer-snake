#include "gameboard.h"
#include <QDebug>

GameBoard::GameBoard(QObject *parent)
    : QObject{parent}
    , m_rows(Game::boardRows())
    , m_columns(Game::boardColumns())
    , m_tiles(m_rows*m_columns, Tile::Empty)
{
}

Tile GameBoard::tiles(const Position &pos) const
{
    try {
        return m_tiles.at(posToIndex(pos));
    } catch (std::out_of_range&) {;
        return Tile::Empty;
                                 }
}

Tile GameBoard::tiles(int index) const
{
    return m_tiles.at(index);
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

void GameBoard::setTile(int index, Tile tile)
{
    try {
        m_tiles.at(index) = tile;
        auto pos = indexToPos(index);
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

Position GameBoard::indexToPos(uint index) const
{
    return {(int)(index / m_columns), (int)(index % m_columns)};
}
