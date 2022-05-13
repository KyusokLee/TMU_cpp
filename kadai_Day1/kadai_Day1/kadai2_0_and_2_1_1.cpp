//
//  kadai2_0.cpp
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

using namespace std;

// rand()を用いて偏りのない[0,1]範囲の一様乱数を発生させる関数
double rnd_val2(int input) {
    double returnValue = (double(input) + 0.5) / (RAND_MAX + 1.0);
    return returnValue;
}

// 課題2-0: サイコロクラス
class dice {
public:
    //コンストラクタ
    dice() {};
    //ディストラクタ
    ~dice() {};
    
    int ID;
    int value;
    
    int Roll() {
        value = rnd_val2(rand()) * 6 + 1;
        return value;
    }
};

int main_2_1() {
    dice a;
    dice b;
    srand(20141106);
    int sum = 0;
    int testcases = 10;
    
    //課題2_1 (試行回数10までする)
    for (int i = 0; i < testcases; i++) {
        a.Roll();
        b.Roll();
        cout << "サイコロa: " << a.value << endl;
        cout << "サイコロb: " << b.value << endl;
        sum += (a.value + b.value);
    }
    
    cout << sum / testcases << endl;
    return 0;
}
