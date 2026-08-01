#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

#include "DebugEntityInspector.h"
#include "DebugPerformanceMonitor.h"
#include "DebugProfilerTimer.h"

#include "EntityManager.h"

#include "DirectionComponent.h"

#include "DebugEntityInfo.h"

class DebugUIManager {
  public:
    bool isMainDebugMenuDraw  = false;
    bool isDrawCollisionBoxes = false;
    bool isDrawCameraBounds   = false;
    bool isDrawGrid           = false;

    void drawMainDebugWindow(const EntityManager&           entityManager,
                             const DebugPerformanceMonitor& debugPerformanceMonitor,
                             bool&                          isGamePaused,
                             bool&                          isDrawAllEntityInfo) {

        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, 180.f), ImGuiCond_Always);

        isMainDebugMenuDraw =
            ImGui::Begin("Main Debug Panel", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

        if (isMainDebugMenuDraw) {
            if (ImGui::BeginTabBar("DebugTabBar")) {

                drawInfoDebugWindow(entityManager, debugPerformanceMonitor);
                drawTogglesDebugWindow(isGamePaused, isDrawAllEntityInfo);
                drawAIDebugWindow();
                drawViewDebugWindow();

                ImGui::EndTabBar();
            }
        }

        ImGui::End();
    }

    void drawEntities(const std::vector<DebugEntityInfo>& vms, sf::RenderWindow& window, const sf::View& worldView) {

        for (const auto& vm : vms) {
            // world -> screen
            sf::Vector2i pixel = window.mapCoordsToPixel(sf::Vector2f(vm.x, vm.y), worldView);
            ImVec2       screenPos(static_cast<float>(pixel.x) + 60.f, static_cast<float>(pixel.y));

            std::string windowName = "Entity " + std::to_string(vm.id);
            ImGui::SetNextWindowPos(screenPos, ImGuiCond_Always);
            ImGui::Begin(windowName.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize);

            ImGui::Separator();
            ImGui::Text("Entity ID %d", vm.id);
            ImGui::Separator();

            ImGui::Text("Position: x=%.2f, y=%.2f", vm.x, vm.y);
            ImGui::Text("Direction: H=%s, V=%s", directionToString(vm.h), directionToString(vm.v));
            ImGui::Text("Speed: %.2f", vm.speed);

            ImGui::End();
        }
    }

    void drawMouseInfoAtCursor(sf::RenderWindow& window, const sf::View& worldView) {
        sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorld = window.mapPixelToCoords(mousePixel, worldView);

        ImVec2 imguiPos = ImVec2(static_cast<float>(mousePixel.x) + 12.f, static_cast<float>(mousePixel.y) + 12.f);

        ImGui::SetNextWindowPos(imguiPos, ImGuiCond_Always);
        ImGui::SetNextWindowBgAlpha(0.6f);

        ImGui::Begin("Mouse Tooltip",
                     nullptr,
                     ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize |
                         ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings |
                         ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);

        ImGui::Text("screen: x=%d, y=%d", mousePixel.x, mousePixel.y);
        ImGui::Text("world:  x=%.1f, y=%.1f", mouseWorld.x, mouseWorld.y);

        ImGui::End();
    }

    bool getDrawCollisionBoxes() const {
        return isDrawCollisionBoxes;
    }

    bool getDrawCameraBounds() const {
        return isDrawCameraBounds;
    }

    bool getDrawGrid() const {
        return isDrawGrid;
    }

  private:
    // ------------------------- MainDebugWindow -------------------------

    void drawInfoDebugWindow(const EntityManager&           entityManager,
                             const DebugPerformanceMonitor& debugPerformanceMonitor) {

        if (ImGui::BeginTabItem("Info:")) {

            if (ImGui::BeginChild("ChildWindow_1", ImVec2(200, 0), true)) {
                ImGui::Text("InputSystem:      %.3f ms", DebugProfilerTimer::getTime("InputSystem"));
                ImGui::Text("MovementSystem:   %.3f ms", DebugProfilerTimer::getTime("MovementSystem"));
                ImGui::Text("RenderSystem:     %.3f ms", DebugProfilerTimer::getTime("RenderSystem"));

                ImGui::EndChild();
            }

            ImGui::SameLine();

            if (ImGui::BeginChild("ChildWindow_2", ImVec2(100, 0), true)) {
                ImGui::Text("Entities: %zu", entityManager.getEntities().size());
                ImGui::Text("Players:  %zu", 0);
                ImGui::Text("Npcs:     %zu", 0);
                ImGui::Text("Items:    %zu", 0);

                ImGui::EndChild();
            }

            ImGui::SameLine();

            if (ImGui::BeginChild("ChildWindow_3", ImVec2(80, 50), true)) {
                ImGui::Text("FPS: %.f", debugPerformanceMonitor.getFPS());
                ImGui::Text("TPS: %.f", debugPerformanceMonitor.getTPS());

                ImGui::EndChild();
            }

            ImGui::EndTabItem();
        }
    }

    void drawTogglesDebugWindow(bool& isGamePaused, bool& isDrawAllEntityInfo) {
        if (ImGui::BeginTabItem("Toggles:")) {

            if (ImGui::Button("Respawn Entities")) {
            }

            ImGui::Checkbox("Game paused", &isGamePaused);
            ImGui::SameLine();
            ImGui::Checkbox("Draw all entity info", &isDrawAllEntityInfo);

            ImGui::EndTabItem();
        }
    }

    void drawAIDebugWindow() {
        if (ImGui::BeginTabItem("AI Debug")) {
            ImGui::Text("No AI data yet.");
            ImGui::EndTabItem();
        }
    }

    void drawViewDebugWindow() {
        if (ImGui::BeginTabItem("View")) {
            ImGui::Text("Camera Position: x=..., y=...");
            ImGui::Checkbox("Draw Collision Boxes", &isDrawCollisionBoxes);
            ImGui::SameLine();
            ImGui::Checkbox("Show Camera Bounds", &isDrawCameraBounds);
            ImGui::SameLine();
            ImGui::Checkbox("Show Grid", &isDrawGrid);
            ImGui::EndTabItem();
        }
    }

    // ------------------------- EntityInfo -------------------------

    const char* directionToString(Horizontal dir) {
        switch (dir) {
        case Horizontal::LEFT:
            return "LEFT";
        case Horizontal::RIGHT:
            return "RIGHT";
        case Horizontal::NONE:
            return "NONE";
        default:
            return "?";
        }
    }

    const char* directionToString(Vertical dir) {
        switch (dir) {
        case Vertical::UP:
            return "UP";
        case Vertical::DOWN:
            return "DOWN";
        case Vertical::NONE:
            return "NONE";
        default:
            return "?";
        }
    }
};
