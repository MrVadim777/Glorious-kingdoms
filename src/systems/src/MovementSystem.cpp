#include "systems/include/MovementSystem.h"
#include "components/DirectionComponent.h"
#include "components/PositionComponent.h"
#include "components/SpeedComponent.h"


void MovementSystem::update(const std::vector<std::unique_ptr<Entity>>& entities, float deltaTime) {
    for (auto& entity : entities) {
        if (entity->has<PositionComponent>() && entity->has<DirectionComponent>()) {
            entity->get<PositionComponent>()->x +=
                (int)entity->get<DirectionComponent>()->horizontal * deltaTime * entity->get<SpeedComponent>()->speed;
            entity->get<PositionComponent>()->y +=
                (int)entity->get<DirectionComponent>()->vertical * deltaTime * entity->get<SpeedComponent>()->speed;
        }
    }
}
