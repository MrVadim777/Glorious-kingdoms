#pragma once

#include "EntityId.h"
#include "DirectionComponent.h"

struct EntityDebugVM {
    EntityId   id;
    float      x, y;
    Horizontal h;
    Vertical   v;
    float      speed;
};