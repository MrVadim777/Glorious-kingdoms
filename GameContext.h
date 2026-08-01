#pragma once

#include "Location.h"
#include "EntityManager.h"
#include "SpatialGridManager.h"

#include "ComponentStorage.h"
#include "ComponentTypeIndex.h"

#include "DirectionComponent.h"
#include "PositionComponent.h"
#include "RenderableComponent.h"
#include "SpeedComponent.h"
#include "CellIndexComponent.h"

struct ECSRegistry {
    EntityManager entityManager;

    ComponentStorage<PositionComponent>   positionStorage;
    ComponentStorage<DirectionComponent>  directionStorage;
    ComponentStorage<SpeedComponent>      speedStorage;
    ComponentStorage<RenderableComponent> renderableStorage;
    ComponentStorage<CellIndexComponent>  cellIndexStorage;

    EntityId createEntity() {
        return entityManager.create();
    }

    void addPosition(EntityId entityId, const PositionComponent& position) {
        positionStorage.add(entityId, position);
        entityManager.addComponentBit(entityId, getComponentIndex<PositionComponent>());
    }

    void addDirection(EntityId entityId, const DirectionComponent& direction) {
        directionStorage.add(entityId, direction);
        entityManager.addComponentBit(entityId, getComponentIndex<DirectionComponent>());
    }

    void addSpeed(EntityId entityId, const SpeedComponent& speed) {
        speedStorage.add(entityId, speed);
        entityManager.addComponentBit(entityId, getComponentIndex<SpeedComponent>());
    }

    void addRenderable(EntityId entityId, const RenderableComponent& renderable) {
        renderableStorage.add(entityId, renderable);
        entityManager.addComponentBit(entityId, getComponentIndex<RenderableComponent>());
    }

    void addCellIndex(EntityId entityId, const CellIndexComponent& cellIndex) {
        cellIndexStorage.add(entityId, cellIndex);
        entityManager.addComponentBit(entityId, getComponentIndex<CellIndexComponent>());
    }
};

struct WorldServices {
    Location           currentLocation;
    SpatialGridManager spatialGridManager;

    WorldServices() : currentLocation(), spatialGridManager(currentLocation.getCellSize()) {
    }
};

struct Gfx {
    sf::RenderWindow window;
    sf::View         worldView;
};

struct GameContext {
    ECSRegistry   ecs;
    WorldServices world;
    Gfx           gfx;
};