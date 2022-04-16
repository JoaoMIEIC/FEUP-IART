#pragma once

#include "graph.h"

void simulate(vector<Car> &cars, vector<Intersection> &intersections, int duration);
void clearStreets(vector<Intersection> &intersections);

int evaluateSolution(vector<Car> &cars, vector<Intersection> &intersections, int duration, int mode);

int evaluateWithTime(vector<Car> cars, vector<Intersection> &intersections, int duration);

int evaluateWithPercentage(vector<Car> cars, vector<Intersection> &intersections, int duration);
int getPercentageDone(Car* car);


