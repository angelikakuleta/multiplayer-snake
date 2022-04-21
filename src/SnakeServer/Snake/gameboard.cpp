#include "gameboard.h"

GameBoard::GameBoard(QObject *parent)
    : QObject{parent}
    , m_rows(Game::boardRows())
    , m_columns(Game::boardColumns())
    , m_tiles(m_rows*m_columns, Tile::Empty)
    , m_food(0)
{
}

void GameBoard::clear()
{
    for (std::size_t i = 0; i < m_tiles.size(); i++) {
        m_tiles.at(i) = Tile::Empty;
    }
}

void GameBoard::generateFood()
{
    do {
        int row = rand() % rows();
        int column = rand() % columns();
        if (tile({row, column}) == Tile::Empty) {
            setTile({row, column}, Tile::Food);
            return;
        }
    } while (true);
    m_food++;
}

Position GameBoard::generatePlayer(const Tile &tile)
{
    do {
        int row = rand() % rows();
        int column = rand() % columns();
        if (this->tile({row, column}) == Tile::Empty) {
            setTile({row, column}, tile);
            return {row, column};
        }
    } while (true);
}

const Tile &GameBoard::tile(const Position &pos) const
{
    return m_tiles[pos.row * m_columns + pos.column];
}

void GameBoard::setTile( const Position &pos, const Tile &tile)
{
    m_tiles[pos.row * m_columns + pos.column] = tile;
}
