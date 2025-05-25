#pragma once

#include "core/include/Entity.h"
#include <memory>
#include <vector>

class MovementSystem {
    public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities, float deltaTime);
};
