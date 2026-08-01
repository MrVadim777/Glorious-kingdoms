#pragma once

#include <algorithm>
#include <bitset>

#include "GameContext.h"

class LocationBoundsSystem {
  private:
    std::bitset<MAX_COMPONENTS> required;

    ECSRegistry& ecs;
    Location&    location;

  public:
    LocationBoundsSystem(GameContext& gameContext) : ecs(gameContext.ecs), location(gameContext.world.currentLocation) {

        required.set(getComponentIndex<PositionComponent>());
    }

    void update() {
        const float minX = 1.f;
        const float minY = 1.f;
        const float maxX = location.getWidthPixels() - 1.f;
        const float maxY = location.getHeightPixels() - 1.f;

        for (const auto& [entity, mask] : ecs.entityManager.getMasks()) {
            if ((mask & required) != required)
                continue;

            PositionComponent* pos = ecs.positionStorage.get(entity);

            if (pos == nullptr)
                continue;

            pos->x = std::clamp(pos->x, minX, maxX);
            pos->y = std::clamp(pos->y, minY, maxY);
        }
    }
};