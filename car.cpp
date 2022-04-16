#include "graph.h"

Car::Car(): totalTravelDist(0), totalTimeWaiting(0), distTilIntersection(0), recentlyInQueue(false){}

void Car::advance() {
    if (this->getPath().empty()) return;

    if (distTilIntersection > 0) {
        distTilIntersection--;
        if (distTilIntersection == 0) {
            if(this->getPath().size() > 1) {
                this->path.front()->addToQueue(this);
                this->recentlyInQueue = true;
            }
            else this->popStreet();
        }
        this->increaseTravelDist();
    } else{
        this->increaseTimeWaiting();
        if (this->recentlyInQueue == true) this->recentlyInQueue = false;
    }

}

void Car::increaseTravelDist() {
    this->totalTravelDist++;
}

void Car::increaseTimeWaiting() {
    this->totalTimeWaiting++;
}

void Car::decreaseTimeWaiting() {
    this->totalTimeWaiting--;
}

bool Car::isRecentlyInQueue(){
    return this->recentlyInQueue;
}

void Car::setRecentlyInQueue(bool value){
    this->recentlyInQueue = value;
}

void Car::addStreet(Street * street){
    this->path.push(street);
}
int Car::getTotalTravelDist(){
    return this->totalTravelDist;
}

int Car::getTotalTimeWaiting(){
    return this->totalTimeWaiting;
}

int Car::getDistTilIntersection(){
    return this->distTilIntersection;
}

queue<Street*> Car::getPath() {
    return this->path;
}

Street* Car::removeStreet() {
    Street* street = this->path.front();
    this->path.pop();
    return street;
}

void Car::popStreet() {

    this->path.pop();
    if (this->path.empty()) return;
    distTilIntersection = this->path.front()->getLength();
    this->advance();
}