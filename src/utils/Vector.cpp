#include "utils/Vector.hpp"

Vector::Vector(double x, double y)
{
    this->x = x;
    this->y = y;
}

Vector::Vector()
{
    this->x = std::numeric_limits<float>::lowest();
    this->y = std::numeric_limits<float>::lowest();
}

Vector::~Vector()
{
}

Vector Vector::operator+(const Vector& otherVector) const {
    return Vector{x + otherVector.x, y + otherVector.y};

}

Vector& Vector::operator+=(const Vector& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector& Vector::operator/=(double scalar) {
    if (scalar != 0) {
        x /= scalar;
        y /= scalar;
    } else {
        
        std::cerr << "Division by zero error in Vector operator/=" << std::endl;
        x = 0;
        y = 0;
    }
    return *this;
}


Vector Vector::operator-(Vector &otherVector) const
{
    float newX = this->x - otherVector.x;
    float newY = this->y - otherVector.y;
    return Vector(newX, newY);
}

Vector Vector::operator/(double scalar) const {
        return Vector{x / scalar, y / scalar}; 
    }

Vector Vector::operator*(double scalar) const {
    return Vector{x * scalar, y * scalar}; 
}

bool Vector::operator==(Vector &otherVector)
{
    return (this->x == otherVector.x && this->y == otherVector.y);
}

double Vector::squaredDistanceTo(const Vector &other)
{
    return (this->x - other.x)*(this->x - other.x) + (this->y - other.y)*(this->y - other.y);
}

double Vector::distanceTo(const Vector &other)
{
    return sqrt((this->x - other.x)*(this->x - other.x) + (this->y - other.y)*(this->y - other.y));
}


Vector Vector::normalize()
{
    float distance = sqrt((this->x * this->x) + (this->y * this->y));
    float newX = this->x / distance;
    float newY = this->y / distance;
    return Vector(newX, newY);

}

double Vector::operator[](double index)
{
    if (index == 0)
        return x;
    else if (index == 1)
        return y;
    else
        std::cout << "Index out of range" << std::endl;
        return 0.0;
}
