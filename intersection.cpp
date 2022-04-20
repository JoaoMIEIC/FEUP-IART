#include <random>

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

void Intersection::clearStreets(){
    for (int i = 0; i < trafficSchedule.size(); i++)
        trafficSchedule[i]->clearQueue();
}

void Intersection::removeIncomingStreets(){
    this->trafficSchedule.clear();
}

void Intersection::changeSchedules(int funcType){
    srand((unsigned) time(0));

    int choiceTrafficLight = (rand() % trafficSchedule.size());

    random_device rd;
    default_random_engine generator(rd());
    geometric_distribution<int> randomNSeconds(0.3 /*macro definable*/);

    trafficSchedule[choiceTrafficLight]->changeDuration(funcType);
}

void Intersection::shuffleOrder() {
    srand((unsigned) time(0));
    shuffle(trafficSchedule.begin(), trafficSchedule.end(), std::mt19937(std::random_device()()));
}

void Intersection::changeStreetSchedule(int streetIndex, int duration){
    trafficSchedule[streetIndex]->setDuration(duration);
    changeLog += "Street " + to_string(streetIndex) + " set to " + to_string(duration) + " \n";
}
