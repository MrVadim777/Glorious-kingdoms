#pragma once
#include <SFML/Graphics.hpp>

#include <bitset>

#include "ComponentTypeIndex.h"
#include "GameContext.h"

#include "DebugProfileScope.h"

class InputSystem {
  private:
    std::bitset<MAX_COMPONENTS> required;
    ECSRegistry&                ecs;
    sf::RenderWindow&           window;

  public:
    InputSystem(GameContext& gameContext) : ecs(gameContext.ecs), window(gameContext.gfx.window) {
        required.set(getComponentIndex<DirectionComponent>());
    }

    void update(EntityId player) {
        PROFILE_SCOPE("InputSystem");

        if (window.hasFocus() == false)
            return;

        const auto mask = ecs.entityManager.getMask(player);

        if ((mask & required) != required)
            return;

        auto* dir = ecs.directionStorage.get(player);

        if (dir == nullptr)
            return;

        dir->vertical = sf::Keyboard::isKeyPressed(sf::Keyboard::W)   ? Vertical::UP
                        : sf::Keyboard::isKeyPressed(sf::Keyboard::S) ? Vertical::DOWN
                                                                      : Vertical::NONE;

        dir->horizontal = sf::Keyboard::isKeyPressed(sf::Keyboard::D)   ? Horizontal::RIGHT
                          : sf::Keyboard::isKeyPressed(sf::Keyboard::A) ? Horizontal::LEFT
                                                                        : Horizontal::NONE;
    }
};
