#pragma once

#include <unordered_set>

#include "EntityManager.h"

#include "DebugConsole.h"

#include "ComponentStorage.h"

#include "DirectionComponent.h"
#include "PositionComponent.h"
#include "SpeedComponent.h"

class DebugEntityInspector {
  private:
    std::unordered_set<EntityId> entitiesForVisibleDebugMenu;

    bool drawAllEntityInfo = false;

  public:
    void toggleObjectVisibility(EntityId entityId) {
        if (entitiesForVisibleDebugMenu.count(entityId)) {
            entitiesForVisibleDebugMenu.erase(entityId);

            DebugConsole::log(std::string("Entity id: " + std::to_string(entityId) + " is invisible"),
                              DebugConsole::MessageType::ERROR);
        } else {
            entitiesForVisibleDebugMenu.insert(entityId);

            DebugConsole::log(std::string("Entity id: " + std::to_string(entityId) + " is visible"),
                              DebugConsole::MessageType::WARNING);
        }
    }

    const std::unordered_set<EntityId>& getVisibleEntities() const {
        return entitiesForVisibleDebugMenu;
    }

    bool isDrawAllEntityInfo() const {
        return this->drawAllEntityInfo;
    }

    void setDrawAllEntityInfo(bool state) {
        drawAllEntityInfo = state;
    }
};