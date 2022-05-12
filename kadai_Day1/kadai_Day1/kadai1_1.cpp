//
//  main.cpp
//  kadai_Day1
//
//  Created by Kyus'lee on 2022/05/12.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <random>

//#include <iomanip> // Input Output Manipulator : 入出力の調整を行うライブラリ
// iomanip　代表的な提供関数
//      setw(): 出力のスペース調整
//      setbase(): ?進数の設定可能 (8, 10, 16進数のみ可能)
//      setprecision(): 浮動小数点の有効数字の設定 (.を除いた全体の数字の個数で判断)

using namespace std;
double rnd_val(int putData);

int main_1() {
    //区間(0,1)にある1000個の乱数を発生させ、求めた平均値を求めるプログラム
    double sum = 0.0;
    int upperBound = 1000;
    srand(20141106); // シード: 学習番号
    for (int i = 0; i < upperBound; i++) {
        sum += rnd_val(rand());
    }
    
    sum /= upperBound;
    sum = round(sum * 100000) / 100000; //少数第6位を四捨五入
    cout << "求めた平均値:" << sum << endl;
    
    return 0;
}

// rand()を用いて偏りのない[0,1]範囲の一様乱数を発生させる関数
double rnd_val(int putData) {
    double returnValue = (double(putData) + 0.5) / (RAND_MAX + 1.0);
    return returnValue;
}
