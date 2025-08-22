#pragma once
#include "EntityId.h"
#include <unordered_map>

template <typename T> class ComponentStorage {
  private:
    std::unordered_map<EntityId, T> data;

  public:
    void add(EntityId e, const T& component) {
        data[e] = component;
    }

    T* get(EntityId e) {
        auto it = data.find(e);
        return it != data.end() ? &it->second : nullptr;
    }
    bool has(EntityId e) const {
        return data.count(e) > 0;
    }
};