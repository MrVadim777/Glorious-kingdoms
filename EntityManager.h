#pragma once
#include "EntityId.h"
#include <bitset>
#include <unordered_map>

constexpr size_t MAX_COMPONENTS = 64;

class EntityManager {
  private:
    EntityId                                                  id = 0;
    std::unordered_map<EntityId, std::bitset<MAX_COMPONENTS>> masks;

  public:
    EntityId create() {
        masks[id].reset();
        return id++;
    }

    void addComponentBit(EntityId e, size_t index) {
        masks[e].set(index);
    }

    const std::bitset<MAX_COMPONENTS>& getMask(EntityId e) const {
        return masks.at(e);
    }

    const std::unordered_map < EntityId, std::bitset<MAX_COMPONENTS>>& getMasks() const {
        return masks;
    }

    std::vector<EntityId> getEntities() const {
        std::vector<EntityId> result;

        for (const auto& [e, _] : masks) {
            result.push_back(e);
        }

        return result;
    }
};