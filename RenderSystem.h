#pragma once
#include <SFML/Graphics.hpp>
#include <bitset>

#include "GameContext.h"

#include "ComponentStorage.h"
#include "ComponentTypeIndex.h"

class RenderSystem {
  private:
    std::bitset<MAX_COMPONENTS> required;
    ECSRegistry&                ecs;
    sf::RenderWindow&           window;

  public:
    RenderSystem(GameContext& gameContext) : ecs(gameContext.ecs), window(gameContext.gfx.window) {
        required.set(getComponentIndex<PositionComponent>());
        required.set(getComponentIndex<RenderableComponent>());
    }

    void render() {
        PROFILE_SCOPE("RenderSystem");

        for (const auto& [entity, mask] : ecs.entityManager.getMasks()) {

            if ((mask & required) != required)
                continue;

            auto* pos = ecs.positionStorage.get(entity);
            auto* rnd = ecs.renderableStorage.get(entity);

            if ((pos && rnd) == false)
                continue;

            rnd->shape.setPosition(pos->x, pos->y);
            window.draw(rnd->shape);
        }
    }
};