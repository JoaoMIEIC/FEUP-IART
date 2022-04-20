#include <iomanip>
#include <map>
#include "genetic.h"

void Solution::crossover(const Solution& parent1, const Solution& parent2){
    for (int i = 0; i < parent1.intersections.size(); i++){
        if (i % 2 == 0) intersections.push_back(parent1.intersections[i]);
        else intersections.push_back(parent2.intersections[i]);
    }
}

random_device rd;
mt19937 gen(rd());
negative_binomial_distribution<> randomNSeconds(5, 0.75);

void Solution::mutation(){
    srand(time(nullptr));

    for (int nMutations = rand() % 4 + 1; nMutations != 0; nMutations--){
        int intersectionIndex = rand() % intersections.size();
        int streetIndex = rand() % intersections[intersectionIndex].getTrafficSchedule().size();
        intersections[intersectionIndex].changeStreetSchedule(streetIndex, randomNSeconds(gen));
    }

    for (int i = 0; i < intersections.size(); i++)
        if (!intersections[i].changeLog.empty())
            changeLog += "At index " + to_string(i) + ", " + intersections[i].changeLog;

    return;
}

void Solution::evaluate(vector<Car> &cars, int duration){
    fitnessValue = evaluateSolution(cars, intersections, duration, 0);
}

Solution* rouletteSelection(vector<Solution> &solutionPool){
    // TODO: check if randoms are working (prob arent)
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