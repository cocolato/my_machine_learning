//
// Created by a0486470 on 2019-07-22.
//
#include "qlearning.h"
#include <cstdio>

using namespace std;

void printQValue(int qValue[NODENO]){
    int i;

    for(i = 1; i < NODENO; ++i)
        printf("%d\t", qValue[i]);

    printf("\n");
}

int selectA(int olds, int qValue[NODENO]){
    int s;

    if(rand1() < EPSILON){
        if(rand01() == 0)
            s = 2 * olds + 1;
        else
            s = 2 * olds + 2;
    }
    else{
        if(qValue[2 * olds + 1] > qValue[2 * olds + 2])
            s = 2 * olds + 1;
        else
            s = 2 * olds + 2;
    }

    return s;
}

int updated(int s, int qValue[NODENO]){

    int qv;    // 要更新的q值
    int qmax;  // q值最大值

    if(s > 6){
        if(s == 14)
            qv = qValue[s] + ALPHA * (1000 - qValue[s]);
        else
            qv = qValue[s];
    }
    else{
        if(qValue[2 * s + 1] > qValue[2 * s + 2])
            qmax = qValue[2 * s + 1];
        else
            qmax = qValue[2 * s + 2];
        qv = qValue[s] + ALPHA * (GAMMA * qmax - qValue[s]);
    }

    return qv;
}

QLearning::QLearning(int nodeNum, double alpha, double gamma, double epsilon): nodeNum_(nodeNum), alpha_(alpha),
 gamma_(gamma), epsilon_(epsilon){

    qValue_ = make_shared_array<int>(nodeNum);
    for(int i = 0; i < nodeNum; ++i)
        qValue_.get()[i] = rand100();
    printQValue();
    cout << "开始运行！" << endl;
}

QLearning::~QLearning() {
    cout << "结束运行！" << endl;
}

void QLearning::printQValue() {
    for(int i = 1; i < NODENO; ++i)
        printf("%d\t", qValue_.get()[i]);

    printf("\n");
}

int QLearning::selectA() {

    int s;

    if(rand1() < EPSILON){
        if(rand01() == 0)
            s = 2 * status_ + 1;
        else
            s = 2 * status_ + 2;
    }
    else{
        if(qValue_.get()[2 * status_ + 1] > qValue_.get()[2 * status_ + 2])
            s = 2 * status_ + 1;
        else
            s = 2 * status_ + 2;
    }

    return s;

}

int QLearning::updated() {
    int qv;    // 要更新的q值
    int qmax;  // q值最大值

    if(status_ > 6){
        if(status_ == 14)
            qv = qValue_.get()[status_] + ALPHA * (1000 - qValue_.get()[status_]);
        else
            qv = qValue_.get()[status_];
    }
    else{
        if(qValue_.get()[2 * status_ + 1] > qValue_.get()[2 * status_ + 2])
            qmax = qValue_.get()[2 * status_ + 1];
        else
            qmax = qValue_.get()[2 * status_ + 2];
        qv = qValue_.get()[status_] + ALPHA * (GAMMA * qmax - qValue_.get()[status_]);
    }

    return qv;
}

void QLearning::Run() {

    for(int i = 0; i < GENMAX; ++i){
        status_ = 0; // 初始状态
        for(int t = 0; t < 3; ++t){
            status_ = selectA();
            qValue_.get()[status_] = updated();
        }
        printQValue();
    }
}
