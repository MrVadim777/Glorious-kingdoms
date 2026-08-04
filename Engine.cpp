#include "Engine.h"

Engine::Engine()
    : inputSystem(gameContext), movementSystem(gameContext),
      renderSystem(gameContext), spatialPartitionSystem(gameContext), 
      debugSystem(gameContext), locationBoundsSystem(gameContext), 
      cameraSystem(gameContext), perceptionSystem(gameContext){

    gameContext.gfx.window.create(sf::VideoMode(1920, 1080), "ECS Demo");
    gameContext.gfx.window.setFramerateLimit(120);

    cameraSystem.initialize(gameContext.gfx.window);
}

void Engine::initialization() {
    player = EntityFactory::createPlayer(gameContext, {700.f, 500.f}, {Horizontal::NONE, Vertical::NONE}, {300.f}, {1});
    entity = EntityFactory::createNpc(gameContext, {1200.f, 500.f}, {Horizontal::NONE, Vertical::NONE}, {50.f}, {1});

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

        cameraSystem.handleEvent(event);
        debugSystem.handleEvent(event);
    }
}

void Engine::system() {
    inputSystem.update(player);
    movementSystem.update(deltaTime);
    locationBoundsSystem.update();
    spatialPartitionSystem.update();
    perceptionSystem.update();
    cameraSystem.update(player, deltaTime);
    debugSystem.update(deltaTime);
}

void Engine::render() {
    gameContext.gfx.window.clear();
    gameContext.gfx.window.setView(gameContext.gfx.worldView);

    renderSystem.render();
    debugSystem.render(deltaTime);

    gameContext.gfx.window.setView(gameContext.gfx.window.getDefaultView());

    ImGui::SFML::Render(gameContext.gfx.window);

    gameContext.gfx.window.display();
}
