#pragma once 

#include <iomanip>
#include "../Entity.hpp"
#include "Node.hpp"
#include "../../utils/Math.hpp" 
#include <sstream>
#include <string>

/**
 * @class Object
 * Represents an object with position and interpolation methods.
 */

class Object: public Entity
{
public:
    Object(Vector pos);  // Constructor
    ~Object();  // Destructor

    bool barycentric_interpolation(Node *n1, Node *n2, Node *n3);  // Barycentric interpolation
    void billinearInterpolation(Node *n1, Node *n2, Node *n3, Node *n4);  // Bilinear interpolation
    void idw_interpolation(const std::vector<Node*>& nearestNodes);  // Inverse Distance Weighting (IDW) interpolation
    
    Vector getActualGPSPosition();  // Get actual GPS position

private:
    Vector actualGPSPosition;  // Stores interpolated GPS position
};
