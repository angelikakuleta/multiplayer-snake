#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QObject>
#include <game.h>

using Tile = Game::Tile;
using Position = Game::Position;

class GameBoard : public QObject
{
    Q_OBJECT
public:
    explicit GameBoard(QObject *parent = nullptr);

    uint rows() const { return m_rows; }
    uint columns() const { return m_columns; }

    void clear();
    void generateFood();
    Position generatePlayer(const Tile &tile);

    const Tile &tile(const Position &pos) const;
    void setTile(const Position &pos, const Tile &tile);

    const std::vector<Tile> &tiles() const { return m_tiles; }

private:
    const uint m_rows;
    const uint m_columns;
    std::vector<Tile> m_tiles;
    uint m_food;
};

#endif // GAMEBOARD_H
