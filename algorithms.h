#pragma once

#include "macros.h"
#include "graph.h"
#include "evaluation.h"


void applyNeighborhoodFunc(Intersection* intersection, int rnd = -1);

void hillClimbing(vector<Car> &cars, vector<Intersection> & intersections, int duration, int iterations);

void simulatedAnnealing(vector<Car> &cars, vector<Intersection> & intersections, int duration, int iterations);
void storeDurations(vector<pair<Street*, int>> &durations, Intersection* intersection);
void revertDurations(vector<pair<Street*, int>> &durations, Intersection* intersection);
float coolingStructure(float temperature, int counter);