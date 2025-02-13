#include "core/Entity.hpp"

// Destructor: No special cleanup is needed since no dynamic memory is allocated here
Entity::~Entity()
{
}

// Returns the entity's position as a Vector
Vector Entity::getPosition() const
{
    return this->position;
}

// Returns the X coordinate of the entity's position
float Entity::getPositionX() const
{
    return this->position.x;
}

// Returns the Y coordinate of the entity's position
float Entity::getPositionY() const
{
    return this->position.y;
}

// Sets the entity's position to the given Vector
void Entity::setPosition(Vector pos)
{
    this->position = pos;
}
