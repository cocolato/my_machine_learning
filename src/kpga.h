//
// Created by a0486470 on 2019-07-23.
//

#ifndef TMP_KPGA_H
#define TMP_KPGA_H

#include <iostream>
#include <vector>
#include "rand.h"

using namespace std;

int notVal(int v);

class kpGA{
private:
    int maxValue_;
    int parNum_;
    int weightLimit_;
    int poolSize_;
    int lastG_;
    double mutRate_;
    vector<vector<int> > parcel_;
    vector<vector<int> > pool_;
    vector<vector<int> > ngpool_;


public:
    explicit kpGA(int maxValue=100, int parNum=30, int poolSize=50,int lastG=1000, double mutRate=0.001);

    vector<vector<int> > getRandomParcel();
    vector<vector<int> > getRandomPool(int poolSize);
    void showPool(int i);
    void mutation();
    int evalfit(vector<int> g);
    void crossing(vector<int> &m, vector<int> &p, vector<int> &c1, vector<int> &c2);
    void selectNg();
    int selectp(vector<int> roulette, int totalfitness);
    void mating();
    void printp();
    void Run();
};



#endif //TMP_KPGA_H
