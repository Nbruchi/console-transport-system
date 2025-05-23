#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "City.h"
#include "Road.h"
#include "Graph.h"
#include "FileManager.h"

void displayMenu() {
    std::cout << "\nMenu:\n"
              << "1. Add new city(ies)\n"
              << "2. Add roads between cities\n"
              << "3. Add the budget for roads\n"
              << "4. Edit city\n"
              << "5. Search for a city using its index\n"
              << "6. Display cities\n"
              << "7. Display roads\n"
              << "8. Display recorded data on console\n"
              << "9. Exit\n"
              << "Enter your choice: ";
}

void addCities(Graph& graph, FileManager& fileManager) {
    int numCities;
    std::cout << "Enter the number of cities to add: ";
    std::cin >> numCities;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 0; i < numCities; ++i) {
        std::string name;
        std::cout << "Enter name for city " << i + 1 << ": ";
        std::getline(std::cin, name);
        graph.addCity(City(i + 1, name));
    }
    
    // Save after adding cities
    if (fileManager.saveGraph(graph)) {
        std::cout << "Cities added and saved successfully.\n";
    } else {
        std::cout << "Error saving cities to file.\n";
    }
}

void addRoad(Graph& graph, FileManager& fileManager) {
    std::string city1Name, city2Name;
    std::cout << "Enter the name of the first city: ";
    std::getline(std::cin, city1Name);
    std::cout << "Enter the name of the second city: ";
    std::getline(std::cin, city2Name);

    City city1(0, city1Name);
    City city2(0, city2Name);
    Road road(city1, city2);
    graph.addRoad(road);
    std::cout << "Road added between " << city1Name << " and " << city2Name << "\n";
    
    // Save after adding road
    if (fileManager.saveGraph(graph)) {
        std::cout << "Road information saved successfully.\n";
    } else {
        std::cout << "Error saving road information to file.\n";
    }
}

void addRoadBudget(Graph& graph, FileManager& fileManager) {
    std::string city1Name, city2Name;
    double budget;
    std::cout << "Enter the name of the first city: ";
    std::getline(std::cin, city1Name);
    std::cout << "Enter the name of the second city: ";
    std::getline(std::cin, city2Name);
    std::cout << "Enter the budget for the road: ";
    std::cin >> budget;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    City city1(0, city1Name);
    City city2(0, city2Name);
    Road road(city1, city2);
    graph.setRoadBudget(road, budget);
    std::cout << "Budget added for the road between " << city1Name << " and " << city2Name << "\n";
    
    // Save after adding budget
    if (fileManager.saveGraph(graph)) {
        std::cout << "Budget information saved successfully.\n";
    } else {
        std::cout << "Error saving budget information to file.\n";
    }
}

void editCity(Graph& graph, FileManager& fileManager) {
    int index;
    std::string newName;
    std::cout << "Enter the index of the city to edit: ";
    std::cin >> index;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter new name for city: ";
    std::getline(std::cin, newName);

    std::vector<City> cities = graph.getCities();
    if (index > 0 && index <= static_cast<int>(cities.size())) {
        City city(index, newName);
        graph.removeCity(cities[index - 1]);
        graph.addCity(city);
        std::cout << "City updated successfully.\n";
        
        // Save after editing city
        if (fileManager.saveGraph(graph)) {
            std::cout << "City information saved successfully.\n";
        } else {
            std::cout << "Error saving city information to file.\n";
        }
    } else {
        std::cout << "Invalid city index.\n";
    }
}

void searchCity(const Graph& graph) {
    int index;
    std::cout << "Enter the index of the city to search: ";
    std::cin >> index;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<City> cities = graph.getCities();
    if (index > 0 && index <= static_cast<int>(cities.size())) {
        std::cout << "City found: " << cities[index - 1].getName() << "\n";
    } else {
        std::cout << "City not found.\n";
    }
}

void displayCities(const Graph& graph) {
    std::cout << "Cities:\n";
    std::vector<City> cities = graph.getCities();
    for (size_t i = 0; i < cities.size(); ++i) {
        std::cout << i + 1 << ": " << cities[i].getName() << "\n";
    }
}

void displayRoads(const Graph& graph) {
    graph.displayMatrices();
}

int main() {
    Graph graph;
    FileManager fileManager;
    
    // Try to load existing data
    if (fileManager.loadGraph(graph)) {
        std::cout << "Existing data loaded successfully.\n";
    } else {
        std::cout << "No existing data found or error loading data.\n";
    }

    while (true) {
        displayMenu();
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                addCities(graph, fileManager);
                break;
            case 2:
                addRoad(graph, fileManager);
                break;
            case 3:
                addRoadBudget(graph, fileManager);
                break;
            case 4:
                editCity(graph, fileManager);
                break;
            case 5:
                searchCity(graph);
                break;
            case 6:
                displayCities(graph);
                break;
            case 7:
                displayRoads(graph);
                break;
            case 8:
                graph.displayMatrices();
                break;
            case 9:
                // Save data before exiting
                if (fileManager.saveGraph(graph)) {
                    std::cout << "All data saved successfully.\n";
                } else {
                    std::cout << "Error saving data before exit.\n";
                }
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
} 