#pragma once
#include "../utils/Vector.hpp"

/**
 * @class Entity
 * Base class for objects with a position.
 */

class Entity
{
public:
    virtual ~Entity();  // Virtual destructor for proper cleanup

    Vector getPosition() const;  // Get the entity's position
    float getPositionX() const;  // Get X coordinate of position
    float getPositionY() const;  // Get Y coordinate of position
    void setPosition(Vector pos); // Set a new position

protected:
    Vector position;  // Stores the entity's position
};