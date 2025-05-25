#pragma once

#include "IComponent.h"

struct SpeedComponent : IComponent
{
    float speed;

    SpeedComponent(float speed) : speed(speed)
    {
    }
};
