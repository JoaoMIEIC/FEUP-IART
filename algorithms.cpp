#include "algorithms.h"


void applyNeighborhoodFunc(Intersection* intersection, int rnd){
    int neighborhoodFunc = rnd;

    if (rnd == -1){
        random_device rd;
        default_random_engine generator(rd());
        uniform_int_distribution<int> randomInt(0, 2);
        neighborhoodFunc = randomInt(generator);
    }

    switch(neighborhoodFunc) {
        case (0):
            intersection->changeSchedules(1);
            break;
        case (1):
            intersection->changeSchedules(-1);
            break;
        case (2):
            intersection->shuffleOrder();
            break;
        default:
            break;
    }
}
void hillClimbing(vector<Car> &cars, vector<Intersection> & intersections, int duration, int iterations){
    int bestSolutionCost = evaluateSolution(cars, intersections, duration, 0);
    int counter = 0;

    while(counter < iterations){
        for (int i = 0; i < intersections.size(); i++){
            for (int j = 0; j <= 2; j++){
                vector<pair<Street*,int>> streetDurations;
                storeDurations(streetDurations, &intersections[i]);

                applyNeighborhoodFunc(&intersections[i]);
                int newSolutionCost = evaluateSolution(cars, intersections, duration, 0);
                cout << "i(" << j << "): " << i << " " << newSolutionCost << " " << bestSolutionCost << endl;
                if(newSolutionCost < bestSolutionCost) revertDurations(streetDurations, &intersections[i]);
                else bestSolutionCost = newSolutionCost;

            }
        }

        counter++;
    }
}

double coolingStructure(double temperature, int counter){
    return temperature* pow(0.99999, counter);
}

void storeDurations(vector<pair<Street*, int>> &durations, Intersection* intersection){
    vector<Street*> tmp = intersection->getTrafficSchedule();
    for (int i = 0; i < tmp.size(); i++)
        durations.push_back(make_pair(tmp[i], tmp[i]->getDuration()));



}

void revertDurations(vector<pair<Street*, int>> &durations, Intersection* intersection){
    intersection->removeIncomingStreets();
    for (int i = 0; i < durations.size(); i++){
        intersection->addStreet(durations[i].first);
        durations[i].first->setDuration(durations[i].second);
    }

}

void simulatedAnnealing(vector<Car> &cars, vector<Intersection> & intersections, int duration, int iterations){
    int counter = 0;
    int bestSolutionCost = evaluateSolution(cars, intersections, duration, 0);

    double temperature = 10 * cars.size();

    random_device rd;
    default_random_engine generator(rd());
    uniform_int_distribution<int> randomInt (0, intersections.size() - 1);
    uniform_real_distribution<double> randomDouble(0, 1);

    while(counter < iterations) {
        temperature = coolingStructure(temperature, counter);
        int randInter = randomInt(generator);

        vector<pair<Street*,int>> streetDurations;
        storeDurations(streetDurations, &intersections[randInter]);

        applyNeighborhoodFunc(&intersections[randInter]);

        int newSolutionCost = evaluateSolution(cars, intersections, duration, 0);
        cout << "i: " << counter << " " << newSolutionCost << " " << bestSolutionCost << endl;
        double difference = newSolutionCost - bestSolutionCost;
        if (difference <= 0 && randomDouble(generator) > pow(exp(1), difference/temperature)){
            //cout << "rnd: " << randomDouble(generator) << " pow: " << pow(exp(1), difference/temperature) << " temp: " << temperature<< endl;

            revertDurations(streetDurations, &intersections[randInter]);
            //cout << "This happened!!" << endl;
        }
        else  bestSolutionCost = newSolutionCost;
        counter++;
    }
}





