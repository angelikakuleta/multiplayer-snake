#ifndef GAME_H
#define GAME_H

#include "SnakeCommon_global.h"
#include <QObject>

class SNAKECOMMON_EXPORT Game : public QObject
{
    Q_OBJECT

public:
    explicit Game();

    enum class Tile
    {
        Empty = 0,
        Snake1,
        Snake2,
        Snake3,
        Snake4,
        Food
    };
    Q_ENUM(Tile)

    enum Direction {
        None = 0,
        Up,
        Down,
        Left,
        Right
    };
    Q_ENUM(Direction);
};

#endif // GAME_H
