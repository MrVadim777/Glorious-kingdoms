#pragma once

#include <SFML/Graphics.hpp>

#include "IComponent.h"

struct RenderableComponent : IComponent
{
    sf::RectangleShape shape;

    RenderableComponent(const sf::Vector2f& size, const sf::Color& color) : shape(size)
    {
        shape.setFillColor(color);
    }
};
