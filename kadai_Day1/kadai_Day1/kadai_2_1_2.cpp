//
//  kadai_2_2.cpp
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
double rnd_val2_2(int input) {
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
        value = rnd_val2_2(rand()) * 6 + 1;
        return value;
    }
};

int main_2_1_2() {
    ofstream kadai2_1_2("kadai2_1_2.csv");
    
    dice a;
    dice b;
    srand(20141106);
    kadai2_1_2 << "i回試行" << "," << "平均値(期待値): " << endl;
    
    double sum = 0;
    int startcases = 100;
    
    while (startcases <= 10000) {
        for (int i = 0; i < startcases; i++) {
            a.Roll();
            b.Roll();
            sum += (a.value + b.value);
        }
        cout << startcases << "回試行の平均値（期待値）: " << sum / startcases << endl;
        kadai2_1_2 << startcases << "," << sum / startcases << endl;
        sum = 0;
        startcases += 100;
    }
    kadai2_1_2.close();
    
    return 0;
}
