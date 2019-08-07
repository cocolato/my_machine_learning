//
// Created by a0486470 on 2019-07-19.
//

#ifndef TMP_CLASSIFY_H
#define TMP_CLASSIFY_H

#include <iostream>
#include <vector>
#include <boost/random.hpp>

using namespace std;

vector<vector<int>> readData(const string& fileName);
int rand012();
int calcScore(vector<vector<int>> values, vector<int> teacher, vector<int> answer);


#endif //TMP_CLASSIFY_H
