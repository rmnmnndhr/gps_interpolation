#pragma once
#include <iostream>


/**
 * @class Vector
 * Represents a 2D vector with basic mathematical operations.
 */

class Vector
{
public:
    // Constructor with x and y values
    Vector(double x, double y);

    // Default constructor (sets to (0,0))
    Vector();

    // Destructor
    ~Vector();

    // Add two vectors and return a new vector
    Vector operator+(const Vector& otherVector) const;

    // Add another vector to this vector
    Vector& operator+=(const Vector& other);

    // Divide the vector by a scalar
    Vector& operator/=(double scalar);

    // Subtract two vectors and return a new vector
    Vector operator-(Vector &otherVector) const;

    // Check if two vectors are equal
    bool operator==(Vector &otherVector);

    // Divide the vector by a scalar and return a new vector
    Vector operator/(double scalar) const;

    // Multiply the vector by a scalar and return a new vector
    Vector operator*(double scalar) const;

    // Calculate squared distance to another vector
    double squaredDistanceTo(const Vector& other);

    // Calculate distance to another vector
    double distanceTo(const Vector &other);

    // Normalize the vector (make it unit length)
    Vector normalize();

    // Access vector elements by index (0 for x, 1 for y)
    double operator[](double index);

public:
    double x;  // X-coordinate
    double y;  // Y-coordinate
};
