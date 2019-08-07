//
// Created by a0486470 on 2019-07-22.
//

#ifndef TMP_QLEARNING_H
#define TMP_QLEARNING_H

#include <iostream>
#include "rand.h"

using namespace std;

#define GENMAX 1000 // 学习次数
#define NODENO 15   // Q值的节点数
#define ALPHA 0.1   // 学习系数
#define GAMMA 0.9   // 折扣率
#define EPSILON 0.3 // 确定行动选择的随机性

void printQValue(int qValue[NODENO]);    // 输出Q值
int selectA(int olds, int qValue[NODENO]);  // 行动选择
int updated(int s, int qValue[NODENO]);  // 更新Q值

class QLearning{
private:
    int status_;  // 状态
    int nodeNum_;
    double alpha_;
    double gamma_;
    int genMAX_;
    double epsilon_;
    shared_ptr<int> qValue_;
    int selectA();
    int updated();
public:
    explicit QLearning(int nodeNum=15, double alpha=0.1, double gamma=0.9, double epsilon=0.3);
    ~QLearning();

    void printQValue();
    void Run();
};

#endif //TMP_QLEARNING_H
