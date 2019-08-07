//
// Created by a0486470 on 2019-07-19.
//

#include "classify.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

#define SEED 32767

using namespace std;

vector<vector<int>> readData(const string& fileName) {

    ifstream ReadFile;
    int row = 0;
    string tmp;
    vector<vector<int>> values;

    ReadFile.open(fileName, ios::in|ios::out);

    if (ReadFile.fail()) {
        cout << "Error!" << endl;
    }
    else {
        while (getline(ReadFile, tmp, '\n')) {
            ++row;
            vector<int> vec;
            for(auto& a: tmp){
                vec.push_back(a - '0');
            }
            values.push_back(vec);
        }
        ReadFile.close();
    }

    return values;
}

/* 计算一致程度 */
int calcScore(vector<vector<int>> values, vector<int> teacher, vector<int> answer){
    int score = 0;
    int point;

    for(int i = 0; i < values.size(); ++i){
        point = 0;

        for(int j = 0; j < values[0].size(); ++j){
            if(answer[j] == 2)
                ++point;
            else if(answer[j] == values[i][j])
                ++point;
        }

        if((point == values[0].size()) && (teacher[i] == 1))
            ++score;
        else if((point != values[0].size()) && (teacher[i] == 0))
            ++score;
    }

    return score;
}


int rand012(){
    int rnd;

    while((rnd=rand()) == RAND_MAX);

    return (double)rnd/RAND_MAX*3;
}
