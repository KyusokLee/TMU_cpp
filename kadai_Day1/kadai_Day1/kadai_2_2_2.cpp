//
//  kadai_2_2_2.cpp
//  kadai_Day1
//
//  Created by Kyus'lee on 2022/05/13.
//

#include <stdio.h>
#include <stdlib.h>
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
// N = 2 ~ 10までチェックした
// 中心極限利用
// ファイル入出力あり
int main() {
    FILE *kadai2_DICE_N = fopen("kadai2_2DICE_N", "wb");
    FILE *kadai2_frequency = fopen("kadai2_frequency", "wb");
    
    dice diceN;
    srand(20141106);
    
    int diceCount = 0; //サイコロの個数
    int count = 0; //試行回数
    int diceSum = 0; // n個のサイコロの和
    int startCases = 10000;
    int diceSumCount[61] = {0}; // 9個のサイコロの和の頻度を格納する配列 (0)に初期化
    double tempSum = 0.0; //２つのサイコロの和の合算 (試行回数をある値に固定したとき)
    double averageSum = 0.0; //２つのサイコロの和の平均 (試行回数をある値に固定したとき)
    
    for (diceCount = 2; diceCount <= 10; diceCount++) {
        for (count = 1; count <= startCases; count++) {
            tempSum = 0;
            for (int i = 1; i <= count; i++) {
                diceSum = 0;
                for (int j = 1; j <= diceCount; j++) {
                    diceN.Roll();
                    diceSum += diceN.value;
                }
                diceSumCount[diceSum] += 1;
                tempSum += diceSum;
            }
            averageSum = tempSum / count; //平均値を計算
            fprintf(kadai2_DICE_N, "%d, %d, %d, %f\n", diceCount, count, diceSum, averageSum);
            //サイコロの個数、試行回数、n個のサイコロの和、平均値を出力
        }
        
        for (int k = 0; k < 61; k++) {
            fprintf(kadai2_frequency, "%d, %d\n", k, diceSumCount[k]);
            diceSumCount[k] = 0;
        }
    }
    fclose(kadai2_DICE_N);
    fclose(kadai2_frequency);
    
    return 0;
}
