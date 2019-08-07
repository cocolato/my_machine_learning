//
// Created by a0486470 on 2019-07-22.
//

#include "rand.h"
#include <iostream>
#include <ctime>
#include <algorithm>

using namespace std;


int randInt(int min, int max){
    static mt19937 rng(time(0));
    std::uniform_int_distribution<> norm(min, max-1);
    return norm(rng);
}

int randN(int n){
    static mt19937 rng(time(0));
    std::uniform_int_distribution<> norm(0, n-1);
    return norm(rng);
}

int rand100(){
    static mt19937 rng(time(0));
    std::uniform_int_distribution<> norm(0, 99);
    return norm(rng);
}

int rand01() {
    static mt19937 rng(time(0));
    std::uniform_int_distribution<> norm(0, 1);
    return norm(rng);
}

double rand1(){
    static mt19937 rng(time(0));
    std::uniform_real_distribution<> norm(0, 1);
    return norm(rng);
}

double Percentile(vector<double> Distr, double per){
    unsigned distrSize = Distr.size();

    sort(Distr.begin(), Distr.end());
    double tmp = 1 + (distrSize-1) * per;
    for(auto loc = Distr.begin(); loc != Distr.end(); loc++){
        if(*loc == tmp)
            return *loc;
        else if(*loc > per){
            return (*loc) * (tmp - *(loc-1)) + (*(loc-1)*(*loc-tmp));
        }
    }
}