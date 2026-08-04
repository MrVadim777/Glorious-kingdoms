#pragma once

struct Coord {
    int x;
    int y;
};

class Location {
    Coord coord = {0, 0};

    int widthInCells  = 20;
    int heightInCells = 20;

    const float cellSize = 64.f;

  public:
    float getCellSize() const {
        return cellSize;
    }

    int getWidthInCells() const {
        return widthInCells;
    }

    int getHeightInCells() const {
        return heightInCells;
    }

    float getWidthPixels() const {
        return widthInCells * cellSize;
    }

    float getHeightPixels() const {
        return heightInCells * cellSize;
    }
};