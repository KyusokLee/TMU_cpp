//
//  kadai1_3.cpp
//  kadai_Day1
//
//  Created by Kyus'lee on 2022/05/12.
//

#include "kadai1_2.hpp"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <random>
#include <math.h>

using namespace std;

int main_1_3() {
    ofstream kadai_1("kadai_1(lamda:2).csv");
    double rndUni[1001] = {0};
    double rndExp[1001] = {0};
    double sumAverage = 0.0;
    double sumUnia_b = 0.0;
    double sumExp = 0.0;
    
    int upperBound = 1000;
    srand(20141106); // シード: 学習番号
    kadai_1 << "i番目" << "," << "rndUni: " << "," << "rndExp: " << endl;
    for (int i = 0; i < upperBound; i++) {
        sumAverage += rnd_uni(1, 2, rnd_val1(rand()));
        rndUni[i] = rnd_uni(1, 2, rnd_val1(rand()));
        rndExp[i] = rnd_exp(2.0, rnd_val1(rand()));
        sumUnia_b += rndUni[i];
        sumExp += rndExp[i];
        kadai_1 << i << "," <<rndUni[i] << "," << rndExp[i] << endl;
    }

    kadai_1.close();
    
    sumAverage /= upperBound;
    sumUnia_b /= upperBound;
    sumExp /= upperBound;
    sumAverage = round(sumAverage * 100000) / 100000; //少数第6位を四捨五入
    sumUnia_b = round(sumUnia_b * 100000) / 100000;
    sumExp = round(sumExp * 100000) / 100000;
    cout << "求めた平均値:" << sumAverage << endl;
    cout << "一様分布乱数の平均値(a: 1, b: 2): " << sumUnia_b << endl;
    cout << "指数分布乱数の平均値(lamda: 0.5): " << sumExp << endl;
    
    return 0;
}
