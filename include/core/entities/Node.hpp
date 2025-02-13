#pragma once
#include "../Entity.hpp"



/**
 * @class Node
 * node with a position and GPS coordinates.
 * 
 * This class extends Entity.
 * It also supports a KD-tree structure for efficient searching. Buggy
 */

class Node: public Entity
{
public:
    Node(Vector pos);  // Constructor

    void setGPSPosition(Vector pos);  // Set GPS coordinates
    Vector getGPSPosition() const;    // Get GPS coordinates

    Node* left;   // KD-tree left child
    Node* right;  // KD-tree right child

private:
    Vector GPSPosition;  // Stores GPS position
};
