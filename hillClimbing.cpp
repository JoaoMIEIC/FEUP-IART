#include "hillClimbing.h"

void changeSchedules(vector<Intersection> & intersections, int funcType){
    srand((unsigned) time(0));
    int counter = 0;
    for(int i = 0; i < intersections.size(); i++){
        if(counter >= 2) return;
        int choice = (rand() % 2) + 1;
        for(int j = 0; j < intersections[i].getTrafficSchedule().size(); j++){
            if(choice == 1){
                int choiceTrafficLight = (rand() % intersections[i].getTrafficSchedule().size())  + 1;
                intersections[i].getTrafficSchedule()[choiceTrafficLight] += funcType;
                counter++;
            }
        }
    }
}

void applyNeighborhoodFunc(vector<Intersection> & intersections){
    srand((unsigned) time(0));
    int neighborhoodFunc = rand() % 2 + 1;
    switch(neighborhoodFunc) {
        case (1):
            changeSchedules(intersections, 1);
            break;
        case (2):
            changeSchedules(intersections, -1);
            break;
        default:
            break;
    }
}
void hillClimbing(vector<Car> &cars, int duration, vector<Intersection> & intersections){
    int bestSolutionCost = evaluateFinishedWithTime(cars, duration);
    int tries = 10;

    while(tries < 10){
        applyNeighborhoodFunc(intersections);
        int newSolutionCost = evaluateFinishedWithTime(cars, duration);
        if(newSolutionCost > bestSolutionCost){
            bestSolutionCost = newSolutionCost;
        }
        tries++;
    }

}