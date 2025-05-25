#include "core/include/EntityManager.h"

Entity* EntityManager::createEntity() {
    entities.push_back(std::make_unique<Entity>());
    return entities.back().get();
}

const std::vector<std::unique_ptr<Entity>>& EntityManager::getAll() const { return entities; }

void EntityManager::clear() { entities.clear(); }
