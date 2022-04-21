#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QObject>
#include <vector>
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
    const std::vector<Tile> *tiles() const { return &m_tiles; }
    Tile tiles(const Position &pos) const;
    Tile tiles(int index) const;
    void setTile(const Position &pos, Tile tile);
    void setTile(int index, Tile tile);
    void clear();

signals:
    void dataChanged(const Position &from, const Position &to);

private:
    const uint m_rows;
    const uint m_columns;
    std::vector<Tile> m_tiles;

    int posToIndex(const Position &pos) const;
    Position indexToPos(uint index) const;
};

#endif // GAMEBOARD_H
