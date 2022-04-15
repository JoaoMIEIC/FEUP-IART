#include "evaluation.h"


int evaluateFinishedWithTime(vector<Car> &cars, int duration){
    int score = 0;
    for (auto & car : cars) {
        if (car.getPath().empty()) {
            score += 100;
            score += 10*(duration - (car.getTotalTimeWaiting() + car.getTotalTravelDist()));
        }
    }
    return score;
}

int evaluateWithPercentage(vector<Car> &cars, int duration){
    int score = 0;
    for (auto & car : cars) {
        if (car.getPath().empty()) score += 100;
        else score += getPercentageDone(&car);
    }
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