#include "files.h"
#include "algorithms.h"

Simulation simulation;
vector<Street> streets;
vector<Car> cars;
vector<Intersection> intersections;

int main() {
    readInput(simulation, streets, cars, intersections);

    vector<pair<Street*, int>> result = simulatedAnnealing(cars, intersections, simulation.duration, 10000);
    //vector<pair<Street*, int>> result = hillClimbing(cars, intersections, simulation.duration, 10);
    getBestResult(result);

    writeOutput(intersections);

    return 0;
}