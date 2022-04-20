#include "genetic.h"

void Solution::crossover(const Solution& parent1, const Solution& parent2){
    for (int i = 0; i < parent1.intersections.size(); i++){
        if (i % 2 == 0) intersections.push_back(parent1.intersections[i]);
        else intersections.push_back(parent2.intersections[i]);
    }
}

void Solution::mutation(){
    random_device rd;
    default_random_engine generator(rd());
    uniform_int_distribution<int> randomNMutations(1, 4);
    uniform_int_distribution<int> randomIntersection(0, intersections.size()-1);

    // For example, suppose an ordinary dice is thrown repeatedly until the first time a "1" appears.
    // The probability distribution of the number of times it is thrown is supported
    // on the infinite set { 1, 2, 3, ... } and is a geometric distribution with p = 1/6.
    geometric_distribution<int> randomNSeconds(0.3 /*macro definable*/);

    for (int i = randomNMutations(generator); i != 0; i--){

        int nStreets = intersections[randomIntersection(generator)].getTrafficSchedule().size();
        uniform_int_distribution<int> randomStreet(0, nStreets-1);

        intersections[randomIntersection(generator)].changeStreetSchedule(randomStreet(generator), randomNSeconds(generator));

    }
}

void Solution::evaluate(vector<Car> &cars, int duration){
    fitnessValue = evaluateSolution(cars, intersections, duration, 0);
}

Solution* rouletteSelection(vector<Solution> &solutionPool){
    int totalScore = 0;
    for (auto solution : solutionPool)
        totalScore += solution.getFitnessValue();

    random_device rd;
    default_random_engine generator(rd());
    uniform_int_distribution<int> randomInt(0, totalScore);
    int selectedSolution = randomInt(generator);

    for (int i = 0; i < solutionPool.size(); i++){
        selectedSolution -= solutionPool[i].getFitnessValue();
        if (selectedSolution <= 0) return &solutionPool[i];
    }

    cout << "This shouldn't ever happen I think" << endl;
    return &solutionPool.back();
}

void genetic(vector<Car> &cars, vector<Intersection> &intersections, int duration){
    vector<Solution> solutionPool;
    solutionPool.emplace_back(intersections);
    solutionPool[0].evaluate(cars, duration);

    int counter = 0;

    while (counter < 10000) {
        if (counter == 9999)
            cout << "debug" << endl;

        while (solutionPool.size() < 10 /*macro definable*/) {
            Solution* parents[2];
            parents[0] = rouletteSelection(solutionPool);
            parents[1] = rouletteSelection(solutionPool);

            Solution s(*parents[0], *parents[1]);
            s.evaluate(cars, duration);
            solutionPool.push_back(s);
        }

        // Removes 5 worst solutions
        sort(begin(solutionPool), end(solutionPool));
        solutionPool.erase(begin(solutionPool), begin(solutionPool) + 5);
        cout << "i = " << counter << ", score = " << solutionPool[4].getFitnessValue()<< endl;

        counter++;
    }
}

// Genética:
// 1 -> Criar uma população de Y soluçoes base
// 2 -> Escolher 2 das soluções usando como peso na escolha a função de avaliação -> Parent Selection
// 3 -> Criar nova solução pelo crossover dos 2 escolhidos -> Reproduction
// 4 -> Fazer mutação da nova solução caso cumpra a condição X -> Mutation
// 5 -> Ir para 2 enquanto nova geração não tiver Z soluções -> ????
// 6 -> Entre as novas (e as antigas), escolher as Y melhores soluções -> Discard
// 7 -> Ir para 2 com as soluções escolhidas em 6 -> Iteration