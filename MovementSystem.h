#pragma once

#include "GameContext.h"

#include "ComponentStorage.h"
#include "ComponentTypeIndex.h"

#include "DirectionComponent.h"
#include "PositionComponent.h"
#include "SpeedComponent.h"

class MovementSystem {
  private:
    std::bitset<MAX_COMPONENTS> required;
    ECSRegistry&                ecs;

  public:
    MovementSystem(GameContext& gameContext) : ecs(gameContext.ecs) {
        required.set(getComponentIndex<PositionComponent>());
        required.set(getComponentIndex<DirectionComponent>());
        required.set(getComponentIndex<SpeedComponent>());
    }

    void update(const sf::Time& deltaTime) {
        PROFILE_SCOPE("MovementSystem");

        const float dt = deltaTime.asSeconds();

        for (const auto& [entity, mask] : ecs.entityManager.getMasks()) {

            if ((mask & required) != required)
                continue;

            auto* p = ecs.positionStorage.get(entity);
            auto* d = ecs.directionStorage.get(entity);
            auto* s = ecs.speedStorage.get(entity);

            if ((p && d && s) == false)
                continue;

            p->x += (float)d->horizontal * s->speed * dt;
            p->y += (float)d->vertical * s->speed * dt;
        }
    }
};
