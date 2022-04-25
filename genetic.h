#pragma once

#include "graph.h"
#include "macros.h"
#include "evaluation.h"

class Solution {
    int fitnessValue;

public:
    struct Mutation {
        int intersectionIndex, streetIndex, oldDuration, newDuration;
        Mutation(int intersectionIndex, int streetIndex, int oldDuration, int newDuration)
            : intersectionIndex(intersectionIndex), streetIndex(streetIndex), oldDuration(oldDuration), newDuration(newDuration){};
    };
    vector<Mutation> mutations;

    Solution() = default;

    Solution(const Solution& parent1, const Solution& parent2, vector<Intersection> &intersections) {
        srand(time(nullptr));
        crossover(parent1, parent2);
        if (rand() % 151 < 110) // ~72% chance taking into account modulo operations with MAX_RAND
            mutation(intersections);
        else
            return; //debug
    };

    void setFitnessValue(int fitnessValue){ this->fitnessValue = fitnessValue;}
    int getFitnessValue() { return fitnessValue;}
    bool operator <(const Solution& s1) const {
        return fitnessValue < s1.fitnessValue;
    }

    void crossover(const Solution& parent1, const Solution& parent2);
    void mutation(vector<Intersection> &intersections);
    void evaluate(vector<Car> &cars, int duration);
    void revertStreets(vector<Intersection> &intersections);
};

void genetic(vector<Car> &cars, vector<Intersection> &intersections, int duration);