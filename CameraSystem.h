#pragma once

#include <algorithm>
#include <cmath>

#include "GameContext.h"
#include "PositionComponent.h"

class CameraSystem {
  private:
    ECSRegistry& ecs;
    sf::View&    view;

    sf::Vector2f baseSize;

    float currentZoom = 1.f;
    float targetZoom  = 1.f;

    float minZoom = 0.5f;
    float maxZoom = 3.0f;

    float followSmoothness = 6.f;
    float zoomSmoothness   = 8.f;

  public:
    CameraSystem(GameContext& gameContext) : ecs(gameContext.ecs), view(gameContext.gfx.worldView) {
    }

    void initialize(const sf::RenderWindow& window) {
        view     = window.getDefaultView();
        baseSize = view.getSize();
    }

    void handleEvent(const sf::Event& event) {
        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.delta > 0) {
                targetZoom *= 0.9f;
            } else {
                targetZoom *= 1.1f;
            }

            targetZoom = std::clamp(targetZoom, minZoom, maxZoom);
        }
    }

    void update(EntityId targetEntity, const sf::Time& deltaTime) {
        PositionComponent* position = ecs.positionStorage.get(targetEntity);

        if (position == nullptr)
            return;

        const float dt = deltaTime.asSeconds();

        sf::Vector2f currentCenter = view.getCenter();
        sf::Vector2f targetCenter(position->x, position->y);

        float followT = 1.f - std::exp(-followSmoothness * dt);

        sf::Vector2f newCenter;
        newCenter.x = currentCenter.x + (targetCenter.x - currentCenter.x) * followT;
        newCenter.y = currentCenter.y + (targetCenter.y - currentCenter.y) * followT;

        float zoomT = 1.f - std::exp(-zoomSmoothness * dt);
        currentZoom = currentZoom + (targetZoom - currentZoom) * zoomT;

        view.setCenter(newCenter);
        view.setSize(baseSize * currentZoom);
    }
};