#pragma once
#include "SpatialGridManager.h"
#include <SFML/Graphics.hpp>

class DebugGridRenderSystem {
  private:
    const SpatialGridManager& spatialGridManager;
    sf::Color          emptyCellColor  = sf::Color(255, 255, 255, 100);
    sf::Color          entityCellColor = sf::Color(50, 255, 50, 100);

  public:
    DebugGridRenderSystem(const SpatialGridManager& spatialGridManager) : spatialGridManager(spatialGridManager) {
    }

    void render(sf::RenderWindow& window) {

        sf::RectangleShape rectangle;
        float              cellSize = spatialGridManager.getCellSize();

        for (const auto& [coord, entities] : spatialGridManager.getAllCells()) {
            rectangle.setSize(sf::Vector2f(cellSize, cellSize));
            rectangle.setPosition(sf::Vector2f(coord.x * cellSize, coord.y * cellSize));
            rectangle.setFillColor(sf::Color(0,0,0,0));
            rectangle.setOutlineColor(entityCellColor);
            rectangle.setOutlineThickness(1.f);

            window.draw(rectangle);
        }
    }
};