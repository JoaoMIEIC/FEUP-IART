#include "evaluation.h"


// Cars has no & on purpose
int evaluateSolution(vector<Car> cars, vector<Intersection> &intersections, int duration, int mode){
    switch (mode) {
        case (0):
            return evaluateWithTime(cars, intersections, duration);
        case (1):
            return evaluateWithPercentage(cars, intersections, duration);
        default:
            return -1;
    }
}

void simulate(vector<Car> &cars, vector<Intersection> &intersections, int duration){
    for (int i = 0; i < cars.size(); i++)
        cars[i].getPath().front()->addToQueue(&cars[i]);

    for (int i = 0; i < duration; i++){
        for (int j = 0; j < cars.size(); j++)
            cars[j].advance();
        for (int j = 0; j < intersections.size(); j++)
            intersections[j].moveCar();
    }
}

void clearStreets(vector<Intersection> &intersections){
    for (int i = 0; i < intersections.size(); i++)
        intersections[i].clearStreets();
}

int evaluateWithTime(vector<Car> &cars, vector<Intersection> &intersections, int duration){
    simulate(cars, intersections, duration);

    int score = 0;
    for (auto & car : cars) {
        if (car.getPath().empty()) {
            score += 100;
            score += 10*(duration - (car.getTotalTimeWaiting() + car.getTotalTravelDist()));
        }
    }

    clearStreets(intersections);
    return score;
}

int evaluateWithPercentage(vector<Car> &cars, vector<Intersection> &intersections, int duration){
    simulate(cars, intersections, duration);

    int score = 0;
    for (int i = 0; i < cars.size(); i++) {
        if (cars[i].getPath().empty()) score += 100;
        else score += getPercentageDone(&cars[i]);
    }

    clearStreets(intersections);
    return score;
}

int getPercentageDone(Car* car){
    float distanceDone = car->getTotalTravelDist();
    float distanceLeft = car->getDistTilIntersection();

    car->getPath().pop();
    while(!car->getPath().empty()){
        distanceLeft += car->getPath().front()->getDuration();
    }

    return 100 * (distanceDone / (distanceDone + distanceLeft));
}