#include "Road.h"

// Constructors
Road::Road() : budget(0.0) {}

Road::Road(const City& c1, const City& c2, double roadBudget)
    : city1(c1), city2(c2), budget(roadBudget) {}

// Getters
City Road::getCity1() const {
    return city1;
}

City Road::getCity2() const {
    return city2;
}

double Road::getBudget() const {
    return budget;
}

// Setters
void Road::setCity1(const City& c1) {
    city1 = c1;
}

void Road::setCity2(const City& c2) {
    city2 = c2;
}

void Road::setBudget(double roadBudget) {
    budget = roadBudget;
}

// Utility methods
bool Road::connects(const City& city) const {
    return city1 == city || city2 == city;
}

bool Road::operator==(const Road& other) const {
    return (city1 == other.city1 && city2 == other.city2) ||
           (city1 == other.city2 && city2 == other.city1);
}

bool Road::operator!=(const Road& other) const {
    return !(*this == other);
} 