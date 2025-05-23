#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>
#include "City.h"
#include "Road.h"
#include "Graph.h"

class FileManager {
private:
    std::string citiesFile;
    std::string roadsFile;

public:
    // Constructors
    FileManager();
    FileManager(const std::string& citiesPath, const std::string& roadsPath);

    // File operations
    bool saveCities(const std::vector<City>& cities);
    bool saveRoads(const std::vector<Road>& roads);
    bool loadCities(std::vector<City>& cities);
    bool loadRoads(std::vector<Road>& roads);
    
    // Graph operations
    bool saveGraph(const Graph& graph);
    bool loadGraph(Graph& graph);

    // Utility methods
    void setCitiesFile(const std::string& path);
    void setRoadsFile(const std::string& path);
    std::string getCitiesFile() const;
    std::string getRoadsFile() const;
};

#endif // FILE_MANAGER_H 