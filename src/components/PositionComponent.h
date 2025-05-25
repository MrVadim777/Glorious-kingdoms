#pragma once

#include <SFML/Graphics.hpp>

#include "IComponent.h"

struct PositionComponent : IComponent
{
    float x = 0.f;
    float y = 0.f;

    PositionComponent(float x, float y) : x(x), y(y)
    {
    }
};
