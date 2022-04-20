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
    void changeDuration(int duration);
    Car* getFront() const;

    void clearQueue();

    bool operator==(const Street* s) const;
};

class Intersection {
    int currentStreet, timeLeft;
    vector<Street*> trafficSchedule;

public:
    void addStreet(Street* s);
    void setTimeLeft(int timeLeft);
    vector<Street*> getTrafficSchedule() const;
    void moveCar();

    void changeSchedules(int funcType);
    void changeStreetSchedule(int streetIndex, int duration);
    void shuffleOrder();
    void clearStreets();
};

class Car {
    int totalTravelDist;
    int totalTimeWaiting;
    int distTilIntersection;
    queue<Street*> path;
    bool recentlyInQueue;

public:
    Car();
    void popStreet();
    void advance();
    queue<Street*> getPath();
    int getTotalTravelDist();
    int getTotalTimeWaiting();
    int getDistTilIntersection();
    bool isRecentlyInQueue();
    void setRecentlyInQueue(bool value);

    void addStreet(Street * street);
    Street* removeStreet();
    void increaseTravelDist();
    void increaseTimeWaiting();
    void decreaseTimeWaiting();


};




