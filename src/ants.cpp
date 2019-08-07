//
// Created by a0486470 on 2019-07-22.
//

#include "ants.h"
#include "rand.h"
#include <vector>
#include <cstdio>

using namespace std;


ants::ants(int antsNum, int limits, double Q, double RHO, int steps, double epsilon) : antsNum_(antsNum),
limits_(limits), Q_(Q), RHO_(RHO), steps_(steps), epsilon_(epsilon) {
    pheromone_ = vector<vector<double> >(2, vector<double>(steps));
    mStep_ = vector<vector<int> >(antsNum, vector<int>(steps));
    cost_ = getRandomCostAry(2);
}

void ants::setCost(vector<vector<int> > a) {
    for(int i = 0; i < 2; ++i){
        for(int j = 0; j < 10; ++ j)
            cost_[i][j] = a[i][j];
    }
}

vector<vector<int> > ants::getRandomCostAry(int size){
    vector<vector<int> > cost;
    cost.resize(size);
    for(int i = 0; i < size; ++i)
        cost[i].resize(steps_);
    for(int i = 0; i < size; ++i)
        for(int j = 0; j < steps_; ++j)
            cost[i][j] = randInt(1, 10);

    return cost;
}

void ants::printp() {
    for(int i = 0; i < 2; ++i){
        for(int j = 0; j < steps_; ++j)
            printf("%4.2lf  ", pheromone_[i][j]);
        cout << endl;
    }
}

void ants::printCost() {
    for(int i = 0; i < 2; ++i){
        for(int j = 0; j < steps_; ++j)
            printf("%d  ", cost_[i][j]);
        cout << endl;
    }
}

void ants::printmStep() {
    cout << "*mStep" << endl;
    for(int i = 0; i < antsNum_; ++i){
        for(int j = 0; j < steps_; ++j)
            cout << mStep_[i][j] << "\t";
        cout << endl;
    }
}

void ants::walk() {
    int m;  // 蚂蚁个体号码
    int s;  // 蚂蚁现在所处的位置

    for(m = 0; m < antsNum_; ++m){
        for(s = 0; s < steps_; ++s){
            if((rand1() < epsilon_) || (abs(pheromone_[0][s] - pheromone_[1][s]) < 1e-09))
                mStep_[m][s] = rand01();
            else{
                if(pheromone_[0][s] > pheromone_[1][s])
                    mStep_[m][s] = 0;
                else
                    mStep_[m][s] = 1;
            }
        }
    }
    printmStep();
}

void ants::update() {

    int m;  // 蚂蚁个体号码
    int lm; // 蚂蚁移动的距离
    double sumLm = 0; // 蚂蚁移动的总体距离

    for(int i = 0; i < 2; ++i){
        for(int j = 0; j < steps_; ++j)
            pheromone_[i][j] *= RHO_;
    }

    for(m = 0; m < antsNum_; ++m){
        lm = 0;
        for(int i = 0; i < steps_; ++i)
            lm += cost_[mStep_[m][i]][i];

        for(int i = 0; i < steps_; ++i)
            pheromone_[mStep_[m][i]][i] += Q_ * (1.0 / lm);
        sumLm += lm;
    }

    cout << "Advange distance:" << sumLm/antsNum_ << endl;
}

void ants::Run() {
    printCost();
    int i;
    for(i = 0; i < limits_; ++i){
        cout << i << endl;
        printp();
        walk();
        update();
    }
    printCost();
}
