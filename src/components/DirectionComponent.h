#pragma once

#include "IComponent.h"

struct Direction 
{
    enum class Vertical
    {
        NONE = 0,
        UP = -1,
        DOWN = 1
    };
    enum class Horizontal
    {
        NONE = 0,
        RIGHT = 1,
        LEFT = -1
    };
};

struct DirectionComponent : IComponent
{
    Direction::Vertical vertical = Direction::Vertical::NONE;
    Direction::Horizontal horizontal = Direction::Horizontal::NONE;
};
