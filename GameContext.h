#pragma once

#include "EntityManager.h"
#include "SpatialGridManager.h"

#include "ComponentStorage.h"

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
};

struct WorldServices {
    SpatialGridManager spatialGridManager;
};

struct Gfx {
    sf::RenderWindow window;
};

struct GameContext {
    ECSRegistry   ecs;
    WorldServices world;
    Gfx           gfx;
};