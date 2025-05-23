#ifndef ROAD_H
#define ROAD_H

#include "City.h"

class Road {
private:
    City city1;
    City city2;
    double budget;

public:
    // Constructors
    Road();
    Road(const City& c1, const City& c2, double roadBudget = 0.0);

    // Getters
    City getCity1() const;
    City getCity2() const;
    double getBudget() const;

    // Setters
    void setCity1(const City& c1);
    void setCity2(const City& c2);
    void setBudget(double roadBudget);

    // Utility methods
    bool connects(const City& city) const;
    bool operator==(const Road& other) const;
    bool operator!=(const Road& other) const;
};

#endif // ROAD_H 