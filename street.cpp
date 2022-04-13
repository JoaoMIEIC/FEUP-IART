#include "graph.h"

Street::Street(int first, int final, string name, int length, vector<Intersection> &intersections): name( move(name) ), length(length), duration(1) {
        this->initIntersection = &intersections[first];
        this->finalIntersection = &intersections[final];
}

Street::Street(string name): name( move(name) ){}

bool Street::operator==(const Street* s) const {
        return this->name == s->name;
}

int Street::getDuration() const{
    return this->duration;
}

int Street::getLength() const{
    return this->length;
}

Car* Street::getFront() const{
    return waitingCars.front();
}

void Street::popCar(){
    if (this->waitingCars.empty()) return;

    Car* firstCar = this->waitingCars.front();
    if (this->waitingCars.front()->isRecentlyInQueue()){
        firstCar->setRecentlyInQueue(false);
        return;
    }

    // firstCar->increaseTravelDist(); // atravessar não custa tempo alegadamente
    firstCar->decreaseTimeWaiting(); // previous increase turned out to not exist
    firstCar->popStreet();
    this->waitingCars.pop();
}

void Street::addToQueue(Car* car){
    this->waitingCars.push(car);
}

Intersection* Street::getInitIntersection() const {
    return this->initIntersection;
}

Intersection* Street::getFinalIntersection() const{
    return this->finalIntersection;
}

void Street::setInitIntersection(Intersection* initIntersection){
    this->initIntersection = initIntersection;
}

void Street::setFinalIntersection(Intersection* finalIntersection){
    this->finalIntersection = finalIntersection;

}

void Street::setDuration(int duration){
    this->duration = duration;
}
