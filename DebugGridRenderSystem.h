#pragma once

#include <SFML/Graphics.hpp>

#include "GameContext.h"
#include "PerceptionComponent.h"
#include "SpatialGridManager.h"

struct CellColor {
    sf::Color line;
    sf::Color fill;
};

class DebugGridRenderSystem {
  private:
    GameContext&    gameContext;
    sf::VertexArray lines;
    CellColor       entityGridColor;
    CellColor       perceptionGridColor;
  public:
    DebugGridRenderSystem(GameContext& gameContext) : gameContext(gameContext), lines(sf::Lines) {

        float cellSize = gameContext.world.currentLocation.getCellSize();
        float width    = gameContext.world.currentLocation.getWidthPixels();
        float height   = gameContext.world.currentLocation.getHeightPixels();

        for (size_t i = 1; i < gameContext.world.currentLocation.getWidthInCells(); i++) {
            lines.append(sf::Vertex(sf::Vector2f(i * cellSize, 0.f), sf::Color(80, 80, 80, 120)));
            lines.append(sf::Vertex(sf::Vector2f(i * cellSize, height), sf::Color(80, 80, 80, 120)));
        }
        for (size_t i = 1; i < gameContext.world.currentLocation.getHeightInCells(); i++) {
            lines.append(sf::Vertex(sf::Vector2f(0.f, i * cellSize), sf::Color(80, 80, 80, 120)));
            lines.append(sf::Vertex(sf::Vector2f(width, i * cellSize), sf::Color(80, 80, 80, 120)));
        }

        lines.append(sf::Vertex(sf::Vector2f(0.f, 0.f), sf::Color::Red));
        lines.append(sf::Vertex(sf::Vector2f(width, 0.f), sf::Color::Red));

        lines.append(sf::Vertex(sf::Vector2f(0.f, 0.f), sf::Color::Red));
        lines.append(sf::Vertex(sf::Vector2f(0.f, height), sf::Color::Red));

        lines.append(sf::Vertex(sf::Vector2f(width, 0.f), sf::Color::Red));
        lines.append(sf::Vertex(sf::Vector2f(width, height), sf::Color::Red));

        lines.append(sf::Vertex(sf::Vector2f(width, height), sf::Color::Red));
        lines.append(sf::Vertex(sf::Vector2f(0.f, height), sf::Color::Red));

        entityGridColor.line = sf::Color(0, 255, 0, 255);
        entityGridColor.fill = sf::Color(0, 255, 0, 80);

        perceptionGridColor.line = sf::Color(255, 0, 0, 255);
        perceptionGridColor.fill = sf::Color(255, 0, 0, 20);
    }

    void renderPerceptionCells(sf::RenderWindow& window) {
        sf::RectangleShape rectangle;

        float cellSize = gameContext.world.spatialGridManager.getCellSize();

        rectangle.setSize(sf::Vector2f(cellSize, cellSize));
        rectangle.setFillColor(perceptionGridColor.fill);
        rectangle.setOutlineColor(perceptionGridColor.line);
        rectangle.setOutlineThickness(1.f);

        for (const auto& [entity, mask] : gameContext.ecs.entityManager.getMasks()) {
            const PerceptionComponent* perception = gameContext.ecs.perceptionStorage.get(entity);

            if (perception == nullptr)
                continue;

            for (const CellCoord& cell : perception->scannedCells) {
                rectangle.setPosition(sf::Vector2f(cell.x * cellSize, cell.y * cellSize));

                window.draw(rectangle);
            }
        }
    }

    void render(sf::RenderWindow& window) {

        sf::RectangleShape rectangle;

        float cellSize = gameContext.world.spatialGridManager.getCellSize();

        window.draw(lines);

        for (const auto& [coord, entities] : gameContext.world.spatialGridManager.getAllCells()) {
            rectangle.setSize(sf::Vector2f(cellSize, cellSize));
            rectangle.setPosition(sf::Vector2f(coord.x * cellSize, coord.y * cellSize));
            rectangle.setFillColor(entityGridColor.fill);
            rectangle.setOutlineColor(entityGridColor.line);
            rectangle.setOutlineThickness(1.f);

            window.draw(rectangle);
        }
    }
};