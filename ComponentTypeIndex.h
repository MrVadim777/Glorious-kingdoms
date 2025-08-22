#pragma once
#include <cstddef>

inline size_t                nextComponentIndex = 0;
template <typename T> size_t getComponentIndex() {
    static size_t index = nextComponentIndex++;
    return index;
}