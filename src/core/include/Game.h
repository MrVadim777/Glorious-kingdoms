#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <memory>

#include "systems/include/InputSystem.h"
#include "systems/include/MovementSystem.h"
#include "systems/include/NpcAISystem.h"
#include "systems/include/RenderSystem.h"

#include "core/include/EntityManager.h"

class Game {
    private:
    sf::RenderWindow window;
    EntityManager    entityManager;

    InputSystem    input;
    NpcAISystem    npcAI;
    MovementSystem movement;
    RenderSystem   renderer;

    void    handleEvents();
    void    update(float dt);
    void    render();
    Entity* getPlayer();

    public:
    Game();
    ~Game();
    void run();
};
