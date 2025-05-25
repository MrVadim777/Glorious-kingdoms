#pragma once

#include "core/include/Entity.h"
#include <SFML/Graphics.hpp>
#include <vector>

class RenderSystem {
    public:
    void render(sf::RenderWindow& window, const std::vector<std::unique_ptr<Entity>>& entities);
};
