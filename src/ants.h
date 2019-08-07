//
// Created by a0486470 on 2019-07-22.
//

#ifndef TMP_ANTS_H
#define TMP_ANTS_H

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class ants{
private:
    int antsNum_;
    int limits_;
    int Q_;  // 更新信息度浓度常数
    double RHO_; // 挥发常数
    int steps_;
    double epsilon_;
    vector<vector<int> > cost_;
    vector<vector<double> > pheromone_;
    vector<vector<int> > mStep_;

    void walk();
    void update();

public:

    explicit ants(int antsNum=100, int limits=1000, double Q=2.5, double RHO=0.8, int steps=10, double epsilon=0.15);
    vector<vector<int> > getRandomCostAry(int size);
    void setCost(vector<vector<int> > a);
    void printp();
    void printmStep();
    void Run();
    void printCost();
};


#endif //TMP_ANTS_H
