#ifndef CITY_H
#define CITY_H

#include <string>

class City {
private:
    int index;
    std::string name;

public:
    // Constructors
    City();
    City(int idx, const std::string& cityName);

    // Getters
    int getIndex() const;
    std::string getName() const;

    // Setters
    void setIndex(int idx);
    void setName(const std::string& cityName);

    // Utility methods
    bool operator==(const City& other) const;
    bool operator!=(const City& other) const;
};

#endif // CITY_H 