#include "algorithms.h"


void applyNeighborhoodFunc(Intersection* intersection){
    srand((unsigned) time(0));
    int neighborhoodFunc = rand() % 3;
    switch(neighborhoodFunc) {
        case (0):
            intersection->changeSchedules(1);
            break;
        case (1):
            intersection->changeSchedules(-1);
            break;
        case (2):
            intersection->shuffleOrder();
            break;
        default:
            break;
    }
}
void hillClimbing(vector<Car> &cars, vector<Intersection> & intersections, int duration){
    int bestSolutionCost = evaluateSolution(cars, intersections, duration, 0);
    int tries = 0;

    while(tries < 10){
        applyNeighborhoodFunc(&intersections[0]);
        int newSolutionCost = evaluateSolution(cars, intersections, duration, 0);
        if(newSolutionCost > bestSolutionCost){
            bestSolutionCost = newSolutionCost;
        }
        tries++;
    }
}

float coolingStructure(float temperature, int counter){
    return temperature* pow(0.9, counter);
}

void storeDurations(vector<int> &durations, Intersection* intersection){
    vector<Street*> tmp = intersection->getTrafficSchedule();
    for (int i = 0; i < tmp.size(); i++)
        durations.push_back(tmp[i]->getDuration());
}

void revertDurations(vector<int> &durations, Intersection* intersection){
    vector<Street*> tmp = intersection->getTrafficSchedule();
    for (int i = 0; i < tmp.size(); i++)
        tmp[i]->setDuration(durations[i]);
}

void simulatedAnnealing(vector<Car> &cars, vector<Intersection> & intersections, int duration, int iterations){
    srand((unsigned) time(0));
    int counter = 0;
    int bestSolutionCost = evaluateSolution(cars, intersections, duration, 0);

    float temperature = 50* cars.size();

    while(counter < iterations) {
        temperature = coolingStructure(temperature, counter);
        int randInter = rand() % intersections.size();

        vector<int> streetDurations;
        storeDurations(streetDurations, &intersections[randInter]);

        applyNeighborhoodFunc(&intersections[randInter]);
        int newSolutionCost = evaluateSolution(cars, intersections, duration, 0);
        cout << "i: " << counter << " " << newSolutionCost << endl;
        int difference = newSolutionCost - bestSolutionCost;

        if (difference <= 0 && rand() % 1 > pow(exp(1), difference/temperature))
            revertDurations(streetDurations, &intersections[randInter]);

        else if (difference > temperature) temperature /= 2; //todo change later
        counter++;
    }
}





