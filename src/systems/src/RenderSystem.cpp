#include "systems/include/RenderSystem.h"
#include "components/PositionComponent.h"
#include "components/RenderableComponent.h"


void RenderSystem::render(sf::RenderWindow& window, const std::vector<std::unique_ptr<Entity>>& entities) {
    for (auto& entity : entities) {
        if (entity->has<RenderableComponent>() && entity->has<PositionComponent>()) {
            auto* position   = entity->get<PositionComponent>();
            auto* renderable = entity->get<RenderableComponent>();

            renderable->shape.setPosition(position->x, position->y);
            window.draw(renderable->shape);
        }
    }
}
