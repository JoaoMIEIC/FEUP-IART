#include "graph.h"

void Intersection::addStreet(Street* s) {
    this->trafficSchedule.push_back(s);
}

void Intersection::moveCar(){
    this->trafficSchedule[currentStreet]->popCar();
    timeLeft--;
    if (timeLeft == 0) {
        currentStreet = ++currentStreet % this->trafficSchedule.size();
        timeLeft = this->trafficSchedule[currentStreet]->getDuration();
    }
}

void Intersection::setTimeLeft(int timeLeft) {
    this->timeLeft = timeLeft;
}

vector<Street*> Intersection::getTrafficSchedule() const{
    return this->trafficSchedule;
}
