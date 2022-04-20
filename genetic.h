#pragma once

#include "graph.h"
#include "macros.h"
#include "evaluation.h"

class Solution {
    int fitnessValue;
    string changeLog = "";
public:
    vector<Intersection> intersections;
    Solution(vector<Intersection> &intersections): intersections(intersections) {}

    Solution(Solution parent1, Solution parent2) {
        crossover(parent1, parent2);
        mutation();
    };

    int getFitnessValue() { return fitnessValue;}
    //vector<Intersection> getIntersections() {return intersections;}
    bool operator <(const Solution& s1) const {
        return fitnessValue < s1.fitnessValue;
    }

    void crossover(const Solution& parent1, const Solution& parent2);
    void mutation();
    void evaluate(vector<Car> &cars, int duration);
};

void genetic(vector<Car> &cars, vector<Intersection> &intersections, int duration);