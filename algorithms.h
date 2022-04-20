#pragma once

#include "macros.h"
#include "graph.h"
#include "evaluation.h"


void applyNeighborhoodFunc(Intersection* intersection);

void hillClimbing(vector<Car> &cars, vector<Intersection> & intersections, int duration);

void simulatedAnnealing(vector<Car> &cars, vector<Intersection> & intersections, int duration, int iterations);
void storeDurations(vector<int> &durations, Intersection* intersection);
void revertDurations(vector<int> &durations, Intersection* intersection);
float coolingStructure(float temperature, int counter);