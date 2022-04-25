#pragma once

#include "macros.h"
#include "graph.h"
#include "evaluation.h"


void applyNeighborhoodFunc(Intersection* intersection, int rnd = -1);

vector<pair<Street*, int>> hillClimbing(vector<Car> &cars, vector<Intersection> & intersections, int duration, int iterations);

vector<pair<Street*, int>> simulatedAnnealing(vector<Car> &cars, vector<Intersection> & intersections, int duration, int iterations);
float coolingStructure(float temperature, int counter);

void storeSolutions(vector<pair<Street*, int>> &durations, vector<Intersection> &intersections);
void storeDurations(vector<pair<Street*, int>> &durations, Intersection* intersection);
void revertDurations(vector<pair<Street*, int>> &durations, Intersection* intersection);
void getBestResult(vector<pair<Street*, int>> &durations);
