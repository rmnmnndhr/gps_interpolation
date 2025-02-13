#pragma once

#include "Vector.hpp"
#include <array>
#include <vector>
#include <cmath>
#include <utility>
#include "../core/entities/Node.hpp"

// performs linear interpolation between two vectors.
Vector lerp(Vector A, Vector B, double t);

// Calculates the mean (average) of a set of numbers.
double mean(const std::vector<double> &numbers);

// Computes the area of a triangle given three points.
float area_of_triangle(float x1, float y1, float x2, float y2, float x3, float y3);

// Computes the variance of a set of numbers.
double variance(const std::vector<double> &numbers);

// Computes the standard deviation of a set of numbers.
double standardDeviation(const std::vector<double> &numbers);

// Finds the highest error from a list of errors.
std::pair<Vector, double> highestError(std::vector<std::pair<Vector, double>>& errors);

// Finds the lowest error from a list of errors.
std::pair<Vector, double> lowestError(std::vector<std::pair<Vector, double>>& errors);

// Maps a value from one range to another.
double map(double t, double i1, double i2, double o1, double o2);

// Computes the Haversine distance between two geographic points.
double haversine(Vector a, Vector b);

// Compares two nodes based on their positions.
bool compareNodes(Node* a, Node* b);
