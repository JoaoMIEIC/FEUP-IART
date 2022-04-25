#include <iomanip>
#include <map>
#include "genetic.h"

void Solution::crossover(const Solution& parent1, const Solution& parent2){
    for (int i = 0; i < min(parent1.mutations.size(), parent2.mutations.size()); i++) {
        if (i % 2 == 0) mutations.push_back(parent1.mutations[i]);
        else mutations.push_back(parent2.mutations[i]);
    }
}

random_device rd;
mt19937 gen(rd());
negative_binomial_distribution<> randomNSeconds(5, 0.75);

void Solution::mutation(vector<Intersection> &intersections){
    srand(time(nullptr));

    for (auto mutation : mutations)
        intersections[mutation.intersectionIndex].changeStreetSchedule(mutation.streetIndex, mutation.newDuration);

    for (int nMutations = rand() % 4 + 1; nMutations != 0; nMutations--){
        int intersectionIndex = rand() % intersections.size();
        int streetIndex = rand() % intersections[intersectionIndex].getTrafficSchedule().size();
        int newStreetDuration = randomNSeconds(gen);

        int oldStreetDuration = intersections[intersectionIndex].changeStreetSchedule(streetIndex, newStreetDuration);
        mutations.emplace_back(intersectionIndex, streetIndex, oldStreetDuration, newStreetDuration);
    }
}

void Solution::revertStreets(vector<Intersection> &intersections){
    for (auto mutation : mutations)
        intersections[mutation.intersectionIndex].changeStreetSchedule(mutation.streetIndex, mutation.oldDuration);
}


Solution* rouletteSelection(vector<Solution> &solutionPool){
    long totalScore = 0;
    for (auto solution : solutionPool)
        totalScore += solution.getFitnessValue();

    uniform_int_distribution<long> randomInt(0, totalScore);
    long selectedSolution = randomInt(gen);

    for (int i = 0; i < solutionPool.size(); i++){
        selectedSolution -= solutionPool[i].getFitnessValue();
        if (selectedSolution <= 0) return &solutionPool[i];
    }

    return &solutionPool.back();
}

void genetic(vector<Car> &cars, vector<Intersection> &intersections, int duration){
    vector<Solution> solutionPool;

    solutionPool.emplace_back();
    solutionPool[0].setFitnessValue(evaluateSolution(cars, intersections, duration, 0));
    cout << "Initial fitness: " << solutionPool[0].getFitnessValue() << endl;

    for (int counter = 0; counter < INT_MAX; counter++) {
        while (solutionPool.size() < 10 /*macro definable*/) {
            Solution newSol (*rouletteSelection(solutionPool), *rouletteSelection(solutionPool), intersections);
            newSol.setFitnessValue(evaluateSolution(cars, intersections, duration, 0));
            newSol.revertStreets(intersections);
            cout << "New offspring has " << newSol.getFitnessValue() << " fitness." << endl;
            solutionPool.push_back(newSol);
        }

        // Removes 5 worst solutions
        sort(begin(solutionPool), end(solutionPool));
        solutionPool.erase(begin(solutionPool), begin(solutionPool) + 5);
        cout << "i = " << counter << ", Best solution has " << solutionPool[4].getFitnessValue() << " fitness." << endl;

    }
}