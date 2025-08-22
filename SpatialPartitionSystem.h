#pragma once

#include <bitset>

#include "GameContext.h"

#include "CellIndexComponent.h"

class SpatialPartitionSystem {
  private:
    std::bitset<MAX_COMPONENTS> required;
    ECSRegistry&                ecs;
    SpatialGridManager&         spatialGridManager;

  public:
    SpatialPartitionSystem(GameContext& gameContext)
        : ecs(gameContext.ecs), spatialGridManager(gameContext.world.spatialGridManager) {

        required.set(getComponentIndex<PositionComponent>());
    }

    void update() {
        for (const auto& [entity, mask] : ecs.entityManager.getMasks()) {

            if ((mask & required) != required)
                continue;

            PositionComponent* pos = ecs.positionStorage.get(entity);

            if (pos == nullptr)
                continue;

            CellCoord newCoord = spatialGridManager.toCellCoord(pos->x, pos->y);

            if (ecs.cellIndexStorage.has(entity)) {
                CellIndexComponent* cellIndex = ecs.cellIndexStorage.get(entity);
                CellCoord           oldCoord  = {cellIndex->x, cellIndex->y};

                if (oldCoord == newCoord)
                    continue;

                spatialGridManager.move(entity, oldCoord, newCoord);
                cellIndex->x = newCoord.x;
                cellIndex->y = newCoord.y;
            } else {
                spatialGridManager.insert(entity, newCoord);
                ecs.cellIndexStorage.add(entity, CellIndexComponent{newCoord.x, newCoord.y});
            }
        }
    }
};