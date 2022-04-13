#include "evaluation.h"


int evaluateFinishedWithTime(vector<Car> &cars, int duration){
    int score = 0;
    for (auto & car : cars) {
        if (car.getPath().empty()) score += 1000;
        score += (duration - (car.getTotalTimeWaiting() + car.getTotalTravelDist()));
    }
    return score;
}