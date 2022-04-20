#include "files.h"
#include "algorithms.h"
#include "genetic.h"

Simulation simulation;
vector<Street> streets;
vector<Car> cars;
vector<Intersection> intersections;

int main() {
    cout << "Input reading starting..." << endl;
    readInput(simulation, streets, cars, intersections);

    genetic(cars, intersections, simulation.duration);
        
    //writeOutput(intersections);

    return 0;
}


