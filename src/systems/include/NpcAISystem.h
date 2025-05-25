#pragma once

#include "core/include/Entity.h"
#include <vector>

class NpcAISystem {
    public:
    void update(Entity* player, std::vector<Entity*> entities);
};
