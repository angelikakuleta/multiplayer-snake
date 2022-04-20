#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QObject>
#include <vector>
#include <game.h>

using Tile = Game::Tile;

class GameBoard : public QObject
{
    Q_OBJECT
public:
    struct Pos { uint row, column; };

    explicit GameBoard(QObject *parent = nullptr);

    uint rows() const { return m_rows; }
    uint columns() const { return m_columns; }
    const std::vector<Tile> *tiles() const { return &m_tiles; }
    Tile tiles(const Pos &pos) const;
    void setTile(const Pos &pos, Tile tile);
    void clear();

signals:
    void dataChanged(const GameBoard::Pos &from, const GameBoard::Pos &to);

private:
    const uint m_rows;
    const uint m_columns;
    std::vector<Tile> m_tiles;

    int posToIndex(const Pos &pos) const;
};

#endif // GAMEBOARD_H
