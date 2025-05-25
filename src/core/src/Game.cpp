#include "core/include/Game.h"

#include "components/DirectionComponent.h"
#include "components/PositionComponent.h"
#include "components/RenderableComponent.h"
#include "components/SpeedComponent.h"
#include "components/tag/NpcTagComponent.h"
#include "components/tag/PlayerTagComponent.h"


Game::Game() : window(sf::VideoMode(800, 600), "Glorious Kingdoms") {
    ImGui::SFML::Init(window);

    Entity* player = entityManager.createEntity();
    player->add<PositionComponent>(100.f, 100.f);
    player->add<RenderableComponent>(sf::Vector2f(50.f, 50.f), sf::Color::White);
    player->add<SpeedComponent>(100.f);
    player->add<DirectionComponent>();
    player->add<PlayerTagComponent>();

    for (int i = 0; i < 1; ++i) {
        Entity* npc = entityManager.createEntity();
        npc->add<PositionComponent>(200.f + i * 60.f, 200.f);
        npc->add<RenderableComponent>(sf::Vector2f(50.f, 50.f), sf::Color::Green);
        npc->add<SpeedComponent>(50.f);
        npc->add<DirectionComponent>();
        npc->add<NpcTagComponent>();
    }
}

Game::~Game() { ImGui::SFML::Shutdown(); }

void Game::run() {
    sf::Clock clock;

   while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event); // 👈 обрабатываем события ImGui
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        float dt = clock.restart().asSeconds();

        ImGui::SFML::Update(window, sf::seconds(dt)); // 👈 обновляем ImGui

        // твои системы
        input.update(*getPlayer());
        npcAI.update(getPlayer(), entityManager.getAllWith<NpcTagComponent>());
        update(dt);

        // окно ImGui для теста
        ImGui::Begin("💀 Debug Window");
        ImGui::Text("Hello from ImGui!");
        ImGui::End();

        window.clear();
        renderer.render(window, entityManager.getAll());

        ImGui::SFML::Render(window); // 👈 отрисовываем ImGui
        window.display();
    }
}

void Game::handleEvents() {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
    }

    ImGui::SFML::ProcessEvent(event);
}

void Game::update(float dt) { movement.update(entityManager.getAll(), dt); }

void Game::render() {
    window.clear();
    renderer.render(window, entityManager.getAll());

    // ==== HUD BEGIN ====
    Entity* player = getPlayer();
    if (player && player->has<PositionComponent>() && player->has<SpeedComponent>()) {
        auto* pos     = player->get<PositionComponent>();
        auto* speed   = player->get<SpeedComponent>();
        auto  npcList = entityManager.getAllWith<NpcTagComponent>();

        ImGui::Begin("Debug HUD");

        ImGui::Text("👤 Player Position: (%.1f, %.1f)", pos->x, pos->y);
        ImGui::Text("💨 Speed: %.2f", speed->speed);
        ImGui::Text("🧟 NPC Count: %d", static_cast<int>(npcList.size()));

        ImGui::End();
    }

    ImGui::SFML::Render(window);
    // ==== HUD END ====

    window.display();
}

Entity* Game::getPlayer() {
    auto players = entityManager.getAllWith<PlayerTagComponent>();
    return players.empty() ? nullptr : players[0];
}
