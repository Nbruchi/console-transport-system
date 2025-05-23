#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include "City.h"
#include "Road.h"

class Graph {
private:
    std::vector<City> cities;
    std::vector<std::vector<int>> roadMatrix;
    std::vector<std::vector<double>> budgetMatrix;

    // Helper methods
    int getCityIndex(const City& city) const;
    void resizeMatrices();

public:
    // Constructors
    Graph();
    explicit Graph(const std::vector<City>& cityList);

    // City management
    void addCity(const City& city);
    void removeCity(const City& city);
    bool hasCity(const City& city) const;
    std::vector<City> getCities() const;

    // Road management
    void addRoad(const Road& road);
    void removeRoad(const Road& road);
    bool hasRoad(const Road& road) const;
    double getRoadBudget(const Road& road) const;
    void setRoadBudget(const Road& road, double budget);

    // Matrix operations
    std::vector<std::vector<int>> getRoadMatrix() const;
    std::vector<std::vector<double>> getBudgetMatrix() const;
    void displayMatrices() const;

    // Utility methods
    size_t size() const;
    void clear();
};

#endif // GRAPH_H 