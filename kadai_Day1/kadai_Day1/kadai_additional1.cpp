//
//  kadai_additional1.cpp
//  kadai_Day1
//
//  Created by Kyus'lee on 2022/05/17.
//

#include <stdio.h>
#include <random>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;
//[0,1] の一様乱数
// rand()を用いて偏りのない[0,1]範囲の一様乱数を発生させる関数
double rnd_val_additional(int putData) {
    double returnValue = (double(putData) + 0.5) / (RAND_MAX + 1.0);
    return returnValue;
}

int main(void)
{
    double x = 0.0; double y = 0.0; double z; double p;
    double count = 0.0; //円の内側に入った点の数
    int testCount;
    
    cout << "試行回数: ";
    cin >> testCount;
    srand(20141106);//乱数生成シードの設定
    
    for(int i = 1; i <= testCount; i++) {
        x = rnd_val_additional(rand());
        y = rnd_val_additional(rand());
        z = x * x + y * y;
        
        if (z < 1) {
            count++;
        }
    }
    p = count / testCount;
    p = p * 4;
    
    cout << "円周率の推定値: " << p << endl;
    cout << "(試行回数: " << testCount << ")" << endl;
    
    return 0;
}
