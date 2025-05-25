#pragma once

#include "core/include/Entity.h"
#include <memory>
#include <vector>

class EntityManager {
    private:
    std::vector<std::unique_ptr<Entity>> entities;

    public:
    Entity*                                     createEntity();
    const std::vector<std::unique_ptr<Entity>>& getAll() const;

    template <typename T> std::vector<Entity*> getAllWith() const {
        std::vector<Entity*> result;

        for (auto& entity : entities) {
            if (entity->has<T>())
                result.push_back(entity.get());
        }

        return result;
    }

    void clear();
};
