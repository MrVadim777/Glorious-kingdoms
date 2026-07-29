#pragma once
#include "GameContext.h"
#include <SFML/Graphics.hpp>

class DebugGridRenderSystem {
  private:
    const GameContext& gameContext;
    sf::VertexArray    lines;
    sf::Color          entityCellColor = sf::Color(50, 255, 50, 100);

  public:
    DebugGridRenderSystem(const GameContext& gameContext) : gameContext(gameContext), lines(sf::Lines) {

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
    }

    void render(sf::RenderWindow& window) {

        sf::RectangleShape rectangle;

        float cellSize = gameContext.world.spatialGridManager.getCellSize();

        window.draw(lines);

        for (const auto& [coord, entities] : gameContext.world.spatialGridManager.getAllCells()) {
            rectangle.setSize(sf::Vector2f(cellSize, cellSize));
            rectangle.setPosition(sf::Vector2f(coord.x * cellSize, coord.y * cellSize));
            rectangle.setFillColor(sf::Color(0, 0, 0, 0));
            rectangle.setOutlineColor(entityCellColor);
            rectangle.setOutlineThickness(1.f);

            window.draw(rectangle);
        }
    }
};