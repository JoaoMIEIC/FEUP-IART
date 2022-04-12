#include "graph.h"

Car::Car(queue<Street*> path): totalTravelDist(0), totalTimeWaiting(0), distTilIntersection(0), path( move(path) ){};


void Car::advance() {
    if (distTilIntersection > 0) {
        distTilIntersection--;
        if (distTilIntersection == 0) this->path.front()->addToQueue(this);
        this->increaseTravelDist();
    } else 
        this->increaseTimeWaiting();
}

void Car::increaseTravelDist() {
    this->totalTravelDist++;
}

void Car::increaseTimeWaiting() {
    this->totalTimeWaiting++;
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

void Car::popStreet() {
    if (this->path.empty()) return;

    this->path.pop();
    distTilIntersection = this->path.front()->getLength();
}