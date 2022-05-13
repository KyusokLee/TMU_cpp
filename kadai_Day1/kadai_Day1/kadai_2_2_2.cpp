//
//  kadai_2_2_2.cpp
//  kadai_Day1
//
//  Created by Kyus'lee on 2022/05/13.
//

#include <stdio.h>
#include <random>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

// rand()を用いて偏りのない[0,1]範囲の一様乱数を発生させる関数
double rnd_val2_2_2(int input) {
    double returnValue = (double(input) + 0.5) / (RAND_MAX + 1.0);
    return returnValue;
}

// サイコロクラス
class dice {
public:
    //コンストラクタ
    dice() {};
    //ディストラクタ
    ~dice() {};
    
    int ID;
    int value;
    
    int Roll() {
        value = rnd_val2_2_2(rand()) * 6 + 1;
        return value;
    }
};

// 課題2-2_2 (N個のサイコロの場合)(試行回数: 10000回)
// ファイル入出力あり
int main() {
    ofstream kadai2_2_2("kadai2_2_2.csv");
    kadai2_2_2 << "i番目" << "," << "サイコロの出る目の和" << endl;
    
    dice a;
    dice b;
    srand(20141106);
    
    double averagesum = 0;
    double sumA = 0;
    double sumB = 0;
    double stdDeviation = 0;
    int startcases = 10000;
    
    for (int i = 0; i < startcases; i++) {
        a.Roll();
        b.Roll();
        kadai2_2_2 << i << "," << a.value + b.value << endl;
        sumA += a.value;
        sumB += b.value;
    }
    
    kadai2_2_2.close();
    
    sumA /= startcases;
    sumB /= startcases;
    averagesum = (sumA + sumB) / 2;
    stdDeviation = sqrt((pow(sumA - averagesum, 2) + pow(sumB - averagesum, 2)) / 2);
    
    cout << "サイコロ2個の10回試行の平均値（期待値）: " << averagesum << endl;
    cout << "その標準偏差の平均値: " << stdDeviation << endl;
    
    return 0;
}
