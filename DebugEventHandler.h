#pragma once

#include <SFML/Graphics.hpp>

#include "GameContext.h"

#include "DebugConsole.h"
#include "DebugEntityInspector.h"

class DebugEventHandler {
  private:
    ECSRegistry&      ecs;
    sf::RenderWindow& window;
    sf::View&         worldView;

  public:
    DebugEventHandler(GameContext& gameContext)
        : ecs(gameContext.ecs), window(gameContext.gfx.window), worldView(gameContext.gfx.worldView) {
    }

    void handleMouseClick(const sf::Event& event, DebugEntityInspector& inspector) {

        if (ImGui::GetIO().WantCaptureMouse)
            return;

        if (event.type != sf::Event::MouseButtonReleased || event.mouseButton.button != sf::Mouse::Left)
            return;

        const sf::Vector2i pixel{event.mouseButton.x, event.mouseButton.y};
        const sf::Vector2f world = window.mapPixelToCoords(pixel, worldView);

        for (const auto& [entity, /*mask*/ _] : ecs.entityManager.getMasks()) {
            const auto* rend = ecs.renderableStorage.get(entity);

            if (!rend)
                continue;

            if (rend->shape.getGlobalBounds().contains(world)) {
                inspector.toggleObjectVisibility(entity);
                break;
            }
        }
    }

    void handleKeyboardClick(sf::Event& event, bool& isDebugMenu) {

        if (ImGui::GetIO().WantCaptureKeyboard)
            return;

        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Tilde) {
            isDebugMenu = !isDebugMenu;
        }
    }
};