#include "files.h"
#include "evaluation.h"


Simulation simulation;
vector<Street> streets;
vector<Car> cars;
vector<Intersection> intersections;

int main() {
    readInput(simulation, streets, cars, intersections);

    for (int i = 0; i < simulation.duration; i++){
        for (auto car : cars) car.advance();
        for (auto intersection : intersections) intersection.moveCar();
    }
    
    cout << evaluateFinishedWithTime(cars,simulation.duration);
        
    writeOutput(intersections);
    return 0;
}


