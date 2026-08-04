#pragma once
#include <vector>
#include "EntityId.h"

struct PerceptionComponent {
    int                     radius = 1;
    std::vector<EntityId>   nearbyEntities;
    std::vector<CellCoord>  scannedCells; // Временно для дебага
};