//
// Created by a0486470 on 2019-07-22.
//

#ifndef TMP_RAND_H
#define TMP_RAND_H

#include <random>
#include <memory>

using namespace std;

int rand100();  // 返回0~100的随机函数
int rand01();   // 返回0，1随机数
double rand1(); // 返回0~1之间随机数
int randInt(int min, int max);
int randN(int n);
double Percentile(vector<double> Distr, double per);
template <typename T>
shared_ptr<T> make_shared_array(size_t size)
{
    //default_delete是STL中的默认删除器
    return shared_ptr<T>(new T[size], default_delete<T[]>());
}





#endif //TMP_RAND_H
