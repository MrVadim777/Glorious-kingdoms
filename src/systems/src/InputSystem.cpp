#include "systems/include/InputSystem.h"
#include "components/DirectionComponent.h"


void InputSystem::update(Entity& entity) {
    Direction::Vertical&   verticalDir   = entity.get<DirectionComponent>()->vertical;
    Direction::Horizontal& horizontalDir = entity.get<DirectionComponent>()->horizontal;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        verticalDir = Direction::Vertical::UP;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        verticalDir = Direction::Vertical::DOWN;
    } else {
        verticalDir = Direction::Vertical::NONE;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        horizontalDir = Direction::Horizontal::RIGHT;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        horizontalDir = Direction::Horizontal::LEFT;
    } else {
        horizontalDir = Direction::Horizontal::NONE;
    }
}
