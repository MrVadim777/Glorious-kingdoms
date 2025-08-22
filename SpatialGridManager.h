#pragma once
#include <unordered_map>
#include <vector>
#include <cmath>
#include <algorithm>

#include "EntityId.h"

struct CellCoord {
    int x;
    int y;
};

inline bool operator==(const CellCoord& a, const CellCoord& b) {
    return a.x == b.x && a.y == b.y;
}

struct CellHash {
    size_t operator()(const CellCoord& c) const noexcept {
        return std::hash<long long>()(((long long)c.x << 32) ^ (unsigned)c.y);
    }
};

class SpatialGridManager {
  private:
    std::unordered_map<CellCoord, std::vector<EntityId>, CellHash> cells;
    float                                                          cellSize;

  public:
    SpatialGridManager(float cellSize = 64.f) : cellSize(cellSize) {
    }

    CellCoord toCellCoord(float x, float y) const {
        return {(int)std::floor(x / cellSize), (int)std::floor(y / cellSize)};
    }

    void insert(EntityId id, CellCoord cellCoord) {
        std::vector<EntityId>& cellVector = cells[cellCoord];
        cellVector.push_back(id);
    }

    void remove(EntityId id, CellCoord c) {
        auto it = cells.find(c);

        if (it == cells.end()) {
            return;
        }

        std::vector<EntityId>& cellVector = it->second;
        cellVector.erase(std::remove(cellVector.begin(), cellVector.end(), id), cellVector.end());

        if (cellVector.empty()) {
            cells.erase(it);
        }
    }

    void move(EntityId id, CellCoord from, CellCoord to) {
        if (from.x == to.x && from.y == to.y) {
            return;
        }

        remove(id, from);
        insert(id, to);
    }

    const std::vector<EntityId>* getCell(CellCoord c) const {
        auto it = cells.find(c);
        return (it == cells.end()) ? nullptr : &it->second;
    }

    const std::unordered_map<CellCoord, std::vector<EntityId>, CellHash>& getAllCells() const {
        return cells;
    }

    const float getCellSize() const {
        return cellSize;
    }

    void setCellSize(float cellSize) {
        this->cellSize = cellSize;
    }

    void clear() {
        cells.clear();
    }
};
