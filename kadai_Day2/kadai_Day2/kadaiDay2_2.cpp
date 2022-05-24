//
//  kadaiDay2_2.cpp
//  kadai_Day2
//
//  Created by Kyus'lee on 2022/05/19.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <cmath>
#include <ctime>
#include <queue>
#include <fstream>

using namespace std;

double rnd_val();
double rnd_exp(double lambda);

//Person クラス
class Person {
private:
    int ID;

public:
    double arrivalTime;
    
    Person() {};
    ~ Person() {};
    
    void setPersonProperty(int personalID, int personalArrivalTime) {
        ID = personalID;
        arrivalTime = personalArrivalTime;
    }
    
    void showData() {
        cout << "ID: " << ID << endl;
        cout << "到着時間: " << arrivalTime << endl;
    }
};

int main() {
    srand((unsigned int)time(NULL)); //乱数生成シード: time間数を用いて現在時間をシードとして利用
    
    const int totalPerson = 10000; // 総客数: 10000人に固定
    double currentTime = 0.0;
    double lambda; // 到着時間間隔のパラメータ  (平均到着時間: 1 / lambda)
    int personNum = 0; // 客の番号 (到着個数)
    
    cout << "lambda: ";
    cin >> lambda;
    
    // Personクラス型の配列定義 (要素数: 総客数) (new演算子　-> メモリ動的確保
    Person *personData = new Person[totalPerson];
    
    for (personNum = 0; personNum < totalPerson; personNum++) {
        personData[personNum].setPersonProperty(personNum, currentTime);
        currentTime += rnd_exp(lambda); //指数分布乱数を用いて、現在時刻を更新する
    }
    
    cout << "Final Arrival Time: " << currentTime << endl;
    
    //単位時間あたりの到着個数を集計
    currentTime = floor(currentTime);
    int *arrayA = new int[currentTime + 1];
    int time;
    
    for (int i = 0; i < totalPerson; i++) {
        time = floor(personData[i].arrivalTime);
        arrayA[time]++;
    }
    
    //ヒストグラム集計
    int arrayF[100] = {0};
    for (int i = 0; i < currentTime + 1; i++) {
        arrayF[arrayA[i]]++;
    }
    
    //データをヒストグラムで表す (ファイル出力)
    // arrayF[]に格納されているのは、単位時間あたりの到着個数
    // 設定したlambdaごとに名前を変えて保存した
    ofstream kadaiDay2_2("kadaiDay2_2(lambda: 8).csv");
    
    // 到着個数を30までにした (100くらいまでにすると、グラフが小さくなるため)
    for (int i = 0; i < 32; i++) {
        kadaiDay2_2 << i << "," << arrayF[i] << endl;
    }
    
    kadaiDay2_2.close();
    
    delete[] personData; //メモリのdeinit
    delete[] arrayA; //メモリのdeinit
    
    return 0;
}

// rand()を用いて偏りのない[0,1]範囲の一様乱数を発生させる関数
double rnd_val() {
    double returnValue = (double(rand()) + 0.5) / (RAND_MAX + 1.0);
    return returnValue;
}

// rnd_val()を用いた指数分布乱数
double rnd_exp(double lambda) {
    return (-1 * log(1.0 - rnd_val())) / lambda;
}
