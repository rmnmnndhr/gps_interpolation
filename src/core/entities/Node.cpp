#include "core/entities/Node.hpp"

// Constructor: Initializes node with a given position
Node::Node(Vector pos)
{
    this->position = pos;
}

// Sets the GPS position of the node
void Node::setGPSPosition(Vector pos) 
{
    this->GPSPosition = pos;
}

// Returns the GPS position of the node
Vector Node::getGPSPosition() const
{
    return this->GPSPosition;
}
