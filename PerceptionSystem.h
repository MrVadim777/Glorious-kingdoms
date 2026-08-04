#pragma once

#include <bitset>
#include <vector>

#include "ComponentTypeIndex.h"
#include "GameContext.h"
#include "PerceptionComponent.h"
#include "PositionComponent.h"
#include "SpatialGridManager.h"

class PerceptionSystem {
  private:
    std::bitset<MAX_COMPONENTS> required;

    WorldServices& world;
    ECSRegistry&   ecs;

  public:
    PerceptionSystem(GameContext& gameContext) : world(gameContext.world), ecs(gameContext.ecs) {

        required.set(getComponentIndex<PositionComponent>());
        required.set(getComponentIndex<PerceptionComponent>());
    }

    void update() {
        for (const auto& [entity, mask] : ecs.entityManager.getMasks()) {
            if ((mask & required) != required)
                continue;

            PositionComponent*   position   = ecs.positionStorage.get(entity);
            PerceptionComponent* perception = ecs.perceptionStorage.get(entity);

            perception->nearbyEntities.clear();
            perception->scannedCells.clear();

            CellCoord center = world.spatialGridManager.toCellCoord(position->x, position->y);

            int radius = perception->radius;

            for (int y = center.y - radius; y <= center.y + radius; ++y) {
                for (int x = center.x - radius; x <= center.x + radius; ++x) {
                    CellCoord checkedCell{x, y};

                    if (checkedCell.x < 0 || checkedCell.y < 0 ||
                        checkedCell.x >= world.currentLocation.getWidthInCells() ||
                        checkedCell.y >= world.currentLocation.getHeightInCells()) {
                        continue;
                    }

                    perception->scannedCells.push_back(checkedCell);

                    const std::vector<EntityId>* entitiesInCell = world.spatialGridManager.getCell(checkedCell);

                    if (entitiesInCell == nullptr)
                        continue;

                    for (EntityId other : *entitiesInCell) {
                        if (other == entity)
                            continue;

                        perception->nearbyEntities.push_back(other);
                    }
                }
            }
        }
    }
};