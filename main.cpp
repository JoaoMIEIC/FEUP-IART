#include "files.h"
#include "algorithms.h"

Simulation simulation;
vector<Street> streets;
vector<Car> cars;
vector<Intersection> intersections;

int main() {
    readInput(simulation, streets, cars, intersections);

    //simulatedAnnealing(cars, intersections, simulation.duration, 10000);
    hillClimbing(cars, intersections, simulation.duration, 10);

    //writeOutput(intersections);

    return 0;
}