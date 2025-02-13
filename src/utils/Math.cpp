#include "utils/Math.hpp"

Vector lerp(Vector A, Vector B, double t)
{
    float x = A.x + t * (B.x - A.x);
    float y = A.y + t * (B.y - A.y);

    return Vector(x, y);
}


float area_of_triangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    return 0.5 * std::abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
}

// Function to calculate the mean
double mean(const std::vector<double>& numbers) {
    if (numbers.empty()) {
        std::cerr << "Error: Cannot calculate mean of an empty vector." << std::endl;
        return 0.0;  // Or consider throwing an exception
    }

    double total = 0;
    for (double number : numbers) {
        total += number;
    }

    return total / numbers.size();
}

bool compareNodes(Node* a, Node* b) {
    return a->getPosition().x < b->getPosition().x;
}


// Function to calculate the variance
double variance(const std::vector<double>& numbers) {
    int total_numbers = numbers.size();

    if (total_numbers < 2) {
        std::cerr << "Error: Need at least two numbers to calculate variance." << std::endl;
        return 0.0;  // Or consider throwing an exception
    }

    double m = mean(numbers);
    double var = 0;
    for (double number : numbers) {
        var += (number - m) * (number - m);
    }

    return var / (total_numbers - 1);  // Sample variance, use total_numbers for population variance
}

// Function to calculate the standard deviation
double standardDeviation(const std::vector<double>& numbers) {
    if (numbers.empty()) {
        std::cerr << "Error: Cannot calculate standard deviation of an empty vector." << std::endl;
        return 0.0;  // Or consider throwing an exception
    }

    return std::sqrt(variance(numbers));
}

std::pair<Vector, double> highestError(std::vector<std::pair<Vector, double>>& errors) 
{
    std::pair<Vector, double> point;
    double d=0;
    for(auto& error: errors)
    {
        if(error.second > d)
        {
            d = error.second;
            point = error;
        }
    }
    return point;
}


std::pair<Vector, double> lowestError(std::vector<std::pair<Vector, double>>& errors) 
{
    std::pair<Vector, double> point;
    double d = INFINITY;
    for(auto& error: errors)
    {
        if(error.second < d)
        {
            d = error.second;
            point = error;
        }
    }
    return point;
}

double map(double t, double i1, double i2, double o1, double o2)
{
    double p = (o2 - o1) / (i2 - i1);
    return o1 + p * (t-i1);
}

// Convert degrees to radians
double toRadians(double degree) {
    return degree * (M_PI / 180.0);
}


// Haversine formula to calculate the distance between two GPS coordinates
double haversine(Vector v1, Vector v2) {
    double lat1 = v1.x;
    double lon1 = v1.y;
    double lat2 = v2.x;
    double lon2 = v2.y;

    double dLat = toRadians(lat2-lat1);
    double dLon = toRadians(lon2-lon1);

    lat1 = toRadians(lat1);
    lat2 = toRadians(lat2);

    double a = sin(dLat/2) * sin(dLat/2) +
            sin(dLon/2) * sin(dLon/2) * cos(lat1) * cos(lat2); 
    double c = 2 * atan2(sqrt(a), sqrt(1-a)); 
    
    return 6371000.0 * c; // Distance in kilometers
}

