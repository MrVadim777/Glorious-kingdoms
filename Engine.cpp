#include "Engine.h"

Engine::Engine()
    : inputSystem(gameContext), movementSystem(gameContext),
      renderSystem(gameContext), spatialPartitionSystem(gameContext), debugSystem(gameContext) {

    gameContext.gfx.window.create(sf::VideoMode(1920, 1080), "ECS Demo");
    gameContext.gfx.window.setFramerateLimit(120);
}

void Engine::initialization() {
    player = EntityFactory::createPlayer(gameContext, {700.f, 500.f}, {Horizontal::NONE, Vertical::NONE}, {50.f});
    entity = EntityFactory::createNpc(gameContext, {1200.f, 500.f}, {Horizontal::NONE, Vertical::NONE}, {50.f});

    ImGui::SFML::Init(gameContext.gfx.window);
}

void Engine::update() {
    while (gameContext.gfx.window.isOpen()) {
        deltaTime = clock.restart();
        ImGui::SFML::Update(gameContext.gfx.window, deltaTime);

        handleEvent();
        system();
        render();
    }
}

void Engine::handleEvent() {
    while (gameContext.gfx.window.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(event);
        handleWindowClose();

        debugSystem.handleEvent(event);
    }
}

void Engine::system() {
    inputSystem.update(player);
    movementSystem.update(deltaTime);
    spatialPartitionSystem.update();
    debugSystem.update(deltaTime);
}

void Engine::render() {
    gameContext.gfx.window.clear();

    renderSystem.render();
    debugSystem.render(deltaTime);

    ImGui::SFML::Render(gameContext.gfx.window);

    gameContext.gfx.window.display();
}
