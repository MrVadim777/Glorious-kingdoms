#pragma once

#include "EntityId.h"
#include "DirectionComponent.h"

struct DebugEntityInfo {
    EntityId   id;
    float      x, y;
    Horizontal h;
    Vertical   v;
    float      speed;
};