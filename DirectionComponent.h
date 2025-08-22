#pragma once

enum class Vertical { NONE = 0, UP = -1, DOWN = 1 };
enum class Horizontal { NONE = 0, RIGHT = 1, LEFT = -1};

struct DirectionComponent {
    Horizontal horizontal = Horizontal::NONE;
    Vertical   vertical   = Vertical::NONE;
};