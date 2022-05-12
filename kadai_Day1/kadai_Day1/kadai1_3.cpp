//
//  kadai1_3.cpp
//  kadai_Day1
//
//  Created by Kyus'lee on 2022/05/12.
//

#include "kadai1_2.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

using namespace std;

int main() {
    FILE *fp = fopen("kadai1Graph", "wb");
    
    
    //区間(0,1)にある1000個の乱数を発生させ、求めた平均値を求めるプログラム
    double sum = 0.0;
    int upperBound = 1000;
    srand(20141106); // シード: 学習番号
    for (int i = 0; i < upperBound; i++) {
        sum += rnd_uni(1, 2, rnd_val1(rand()));
    }
    
    sum /= upperBound;
    sum = round(sum * 100000) / 100000; //少数第6位を四捨五入
    cout << "求めた平均値:" << sum << endl;
    
    return 0;
}
