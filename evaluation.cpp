#include "evaluation.h"


int evaluateFinishedWithTime(vector<Car> &cars, int duration){
    int score = 0;
    for(auto & car : cars){
        if (car.getPath().empty()) {
            score += 1000;          
            score += (duration - (car.getTotalTimeWaiting() + car.getTotalTravelDist()));
        }
        // TODO: add score to cars who traveled some distance but didnt finish
    }  
    return score;
}