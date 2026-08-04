#pragma once
#include <unordered_map>
#include <vector>
#include <cmath>
#include <algorithm>

#include "EntityId.h"

/// Координата клетки в spatial grid.
///
/// Это не позиция в пикселях, а индекс клетки.
/// Например, мировая позиция `{130, 70}` при `cellSize = 64`
/// будет соответствовать клетке `{2, 1}`.
struct CellCoord {
    int x;
    int y;
};

/// Сравнивает две координаты клеток.
///
/// Нужен unordered_map, чтобы понимать,
/// когда два CellCoord указывают на одну и ту же клетку.
inline bool operator==(const CellCoord& a, const CellCoord& b) {
    return a.x == b.x && a.y == b.y;
}

/// Хэш-функция для CellCoord.
///
/// Нужна unordered_map, чтобы использовать CellCoord как ключ.
/// Превращает пару координат x/y в одно число для быстрого поиска.
struct CellHash {
    size_t operator()(const CellCoord& c) const noexcept {
        return std::hash<long long>()(((long long)c.x << 32) ^ (unsigned)c.y);
    }
};

/// Управляет разреженной spatial-сеткой.
///
/// Хранит только занятые клетки:
/// `CellCoord -> список EntityId`.
///
/// Используется для быстрого поиска сущностей в конкретной клетке,
/// без перебора всех сущностей в мире.
class SpatialGridManager {
  private:
    std::unordered_map<CellCoord, std::vector<EntityId>, CellHash> cells;
    float                                                          cellSize;

  public:
    SpatialGridManager(float cellSize) : cellSize(cellSize) {
    }

    /// Переводит мировую позицию в координату клетки.
    ///
    /// @param x Позиция по X в мировых пикселях.
    /// @param y Позиция по Y в мировых пикселях.
    /// @return Координата клетки, в которой находится эта позиция.
    CellCoord toCellCoord(float x, float y) const {
        return {(int)std::floor(x / cellSize), (int)std::floor(y / cellSize)};
    }

    /// Положить сущность в вектор ячейки.
    /// 
    /// Из мапы [cells] достаётся ссылка на вектор [EntityId] по индексу ячейки [cell], и в вектор кладётся [id].
    /// 
    /// @param id - id сущности.
    /// @param cell - индекс ячейки.
    void insert(EntityId id, CellCoord cell) {
        std::vector<EntityId>& cellVector = cells[cell];
        cellVector.push_back(id);
    }

    /// Добавляет сущность в указанную клетку.
    ///
    /// Если клетки ещё нет в `cells`, она будет создана автоматически.
    ///
    /// @param id ID сущности.
    /// @param cell Координата клетки, куда добавляется сущность.
    void remove(EntityId id, CellCoord cell) {
        auto it = cells.find(cell);

        if (it == cells.end()) {
            return;
        }

        std::vector<EntityId>& cellVector = it->second;
        cellVector.erase(std::remove(cellVector.begin(), cellVector.end(), id), cellVector.end());

        if (cellVector.empty()) {
            cells.erase(it);
        }
    }

    /// Перемещает сущность из одной клетки в другую.
    ///
    /// Если `from` и `to` указывают на одну и ту же клетку,
    /// метод ничего не делает.
    ///
    /// @param id ID сущности.
    /// @param from Клетка, из которой нужно удалить сущность.
    /// @param to Клетка, в которую нужно добавить сущность.
    void move(EntityId id, CellCoord from, CellCoord to) {
        if (from.x == to.x && from.y == to.y) {
            return;
        }

        remove(id, from);
        insert(id, to);
    }

    /// Возвращает список сущностей в указанной клетке.
    ///
    /// Если клетки нет в `cells`, значит она пустая,
    /// и метод возвращает `nullptr`.
    ///
    /// @param cell Координата клетки.
    /// @return Указатель на список EntityId или nullptr, если клетка пустая.
    const std::vector<EntityId>* getCell(CellCoord cell) const {
        auto it = cells.find(cell);
        return (it == cells.end()) ? nullptr : &it->second;
    }

    /// Возвращает все занятые клетки.
    ///
    /// Используется, например, debug-отрисовкой сетки.
    ///
    /// @return Const-ссылка на map занятых клеток.
    const std::unordered_map<CellCoord, std::vector<EntityId>, CellHash>& getAllCells() const {
        return cells;
    }

    /// Возвращает размер одной клетки в мировых пикселях.
    ///
    /// @return Размер клетки.
    float getCellSize() const {
        return cellSize;
    }

    
    /// Устанавливает новый размер клетки.
    ///
    /// Важно: метод не пересчитывает уже существующие клетки.
    /// После изменения размера нужно заново заполнить spatial grid.
    ///
    /// @param cellSize Новый размер клетки в мировых пикселях.
    void setCellSize(float cellSize) {
        this->cellSize = cellSize;
    }

    /// Полностью очищает spatial grid.
    ///
    /// После вызова все связи `клетка -> сущности` будут удалены.
    void clear() {
        cells.clear();
    }
};
