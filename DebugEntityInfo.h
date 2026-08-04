#pragma once

#include <vector>

#include "DirectionComponent.h"
#include "EntityId.h"

struct DebugEntityInfo {
    EntityId id;

    float x, y;

    Horizontal h;
    Vertical   v;

    float speed;

    bool                  hasPerception    = false;
    int                   perceptionRadius = 0;
    std::vector<EntityId> nearbyEntities;
};