#include "Graph.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

// Private helper methods
int Graph::getCityIndex(const City& city) const {
    auto it = std::find_if(cities.begin(), cities.end(),
        [&city](const City& c) { return c == city; });
    return it != cities.end() ? std::distance(cities.begin(), it) : -1;
}

void Graph::resizeMatrices() {
    size_t size = cities.size();
    roadMatrix.resize(size, std::vector<int>(size, 0));
    budgetMatrix.resize(size, std::vector<double>(size, 0.0));
}

// Constructors
Graph::Graph() {}

Graph::Graph(const std::vector<City>& cityList) : cities(cityList) {
    resizeMatrices();
}

// City management
void Graph::addCity(const City& city) {
    if (!hasCity(city)) {
        cities.push_back(city);
        resizeMatrices();
    }
}

void Graph::removeCity(const City& city) {
    int index = getCityIndex(city);
    if (index != -1) {
        cities.erase(cities.begin() + index);
        resizeMatrices();
    }
}

bool Graph::hasCity(const City& city) const {
    return getCityIndex(city) != -1;
}

std::vector<City> Graph::getCities() const {
    return cities;
}

// Road management
void Graph::addRoad(const Road& road) {
    int idx1 = getCityIndex(road.getCity1());
    int idx2 = getCityIndex(road.getCity2());
    
    if (idx1 != -1 && idx2 != -1) {
        roadMatrix[idx1][idx2] = 1;
        roadMatrix[idx2][idx1] = 1;
        budgetMatrix[idx1][idx2] = road.getBudget();
        budgetMatrix[idx2][idx1] = road.getBudget();
    }
}

void Graph::removeRoad(const Road& road) {
    int idx1 = getCityIndex(road.getCity1());
    int idx2 = getCityIndex(road.getCity2());
    
    if (idx1 != -1 && idx2 != -1) {
        roadMatrix[idx1][idx2] = 0;
        roadMatrix[idx2][idx1] = 0;
        budgetMatrix[idx1][idx2] = 0.0;
        budgetMatrix[idx2][idx1] = 0.0;
    }
}

bool Graph::hasRoad(const Road& road) const {
    int idx1 = getCityIndex(road.getCity1());
    int idx2 = getCityIndex(road.getCity2());
    
    return idx1 != -1 && idx2 != -1 && roadMatrix[idx1][idx2] == 1;
}

double Graph::getRoadBudget(const Road& road) const {
    int idx1 = getCityIndex(road.getCity1());
    int idx2 = getCityIndex(road.getCity2());
    
    return (idx1 != -1 && idx2 != -1) ? budgetMatrix[idx1][idx2] : 0.0;
}

void Graph::setRoadBudget(const Road& road, double budget) {
    int idx1 = getCityIndex(road.getCity1());
    int idx2 = getCityIndex(road.getCity2());
    
    if (idx1 != -1 && idx2 != -1) {
        budgetMatrix[idx1][idx2] = budget;
        budgetMatrix[idx2][idx1] = budget;
    }
}

// Matrix operations
std::vector<std::vector<int>> Graph::getRoadMatrix() const {
    return roadMatrix;
}

std::vector<std::vector<double>> Graph::getBudgetMatrix() const {
    return budgetMatrix;
}

void Graph::displayMatrices() const {
    // Display cities
    std::cout << "Cities:\n";
    for (size_t i = 0; i < cities.size(); ++i) {
        std::cout << i + 1 << ": " << cities[i].getName() << "\n";
    }
    std::cout << "\n";

    // Display road matrix
    std::cout << "Roads Adjacency Matrix:\n";
    for (const auto& row : roadMatrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    // Display budget matrix
    std::cout << "Budgets Adjacency Matrix:\n";
    for (const auto& row : budgetMatrix) {
        for (double val : row) {
            std::cout << std::fixed << std::setprecision(1) << val << " ";
        }
        std::cout << "\n";
    }
}

// Utility methods
size_t Graph::size() const {
    return cities.size();
}

void Graph::clear() {
    cities.clear();
    roadMatrix.clear();
    budgetMatrix.clear();
} 