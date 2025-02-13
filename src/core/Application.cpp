#include "core/Application.hpp"

// Constructor: Initializes the application by reading the necessary files and setting up the boat's position
Application::Application()
{
    // Load all the reference points with GPS coordinates
    readFileAndInsertToNodes("../assets/all_points.txt", this->nodes);

    // Load the points that need to be validated
    readFileAndInsertToVector("../assets/test/points.txt", this->pointsToBeValidate);

    std::cout << pointsToBeValidate.size() << std::endl;

    // Initialize boat at position (1, 1)
    boat = new Object(Vector(1, 1));
}

// Read nodes (with GPS and position data) from a file and insert into the nodes vector
void Application::readFileAndInsertToNodes(const char* file, std::vector<Node*> &nodes)
{
    std::ifstream inputFile(file);  // Open the file for reading
    if (!inputFile) {
        std::cerr << "Could not open the file: " << file << std::endl;
        return;
    }
    
    float x, y;
    double lat, lon;

    // Read each line in the file
    while (inputFile >> lat >> lon >> x >> y) {
        Node* tempNode = new Node(Vector(x, y));
        tempNode->setGPSPosition(Vector(lat, lon));
        nodes.emplace_back(tempNode);
    }
}

// Read points to be validated from a file and insert into the points vector
void Application::readFileAndInsertToVector(const char* file, std::vector<Vector> &points)
{
    std::ifstream inputFile(file);  // Open the file for reading
    if (!inputFile) 
    {
        std::cerr << "Could not open the file: " << file << std::endl;
        return;
    }

    float x, y;
    while(inputFile >> x >> y)
    {
        points.emplace_back(Vector(x, y));
    }
}

// Destructor
Application::~Application()
{
}

// Validate positions and generate a CSV report
void Application::validatePositions() {
    std::cout << "===== Validating =====" << std::endl;
    std::cout << "===== Creating .csv File =====" << std::endl;

    std::string filename = "../output/output.csv";
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    // Write header to CSV file
    file << "ID,Image Position,,Actual GPS,,Interpolated GPS,,Error Distance,nearest point 1,,nearest point 2,,nearest point 3\n";
    file << ",x,y,lat,lon,lat,lon,meters, x,y,x,y,x,y\n";

    // Start timing the validation process
    auto start = std::chrono::high_resolution_clock::now();

    Vector lastPos = boat->getPosition();
    std::vector<std::vector<std::string>> CSVdata;
    std::vector<double> distances;
    this->errorPoints.clear();
    int id = 0;
    distances.clear();
    CSVdata.clear();

    // Iterate through each point to be validated
    for (Vector& point : this->pointsToBeValidate) {
        Node* node = nullptr; // Initialize the node pointer to nullptr

        // Find the corresponding node from the nodes list based on position
        auto it = std::find_if(nodes.begin(), nodes.end(), [&](const Node* nodePtr) {
            return nodePtr->getPosition() == point;
        });

        // If node is found, create a copy of it and remove the original from the list
        if (it != nodes.end()) {
            node = new Node((*it)->getPosition());
            node->setGPSPosition((*it)->getGPSPosition());

            delete *it; // Free memory of original node
            nodes.erase(it); // Remove the node from the vector
        }

        if (!node) {
            std::cerr << "Node not found for the given point!" << std::endl;
            continue; // Skip this iteration if no node was found
        }

        Node* nodeCopy = new Node(node->getPosition());
        nodeCopy->setGPSPosition(node->getGPSPosition());

        this->boat->setPosition(point); // Set the boat's current position
        this->nearestNodes.clear(); // Clear the nearest nodes vector before using it

        // Calculate distances from the boat's position to all other nodes
        std::vector<std::pair<Node*, double>> dists;
        for (Node* loopNode : nodes) {
            double distance = loopNode->getPosition().distanceTo(this->boat->getPosition());
            dists.emplace_back(loopNode, distance);
        }

        // Sort the nodes by distance from the boat
        std::sort(dists.begin(), dists.end(), [](const auto& a, const auto& b) {
            return a.second < b.second; // Compare distances
        });

        // Select the nearest 10 nodes (or fewer if less are available)
        for (int i = 0; i < 10 && i < dists.size(); ++i) {
            this->nearestNodes.push_back(dists[i].first);
        }

        if (this->nearestNodes.size() < 3) {
            std::cerr << "Not enough nearest nodes found!" << std::endl;
            continue; // Skip this iteration if not enough nodes were found
        }

        // Perform barycentric interpolation using 3 nearest nodes
        this->boat->barycentric_interpolation(nearestNodes[0], nearestNodes[1], nearestNodes[2]);

        // Perform Inverse Distance Weighting interpolation
        this->boat->idw_interpolation(this->nearestNodes);

        // Calculate error distance using haversine formula
        double dis = haversine(nodeCopy->getGPSPosition(), this->boat->getActualGPSPosition());

        // Re-insert the node back into the nodes vector
        this->nodes.emplace_back(nodeCopy);

        if (std::isnan(dis)) {
            std::cout << "Error in interpolation, nearest nodes count: " << nearestNodes.size() << std::endl;
        }

        // Prepare the data for CSV output
        std::vector<std::string> data= {
            std::to_string(id), 
            std::to_string((int)(point.x)), std::to_string((int)(point.y)), 
            std::to_string(nodeCopy->getGPSPosition().x), std::to_string(nodeCopy->getGPSPosition().y),
            std::to_string(this->boat->getActualGPSPosition().x), std::to_string(this->boat->getActualGPSPosition().y),
            std::to_string(dis),
            std::to_string((int)(nearestNodes[0]->getPositionX())), std::to_string((int)(nearestNodes[0]->getPositionY())),
            std::to_string((int)(nearestNodes[1]->getPositionX())), std::to_string((int)(nearestNodes[1]->getPositionY())),
            std::to_string((int)(nearestNodes[2]->getPositionX())), std::to_string((int)(nearestNodes[2]->getPositionY()))
        };
        id++; // Increment ID for each point
        CSVdata.emplace_back(data);
        errorPoints.emplace_back(point, dis);
        distances.emplace_back(dis);
    }

    // Calculate statistics for the errors
    double m = mean(distances);
    double v = variance(distances);
    double sDeviation = standardDeviation(distances);
    std::pair<Vector, double> hError = highestError(errorPoints);
    std::pair<Vector, double> lError = lowestError(errorPoints);

    // Write the data rows to the CSV file
    for (const auto& row : CSVdata) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) {
                file << ",";
            }
        }
        file << "\n";  // Newline after each row
    }
    
    // Write the error statistics to the CSV file
    file << ",\n";
    file << ",Mean error," + std::to_string(m) + "\n";
    file << ",Variance," + std::to_string(v)+ "\n";
    file << ",Standard Deviation," + std::to_string(sDeviation)+ "\n";
    file << ",\n";
    file << ", Highest Error, Position X, Position Y\n";
    file << "," <<std::to_string(hError.second) + "," + std::to_string((int)(hError.first.x)) + "," + std::to_string(hError.first.y) + ",\n";
    file << ",\n";
    file << ", Lowest Error, Position X, Position Y\n";
    file << "," << std::to_string(lError.second) + "," + std::to_string((int)(lError.first.x)) + "," + std::to_string(lError.first.y) + ",\n";
    file.close(); // Close the file

    // End timing and print elapsed time
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "===== CSV file created successfully: "<< filename  << " ======" << std::endl;
    std::cout << "===== Time taken: " << elapsed.count() << "s =====" << std::endl;

    // Restore the boat's original position
    this->boat->setPosition(lastPos);
}
