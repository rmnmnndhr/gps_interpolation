#include "core/entities/Object.hpp"

// Constructor: Initializes object with a given position
Object::Object(Vector pos)
{
    this->position = pos;
}

// Destructor
Object::~Object()
{

}

// Barycentric interpolation method to estimate GPS position based on three nearby nodes
bool Object::barycentric_interpolation(Node *n1, Node *n2, Node *n3)
{
    double x = this->position.x;
    double y = this->position.y;

    // Get positions of the nodes
    Vector p0 = n1->getPosition();
    double x0 = p0.x;
    double y0 = p0.y;
    Vector p1 = n2->getPosition();
    double x1 = p1.x;
    double y1 = p1.y;
    Vector p2 = n3->getPosition();
    double x2 = p2.x;
    double y2 = p2.y;
    Vector result;

    // Get GPS positions of the nodes
    Vector p0GPS = n1->getGPSPosition();
    Vector p1GPS = n2->getGPSPosition();
    Vector p2GPS = n3->getGPSPosition();

    // Calculate area (denominator)
    double A = (y1 - y2) * (x0 - x2) + (x2 - x1) * (y0 - y2);

    // Calculate barycentric coordinates
    double s = ((y1 - y2) * (x - x2) + (x2 - x1) * (y - y2)) / A;
    double t = ((y2 - y0) * (x - x2) + (x0 - x2) * (y - y2)) / A;
    double u = 1.0f - s - t;

    // Interpolated GPS position
    result.x = s * p0GPS.x + t * p1GPS.x + u * p2GPS.x;
    result.y = s * p0GPS.y + t * p1GPS.y + u * p2GPS.y;
    actualGPSPosition = result;

    // Check if the barycentric coordinates are within the valid range (triangle)
    return (s >= 0 && s <= 1) && (t >= 0 && t <= 1) && (u >= 0 && u <= 1);
}

// Bilinear interpolation method to estimate GPS position using four nodes
void Object::billinearInterpolation(Node *n1, Node *n2, Node *n3, Node *n4)
{
    double x = this->position.x;
    double y = this->position.y;

    // Get positions of the nodes
    Vector p0 = n1->getPosition();
    double x0 = p0.x;
    double y0 = p0.y;
    Vector p1 = n2->getPosition();
    double x1 = p1.x;
    double y1 = p1.y;
    Vector p2 = n3->getPosition();
    double x2 = p2.x;
    double y2 = p2.y;
    Vector p3 = n4->getPosition();
    double x3 = p3.x;
    double y3 = p3.y;

    // Interpolation along x-axis for top and bottom edges
    double topXper = (x - x0) / (x1 - x0);
    double topY = (y1 - y0) * topXper + y0;

    double bottomXper = (x - x2) / (x3 - x2);
    double bottomY = (y3 - y2) * bottomXper + y2;

    // Interpolate along y-axis
    double Yper = (y - bottomY) / (topY - bottomY);

    // Perform linear interpolation in both directions
    Vector top = lerp(n1->getGPSPosition(), n2->getGPSPosition(), topXper);
    Vector bottom = lerp(n3->getGPSPosition(), n4->getGPSPosition(), topXper);
    Vector result = lerp(top, bottom, topXper);

    // Set the final interpolated GPS position
    actualGPSPosition = result;
}

// Inverse Distance Weighting interpolation method for estimating GPS position
void Object::idw_interpolation(const std::vector<Node*>& nearestNodes) {
    double weightSum = 0.0;
    Vector interpolatedPosition(0.0, 0.0);  // For local position, modify if needed for GPS

    // Iterate over the nearest nodes
    for (const Node* node : nearestNodes) {
        double distance = haversine(node->getGPSPosition(), this->actualGPSPosition);  // Haversine distance
        if (distance > 0) {
            double weight = 1.0 / (distance * distance * distance);  // Weight inversely proportional to distance
            weightSum += weight;
            interpolatedPosition += node->getGPSPosition() * weight;  // Weighted sum of positions
        }
    }

    // Normalize the interpolated position by the total weight
    if (weightSum > 0) {
        interpolatedPosition /= weightSum;
    }

    // Set the final interpolated GPS position
    this->actualGPSPosition = interpolatedPosition;
}

// Returns the actual GPS position of the object
Vector Object::getActualGPSPosition()
{
    return actualGPSPosition;
}
