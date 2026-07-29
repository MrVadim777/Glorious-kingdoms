#pragma once

#include <SFML/Graphics.hpp>

#include "GameContext.h"

#include "ComponentStorage.h"
#include "ComponentTypeIndex.h"

#include "EntityFactory.h"

#include "DebugSystem.h"
#include "InputSystem.h"
#include "MovementSystem.h"
#include "RenderSystem.h"
#include "SpatialPartitionSystem.h"

class Engine {
  private:
    GameContext gameContext;

    DebugSystem            debugSystem;
    InputSystem            inputSystem;
    MovementSystem         movementSystem;
    RenderSystem           renderSystem;
    SpatialPartitionSystem spatialPartitionSystem;

    sf::Event                         event;
    sf::Clock                         clock;
    sf::Time                          deltaTime;

    EntityId player = 0;
    EntityId entity = 0;

  public:
    Engine();
    void initialization();
    void update();

  private:
    void handleEvent();
    void system();
    void render();

    void handleWindowClose() {
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {

            gameContext.gfx.window.close();
        }
    }
};
