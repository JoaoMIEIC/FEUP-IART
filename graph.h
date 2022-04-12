#pragma once

#include "macros.h"


class Intersection;
class Car;

class Street {
    string name;
    Intersection *initIntersection, *finalIntersection;
    queue<Car*> waitingCars;
    int length, duration;
public:
    Street(int first, int final, string name, int length, vector<Intersection> &intersections);
    Street(string name);
    void popCar();
    void addToQueue(Car* car);
    int getLength() const;

    Intersection* getInitIntersection() const;
    Intersection* getFinalIntersection() const;

    void setInitIntersection(Intersection* initIntersection);
    void setFinalIntersection(Intersection* finalIntersection);

    int getDuration() const;
    void setDuration(int duration);
    Car* getFront() const;

    bool operator==(const Street* s) const;
};

class Intersection {
    int currentStreet, timeLeft;
    vector<Street*> trafficSchedule;

public:
    void addStreet(Street* s);
    vector<Street*> getTrafficSchedule() const;
    void moveCar();
};

class Car {
    int totalTravelDist;
    int totalTimeWaiting;
    int distTilIntersection;
    queue<Street*> path;

public:
    explicit Car(queue<Street*> path);
    void popStreet();
    void advance();
    queue<Street*> getPath();
    int getTotalTravelDist();
    int getTotalTimeWaiting();
    int getDistTilIntersection();

    void increaseTravelDist();
    void increaseTimeWaiting();
    void decreaseTimeWaiting();
};




