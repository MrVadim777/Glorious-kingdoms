#pragma once

#include <bitset>
#include <vector>
#include <iostream>

#include "GameContext.h"

#include "DebugConsole.h"
#include "DebugEntityInspector.h"
#include "DebugEventHandler.h"
#include "DebugGridRenderSystem.h"
#include "DebugPerformanceMonitor.h"
#include "DebugUIManager.h"

#include "ComponentStorage.h"
#include "ComponentTypeIndex.h"

#include "EntityDebugVM.h"

class DebugSystem {
  private:
    std::bitset<MAX_COMPONENTS> required;

    GameContext& gameContext;

    DebugUIManager        debugUIManager;
    DebugGridRenderSystem debugGridRenderSystem;

    DebugPerformanceMonitor debugPerformanceMonitor;
    DebugEntityInspector    debugEntityInspector;

    DebugEventHandler debugEventHandler;

    std::vector<EntityDebugVM> visibleEntitiesInfo;

    bool isDebugMenu  = true;
    bool isGamePaused = false;

  public:
    DebugSystem(GameContext& gameContext)
        : gameContext(gameContext), debugGridRenderSystem(gameContext.world.spatialGridManager),
          debugEventHandler(gameContext) {

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

            debugGridRenderSystem.render(gameContext.gfx.window);

            debugPerformanceMonitor.updateFPS(deltaTime);

            debugUIManager.drawMouseInfoAtCursor(gameContext.gfx.window);

            debugUIManager.drawMainDebugWindow(
                gameContext.ecs.entityManager, debugPerformanceMonitor, isGamePaused, drawAll);

            debugEntityInspector.setDrawAllEntityInfo(drawAll);

            debugUIManager.drawEntities(visibleEntitiesInfo, gameContext.gfx.window);

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

                const auto* p = gameContext.ecs.positionStorage.get(entity);
                const auto* d = gameContext.ecs.directionStorage.get(entity);
                const auto* s = gameContext.ecs.speedStorage.get(entity);

                if (!(p && d && s))
                    continue;

                visibleEntitiesInfo.push_back({entity, p->x, p->y, d->horizontal, d->vertical, s->speed});
            }
        } else {
            const auto& picked = debugEntityInspector.getVisibleEntities();

            for (EntityId entity : picked) {

                const auto* p = gameContext.ecs.positionStorage.get(entity);
                const auto* d = gameContext.ecs.directionStorage.get(entity);
                const auto* s = gameContext.ecs.speedStorage.get(entity);

                if (!(p && d && s))
                    continue;

                visibleEntitiesInfo.push_back({entity, p->x, p->y, d->horizontal, d->vertical, s->speed});
            }
        }
    }
};
