#include "systems/include/NpcAISystem.h"
#include "components/DirectionComponent.h"
#include "components/PositionComponent.h"

void NpcAISystem::update(Entity* player, std::vector<Entity*> entities) {
    for (auto entity : entities) {
        PositionComponent*  playerPos    = player->get<PositionComponent>();
        PositionComponent*  npcPos       = entity->get<PositionComponent>();
        DirectionComponent* npcDirection = entity->get<DirectionComponent>();

        if (npcPos->x < playerPos->x && npcPos->x - playerPos->x < -50.f) {
            npcDirection->horizontal = Direction::Horizontal::RIGHT;
        } else if (npcPos->x > playerPos->x && npcPos->x - playerPos->x > 50.f) {
            npcDirection->horizontal = Direction::Horizontal::LEFT;
        } else {
            npcDirection->horizontal = Direction::Horizontal::NONE;
        }

        if (npcPos->y > playerPos->y && npcPos->y - playerPos->y > 50.f) {
            npcDirection->vertical = Direction::Vertical::UP;
        } else if (npcPos->y < playerPos->y && npcPos->y - playerPos->y < -50.f) {
            npcDirection->vertical = Direction::Vertical::DOWN;
        } else {
            npcDirection->vertical = Direction::Vertical::NONE;
        }
    }
}
