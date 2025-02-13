#pragma once
#include <iostream>
#include "entities/Object.hpp"
#include <fstream>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>

/**
 * @class Application
 * main application
 * validation of positions and file handling.
 */
class Application
{
public:
    Application();  // Constructor
    ~Application(); // Destructor

    void validatePositions();  // Validates positions using interpolation

private:
    void readFileAndInsertToNodes(const char* file, std::vector<Node*> &nodes); // Reads node data from file
    void readFileAndInsertToVector(const char* file, std::vector<Vector> &points); // Reads vector data from file

private:
    std::vector<Vector> currentNodes;  // Stores current node positions
    std::vector<Node*> nodes;          // List of all nodes
    std::vector<Node*> validationNodes; // Nodes used for validation
    std::vector<Vector> pointsToBeValidate; // Points to be validated
    std::vector<std::pair<Vector, double>> errorPoints; // Stores error values for validation
    std::vector<Node*> nearestNodes;   // Stores nearest nodes for interpolation

    Object* boat = nullptr;  // Pointer to the boat object
};
