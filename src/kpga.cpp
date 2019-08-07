//
// Created by a0486470 on 2019-07-23.
//

#include "kpga.h"

using namespace std;

#define YES 1
#define NO 0

int notVal(int v){
    if(v == YES)
        return NO;
    else
        return YES;
}

kpGA::kpGA(int maxValue, int lgNum, int poolSize,int lastG, double mutRate) :maxValue_(maxValue), parNum_(lgNum),
poolSize_(poolSize), lastG_(lastG), mutRate_(mutRate) {
    weightLimit_ = (parNum_ * maxValue_) / 4;
    parcel_ = getRandomParcel();
    pool_ = getRandomPool(poolSize_);
    ngpool_ = getRandomPool(2 * poolSize_);
}

vector<vector<int> > kpGA::getRandomParcel() {
    vector<vector<int> > parcel;
    parcel.resize(parNum_);
    for(int i = 0; i < parNum_; ++i)
        parcel[i].resize(2);
    for(int i = 0; i < parNum_; ++i)
        for(int j = 0; j < 2; ++j)
            parcel[i][j] = rand100();

    return parcel;
}

vector<vector<int> > kpGA::getRandomPool(int poolSize) {
    vector<vector<int> > pool;
    pool.resize(poolSize);
    for(int i = 0; i < poolSize; ++i)
        pool[i].resize(parNum_);
    for(int i = 0; i < poolSize; ++i)
        for(int j = 0; j < parNum_; ++j)
            pool[i][j] = rand01();

    return pool;
}

void kpGA::showPool(int i){
    if(i == 1){
        for(int m = 0; m < poolSize_; ++m){
            for(int n = 0; n < parNum_; ++n)
                cout << pool_[m][n] << endl;
        }
    }
    else if(i == 2){
        for(int m = 0; m < 2 * poolSize_; ++m){
            for(int n = 0; n < parNum_; ++n)
                cout << ngpool_[m][n] << endl;
        }
    }
}

// 变异操作
void kpGA::mutation() {
    for(int i = 0; i < poolSize_ * 2; ++i){
        for(int j = 0; j < parNum_; ++j){
            if((double)randN(100)/100.0 <= mutRate_)
                ngpool_[i][j] = notVal(ngpool_[i][j]);
        }
    }
}

// 计算适应度
int kpGA::evalfit(vector<int> g) {
    int pos;
    int value = 0;
    int weight = 0;

    for(pos = 0; pos < parNum_; ++pos){
        weight += parcel_[pos][0] * g[pos];
        value += parcel_[pos][1] * g[pos];
    }
    if(weight >= weightLimit_)
        return 0;

    return value;
}

void kpGA::crossing(vector<int> &m, vector<int> &p, vector<int> &c1, vector<int> &c2) {
    int j;
    int cp;

    cp = randN(parNum_);

    for(j = 0; j < cp; ++j){
        c1[j] = m[j];
        c2[j] = p[j];
    }

    for(; j < parNum_; ++j){
        c2[j] = m[j];
        c1[j] = p[j];
    }
}

int kpGA::selectp(vector<int> roulette, int totalFitness) {
    int i;
    int ball;
    int acc =0;

    ball = randN(totalFitness);
    for(i = 0; i < poolSize_; ++i){
        acc += roulette[i];
        if(acc > ball)
            break;
    }
    return i >= 30 ? 29 : i;
}

void kpGA::mating() {
    int i;
    int totalFitness = 0;
    vector<int> roulette(poolSize_);
    int mother, father;

    for(i = 0; i < poolSize_; ++i){
        roulette[i] = evalfit(pool_[i]);
        totalFitness += roulette[i];
    }

    for(i = 0; i < poolSize_; ++i){
        do{
            mother = selectp(roulette, totalFitness);
            father = selectp(roulette, totalFitness);
        }while(mother == father);
    }
    i = i >= 30 ? 29 : i;
    crossing(pool_[mother], pool_[father], ngpool_[i*2], ngpool_[i*2+1]);
}

void kpGA::selectNg() {
    int i, j, c;
    int totalFitness = 0;
    vector<int> roulette(poolSize_*2);
    int ball;
    int acc = 0;

    for(i = 0; i < poolSize_; ++i){
        totalFitness = 0;
        for(c = 0; c < poolSize_ * 2; ++c){
            roulette[c] = evalfit(ngpool_[c]);
            totalFitness += roulette[c];
        }
        ball = randN(totalFitness);
        acc = 0;
        for(c = 0; c < 2 * poolSize_; ++c){
            acc += roulette[c];
            if(acc > ball)
                break;
        }

        for(j = 0; j < parNum_; ++j)
            pool_[i][j] = ngpool_[c][j];
    }
}

void kpGA::printp() {
    int i, j;
    int fitness;
    double totalFitness = 0;
    int eLite, bestFit = 0;

    for(i = 0; i < poolSize_; ++i){
        for(j = 0; j < parNum_; ++j)
            cout << pool_[i][j];
        fitness = evalfit(pool_[i]);
        cout << "\t" << fitness << endl;
        if(fitness > bestFit){
            bestFit = fitness;
            eLite = i;
        }

        totalFitness += fitness;
    }

    cout << eLite << "\t" << bestFit << "\t";
    cout << totalFitness/poolSize_ << endl;

}

void kpGA::Run() {
    for(int generation = 1; generation < lastG_ + 1; ++generation){
        cout << "The " << generation << " th" << endl;
        mating();
        cout << 1 <<endl;
        mutation();
        selectNg();
        printp();
    }
}

