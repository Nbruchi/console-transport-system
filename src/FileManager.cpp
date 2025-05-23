#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>

// Constructors
FileManager::FileManager() 
    : citiesFile("data/cities.txt"), roadsFile("data/roads.txt") {
    // Create data directory if it doesn't exist
    std::filesystem::create_directories("data");
}

FileManager::FileManager(const std::string& citiesPath, const std::string& roadsPath)
    : citiesFile(citiesPath), roadsFile(roadsPath) {
    // Create parent directory if it doesn't exist
    std::filesystem::create_directories(std::filesystem::path(citiesPath).parent_path());
}

// File operations
bool FileManager::saveCities(const std::vector<City>& cities) {
    std::ofstream file(citiesFile);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << citiesFile << " for writing\n";
        return false;
    }

    file << "Index\tCity name\n";
    for (const auto& city : cities) {
        file << city.getIndex() << "\t" << city.getName() << "\n";
    }
    file.close();
    std::cout << "Cities saved to " << citiesFile << "\n";
    return true;
}

bool FileManager::saveRoads(const std::vector<Road>& roads) {
    std::ofstream file(roadsFile);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << roadsFile << " for writing\n";
        return false;
    }

    file << "Nbr\tRoad\tBudget\n";
    int count = 1;
    for (const auto& road : roads) {
        file << count++ << "\t"
             << road.getCity1().getName() << " - " << road.getCity2().getName() << "\t"
             << road.getBudget() << "\n";
    }
    file.close();
    std::cout << "Roads saved to " << roadsFile << "\n";
    return true;
}

bool FileManager::loadCities(std::vector<City>& cities) {
    std::ifstream file(citiesFile);
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open file " << citiesFile << " for reading\n";
        return false;
    }

    std::string line;
    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int index;
        std::string name;
        if (iss >> index >> name) {
            cities.emplace_back(index, name);
        }
    }
    file.close();
    return true;
}

bool FileManager::loadRoads(std::vector<Road>& roads) {
    std::ifstream file(roadsFile);
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open file " << roadsFile << " for reading\n";
        return false;
    }

    std::string line;
    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int nbr;
        std::string city1Name, city2Name, dash;
        double budget;
        
        if (iss >> nbr >> city1Name >> dash >> city2Name >> budget) {
            City city1(0, city1Name);
            City city2(0, city2Name);
            roads.emplace_back(city1, city2, budget);
        }
    }
    file.close();
    return true;
}

bool FileManager::saveGraph(const Graph& graph) {
    std::vector<City> cities = graph.getCities();
    if (!saveCities(cities)) {
        return false;
    }

    std::vector<Road> roads;
    for (size_t i = 0; i < cities.size(); ++i) {
        for (size_t j = i + 1; j < cities.size(); ++j) {
            Road road(cities[i], cities[j]);
            if (graph.hasRoad(road)) {
                road.setBudget(graph.getRoadBudget(road));
                roads.push_back(road);
            }
        }
    }
    return saveRoads(roads);
}

bool FileManager::loadGraph(Graph& graph) {
    std::vector<City> cities;
    if (!loadCities(cities)) {
        return false;
    }

    for (const auto& city : cities) {
        graph.addCity(city);
    }

    std::vector<Road> roads;
    if (!loadRoads(roads)) {
        return false;
    }

    for (const auto& road : roads) {
        graph.addRoad(road);
    }
    return true;
}

// Utility methods
void FileManager::setCitiesFile(const std::string& path) {
    citiesFile = path;
    // Create parent directory if it doesn't exist
    std::filesystem::create_directories(std::filesystem::path(path).parent_path());
}

void FileManager::setRoadsFile(const std::string& path) {
    roadsFile = path;
    // Create parent directory if it doesn't exist
    std::filesystem::create_directories(std::filesystem::path(path).parent_path());
}

std::string FileManager::getCitiesFile() const {
    return citiesFile;
}

std::string FileManager::getRoadsFile() const {
    return roadsFile;
}