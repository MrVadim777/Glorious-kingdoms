#pragma once
#include "GameContext.h"

class EntityFactory {
  public:
    static EntityId createPlayer(GameContext&        gameContext,
                                 PositionComponent   position,
                                 DirectionComponent  direction,
                                 SpeedComponent      speed,
                                 PerceptionComponent perception) {
        
        sf::RectangleShape shape(sf::Vector2f(50.f, 50.f)); //Пока кастыль
        shape.setFillColor(sf::Color::Green);
        shape.setOrigin({shape.getSize().x / 2.f, shape.getSize().y / 2.f});

        EntityId entityId = gameContext.ecs.createEntity();

        gameContext.ecs.addPosition(entityId, position);
        gameContext.ecs.addDirection(entityId, direction);
        gameContext.ecs.addSpeed(entityId, speed);
        gameContext.ecs.addRenderable(entityId, {shape});
        gameContext.ecs.addPerception(entityId, perception);

        return entityId;
    }

    static EntityId createNpc(GameContext&        gameContext,
                              PositionComponent   position,
                              DirectionComponent  direction,
                              SpeedComponent      speed,
                              PerceptionComponent perception) {

        sf::RectangleShape shape(sf::Vector2f(50.f, 50.f)); // Пока кастыль
        shape.setFillColor(sf::Color::Blue);
        shape.setOrigin({shape.getSize().x / 2.f, shape.getSize().y / 2.f});

        EntityId entityId = gameContext.ecs.createEntity();

        gameContext.ecs.addPosition(entityId, position);
        gameContext.ecs.addDirection(entityId, direction);
        gameContext.ecs.addSpeed(entityId, speed);
        gameContext.ecs.addRenderable(entityId, {shape});
        gameContext.ecs.addPerception(entityId, perception);

        return entityId;
    }

  };