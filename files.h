#pragma once


#include "graph.h"



void readInput(Simulation &simulation, vector<Street> &streets, vector<Car> &cars, vector<Intersection> &intersections);
void writeOutput(vector<Intersection> &intersections);
void readOutput(vector<Intersection> &intersections);