#include "files.h"
#include "evaluation.h"


Simulation simulation;
vector<Street> streets;
vector<Car> cars;
vector<Intersection> intersections;

int main() {
    readInput(simulation, streets, cars, intersections);

    for (int i = 0; i < simulation.duration; i++){
        cout << "Ola" << endl;
        for (int h = 0; h < cars.size(); h++){
            cout << "Ola2" << endl;
            cars[h].advance();
        }
        for (int j = 0; j < intersections.size(); j++){
            cout << "Ola3" << endl;
            intersections[j].moveCar();
        }
    }
    
    cout << evaluateFinishedWithTime(cars,simulation.duration);
        
    writeOutput(intersections);
    return 0;
}


