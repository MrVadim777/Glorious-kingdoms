#include "Engine.h"

Engine::Engine()
    : inputSystem(gameContext), movementSystem(gameContext),
      renderSystem(gameContext), spatialPartitionSystem(gameContext), debugSystem(gameContext) {

    gameContext.gfx.window.create(sf::VideoMode(1920, 1080), "ECS Demo");
    gameContext.gfx.window.setFramerateLimit(120);
}

void Engine::initialization() {
    player = gameContext.ecs.entityManager.create();

    gameContext.ecs.positionStorage.add(player, {700.f, 500.f});
    gameContext.ecs.directionStorage.add(player, {Horizontal::NONE, Vertical::NONE});
    gameContext.ecs.speedStorage.add(player, {50.f});

    sf::RectangleShape shape(sf::Vector2f(50.f, 50.f));
    shape.setFillColor(sf::Color::Green);
    gameContext.ecs.renderableStorage.add(player, {shape});

    gameContext.ecs.entityManager.addComponentBit(player, getComponentIndex<PositionComponent>());
    gameContext.ecs.entityManager.addComponentBit(player, getComponentIndex<DirectionComponent>());
    gameContext.ecs.entityManager.addComponentBit(player, getComponentIndex<SpeedComponent>());
    gameContext.ecs.entityManager.addComponentBit(player, getComponentIndex<RenderableComponent>());

    entity = gameContext.ecs.entityManager.create();

    gameContext.ecs.positionStorage.add(entity, {1200.f, 500.f});
    gameContext.ecs.directionStorage.add(entity, {Horizontal::NONE, Vertical::NONE});
    gameContext.ecs.speedStorage.add(entity, {50.f});

    sf::RectangleShape shape2(sf::Vector2f(50.f, 50.f));
    shape2.setFillColor(sf::Color::Blue);
    gameContext.ecs.renderableStorage.add(entity, {shape2});

    gameContext.ecs.entityManager.addComponentBit(entity, getComponentIndex<PositionComponent>());
    gameContext.ecs.entityManager.addComponentBit(entity, getComponentIndex<DirectionComponent>());
    gameContext.ecs.entityManager.addComponentBit(entity, getComponentIndex<SpeedComponent>());
    gameContext.ecs.entityManager.addComponentBit(entity, getComponentIndex<RenderableComponent>());

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
