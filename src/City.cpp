#include "City.h"

// Constructors
City::City() : index(0), name("") {}

City::City(int idx, const std::string& cityName) : index(idx), name(cityName) {}

// Getters
int City::getIndex() const {
    return index;
}

std::string City::getName() const {
    return name;
}

// Setters
void City::setIndex(int idx) {
    index = idx;
}

void City::setName(const std::string& cityName) {
    name = cityName;
}

// Utility methods
bool City::operator==(const City& other) const {
    return index == other.index && name == other.name;
}

bool City::operator!=(const City& other) const {
    return !(*this == other);
} 