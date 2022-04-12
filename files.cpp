#include "graph.h"

void readInput(Simulation &simulation, vector<Street> &streets, vector<Car> &cars, vector<Intersection> &intersections) {
    ifstream file("input.txt");
    file >> simulation.duration >> simulation.nIntersections >> simulation.nStreets >> simulation.nCars >> simulation.score;

    // Creates nIntersections empty intersections
    intersections.resize(simulation.nIntersections);

    // Reads and creates streets
    int initial, final, duration;
    string name;
    for (int i = 0; i < simulation.nStreets; i++) {
        file >> initial >> final >> name >> duration;
        streets.emplace_back(initial, final, name, duration);
    }

    // Adds streets to their final intersection
    for (int i = 0; i < streets.size(); i++)
        streets[i].getFinalIntersection()->addStreet(&streets[i]);


    // Reads and creates cars
    int carPathLength;
    string streetName;
    for (int i = 0; i < simulation.nCars; i++) {
        file >> carPathLength;

        queue<Street*> streetNames;
        for (int j = 0; j < carPathLength; j++) {
            file >> streetName;
            streetNames.push(&*find(begin(streets), end(streets), new Street(streetName)));
        }

        cars.emplace_back(streetNames);
        cars[i].getPath().front()->addToQueue(&cars[i]);
    }

    file.close();
}

void writeOutput(vector<Intersection> &intersections){
    // Erases previous content
    ofstream file("output.txt", ios_base::trunc);

    for (int i = 0; i < intersections.size(); i++){
        vector<Street*> trafficSchedule = intersections[i].getTrafficSchedule();
        
        for (int j = 0; j < trafficSchedule.size(); j++) {
            file << trafficSchedule[j]->getDuration() << " ";
        }
        file << endl;
    }

    file.close();
}

void readOutput(vector<Intersection> &intersections){
    ifstream file("output.txt");

    int duration;
    for (const auto& intersection: intersections){
        for (auto street: intersection.getTrafficSchedule()) {
            file >> duration;
            if (street->getDuration() != duration)
                street->setDuration(duration);
        }
    }

    file.close();
}


// Legacy code
/*
// Divides time equally between incoming streets, giving each street one and only one time interval
// when it's open. Very far away from being ideal, because every car queueing after its current street's
// interval will be locked in place until the simulation's end.
void generateInitialSchedule(){
    // Do not use range-based loops (for(auto x : xs)) !!! Elements won't be modified
    for (int i = 0; i < intersections.size(); i++){
        int nIncStreets = (int)intersections[i].trafficSchedule.size();
        int timeShare = duration / nIncStreets;

        int timeLeft = duration;
        for (int j = 0; j < nIncStreets - 1; j++){
            intersections[i].trafficSchedule[j].second = timeShare;
            timeLeft -= timeShare;
        }

        // If it's not possible to divide time equally between every street,
        // the last one stays open for the remaining time ( ]0, 2*timeShare[ )
        intersections[i].trafficSchedule[nIncStreets - 1].second = timeLeft;
    }
}
*/
