#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>

#include "components/IComponent.h"

class Entity {
    private:
    std::unordered_map<std::type_index, std::unique_ptr<IComponent>> components;

    public:
    template <typename T, typename... Args> void add(Args&&... args) {
        components[typeid(T)] = std::make_unique<T>(std::forward<Args>(args)...);
    }

    template <typename T> bool has() const { return components.count(typeid(T)) > 0; }

    template <typename T> T* get() {
        auto it = components.find(typeid(T));
        return it != components.end() ? static_cast<T*>(it->second.get()) : nullptr;
    }
};
