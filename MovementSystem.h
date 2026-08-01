#pragma once

#include <cmath>

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

            float dx = static_cast<float>(d->horizontal);
            float dy = static_cast<float>(d->vertical);

            float length = std::sqrt(dx * dx + dy * dy);

            if (length > 0.f) {
                dx /= length;
                dy /= length;
            }

            p->x += dx * s->speed * dt;
            p->y += dy * s->speed * dt;
        }
    }
};
