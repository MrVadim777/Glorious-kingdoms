#pragma once

#include <bitset>
#include <iostream>
#include <vector>

#include "GameContext.h"

#include "DebugConsole.h"
#include "DebugEntityInspector.h"
#include "DebugEventHandler.h"
#include "DebugGridRenderSystem.h"
#include "DebugPerformanceMonitor.h"
#include "DebugUIManager.h"

#include "ComponentStorage.h"
#include "ComponentTypeIndex.h"

#include "DebugEntityInfo.h"

class DebugSystem {
  private:
    std::bitset<MAX_COMPONENTS> required;

    GameContext& gameContext;

    DebugUIManager        debugUIManager;
    DebugGridRenderSystem debugGridRenderSystem;

    DebugPerformanceMonitor debugPerformanceMonitor;
    DebugEntityInspector    debugEntityInspector;

    DebugEventHandler debugEventHandler;

    std::vector<DebugEntityInfo> visibleEntitiesInfo;

    bool isDebugMenu  = true;
    bool isGamePaused = false;

  public:
    DebugSystem(GameContext& gameContext)
        : gameContext(gameContext), debugGridRenderSystem(gameContext), debugEventHandler(gameContext) {

        required.set(getComponentIndex<PositionComponent>());
        required.set(getComponentIndex<DirectionComponent>());
        required.set(getComponentIndex<SpeedComponent>());

        visibleEntitiesInfo.reserve(128);
    }

    void handleEvent(sf::Event& event) {

        if (isDebugMenu) {
            debugEventHandler.handleMouseClick(event, debugEntityInspector);
        }

        debugEventHandler.handleKeyboardClick(event, isDebugMenu);
    }

    void update(const sf::Time& deltaTime) {
        if (isDebugMenu) {
            debugPerformanceMonitor.updateTPS(deltaTime);

            collectDTOForVisibleEntities();
        }
    }

    void render(const sf::Time& deltaTime) {

        if (isDebugMenu == true) {
            bool drawAll = debugEntityInspector.isDrawAllEntityInfo();

            if (debugUIManager.getDrawPerceptionCells()) {
                debugGridRenderSystem.renderPerceptionCells(gameContext.gfx.window);
            }

            if (debugUIManager.getDrawGrid()) {
                debugGridRenderSystem.render(gameContext.gfx.window);
            }

            debugPerformanceMonitor.updateFPS(deltaTime);

            debugUIManager.drawMouseInfoAtCursor(gameContext.gfx.window, gameContext.gfx.worldView);

            debugUIManager.drawMainDebugWindow(
                gameContext.ecs.entityManager, debugPerformanceMonitor, isGamePaused, drawAll);

            debugEntityInspector.setDrawAllEntityInfo(drawAll);

            debugUIManager.drawEntities(visibleEntitiesInfo, gameContext.gfx.window, gameContext.gfx.worldView);

            if (debugUIManager.isMainDebugMenuDraw == true) {
                DebugConsole::render();
            }
        }
    }

  private:
    void collectDTOForVisibleEntities() {
        visibleEntitiesInfo.clear();

        if (debugEntityInspector.isDrawAllEntityInfo()) {
            for (const auto& [entity, mask] : gameContext.ecs.entityManager.getMasks()) {
                if ((mask & required) != required)
                    continue;

                DebugEntityInfo info;

                if (collectEntityInfo(entity, info)) {
                    visibleEntitiesInfo.push_back(info);
                }
            }
        } else {
            const auto& picked = debugEntityInspector.getVisibleEntities();

            for (EntityId entity : picked) {
                DebugEntityInfo info;

                if (collectEntityInfo(entity, info)) {
                    visibleEntitiesInfo.push_back(info);
                }
            }
        }
    }

    bool collectEntityInfo(EntityId entity, DebugEntityInfo& info) {
        const auto* p = gameContext.ecs.positionStorage.get(entity);
        const auto* d = gameContext.ecs.directionStorage.get(entity);
        const auto* s = gameContext.ecs.speedStorage.get(entity);

        if (!(p && d && s))
            return false;

        info.id    = entity;
        info.x     = p->x;
        info.y     = p->y;
        info.h     = d->horizontal;
        info.v     = d->vertical;
        info.speed = s->speed;

        const auto* perception = gameContext.ecs.perceptionStorage.get(entity);

        if (perception != nullptr) {
            info.hasPerception    = true;
            info.perceptionRadius = perception->radius;
            info.nearbyEntities   = perception->nearbyEntities;
        }

        return true;
    }
};
