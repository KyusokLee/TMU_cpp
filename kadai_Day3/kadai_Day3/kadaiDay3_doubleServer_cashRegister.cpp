//
//  kadaiDay3_doubleServer_cashRegister.cpp
//  kadai_Day3


// Simulation Experiment Day3_Assignments n.2
// レジ２台の実現 (Server : 2個)
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <random>
#include <math.h>
#include <time.h>
#include <queue>
#include <fstream>

using namespace std;

double rnd_val2(); //一様乱数
double rnd_exp2(double lambda); //指数分布乱数

//Person クラス
class Person {
public:
    int personID;
    double arrivalTime; //サーバーへの到着時間
    double departureTime; //サーバーからの退出時間
    int serverID;

    Person() {};
    ~ Person() {};

    void setPersonProperty(int _personID, double _arrivalTime, double _departureTime, int _serverID) {
        personID = _personID;
        arrivalTime = _arrivalTime;
        departureTime = _departureTime;
        serverID = _serverID;
    }

    // 確認を行うときのメソッド
    void showData() {
        cout << "ID: " << personID << endl;
        cout << "serverID: " << serverID << endl;
        cout << "Server Arrival Time: " << arrivalTime << endl;
        cout << "Server Departure Time: " << departureTime << endl;
    }
};


// Server クラス
class Server {
public:
    //メンバー変数
    int serverID;
    double mu; //平均サービス時間
    double finishTime; // 利用終了時間
    bool isAvailable = true;// 利用可能(受け入れ可能) Checkフラグ (最初は、お客さんを受入可能であるため、trueに初期化)
    // Person型のポインタ
    Person* personalData;
    // コンストラクター (initializer) : サーバークラスの初期化
    Server(int _ID, double _mu) {
        serverID = _ID; //受け取ったIDをメンバー関数に代入
        mu = _mu; //受け取ったパラメタをメンバ変数に代入
        finishTime = 0.0; // 利用終了時間の初期化
    };
    ~ Server() {}; // deinitializer

    int acceptPerson(double curTime, Person* _personalData) {
        if (isAvailable) {
            // 受け入れ可能のとき
            personalData = _personalData; //受け入れた客のポインタメンバ変数に代入
            personalData->serverID = serverID; //受け入れた客のServerIDにメンバ変数であるサーバーIDを書き込む
            finishTime = curTime + rnd_exp2(mu); //客の利用時間を計算 -> メンバ変数である利用終了時間を更新
            isAvailable = false; //客の利用が終了となってため、受け入れ不可能とする
            return 1; //受け入れ可能であることを通知
        } else {
            // 受け入れ可能でないとき
            _personalData->serverID = -1; //受け入れできなかった客のserverIDに -1代入
            _personalData->departureTime = -1; //受け入れできなかった客の退出時間に -1代入
            return 0; //受け入れ不可能であることを通知
        }
    }

    // メンバー関数: サーバー利用終了処理を行う関数
    void releaseServer(double curTime) {
        personalData->departureTime = curTime; //受け入れた客の退出時間を更新
        isAvailable = true; //客の受け入れを可能にする
    }
};

//Event　クラス
class Event {
public:
    int eventID; //イベント ID
    int eventType; //イベントの種類
    double eventOccurTime; //発生時刻
    Person *person; // Personオブジェクトのポインタ
    Server *server; // Serverオブジェクトのポインタ

    Event(int _eventID, double _eventOccurTime, int _eventType, Person* _person, Server* _server) {
        eventID = _eventID;
        eventOccurTime = _eventOccurTime;
        eventType = _eventType;
        person = _person;
        server = _server;
    }

    Event() {};
    ~ Event() {};

    bool operator<(const Event& event1) const {
        return eventOccurTime > event1.eventOccurTime;
    };
};

#define UNDEFINED -1
#define EVENT_ARRIVAL 0 //到着イベント
#define EVENT_FINISH 1 //処理終了イベント

int main() {
    priority_queue<Event> evPriorityQueue;
    srand((unsigned int)time(NULL)); //乱数生成シード: time間数を用いて現在時間をシードとして利用

    double lambda = 2.0; // lambdaの設定
    int numPerson = 0;
    const int totalPerson = 10000;
    double mu = 12.0; //サーバー利用時間のパラメタ.平均利用時間: 1 / mu
    int numServer = 2; //今回はserverを２台設ける

    Person *persons = new Person[totalPerson + 1];
    Server **svr;
    svr = new Server*[numServer];

    for (int i = 0; i < numServer; i++) {
        svr[i] = new Server(i, mu);
    }

    int eventID = 0;
    int request = 0; //サーバーに対して受入申請を出す。request = 0: 受入 OK, request = 1: 受入 X
    int lossCount = 0; //ロス数

    Event curEvent; // 現在のcurrent Eventを指すインスタンス
    Server* acceptedServer = NULL;

    persons[numPerson].setPersonProperty(numPerson, 0.0, UNDEFINED, UNDEFINED);
    // Eventの登録 (Queueのpush機能)
    evPriorityQueue.push(Event(eventID++, persons[numPerson].arrivalTime, EVENT_ARRIVAL, &persons[numPerson], NULL));

    //シミュレーション本体
    while (numPerson < totalPerson) {
        if (!evPriorityQueue.empty()) {
            curEvent = evPriorityQueue.top();
            evPriorityQueue.pop();
        } else {
            continue;
        }

        switch (curEvent.eventType)
        {
        case EVENT_ARRIVAL:
            request = 0;

            for (int i = 0; i < numServer; i++) {
                request = svr[i]->acceptPerson(curEvent.eventOccurTime, curEvent.person);

                if (request == 1) {
                    acceptedServer = svr[i];
                    break;
                }
            }

            if (request == 0) {
                lossCount++;
            } else {
                evPriorityQueue.push(Event(eventID++, acceptedServer->finishTime, EVENT_FINISH, curEvent.person, acceptedServer));
            }

            numPerson++;
            persons[numPerson].setPersonProperty(numPerson, curEvent.eventOccurTime + rnd_exp2(lambda), UNDEFINED, UNDEFINED);
            evPriorityQueue.push(Event(eventID++, persons[numPerson].arrivalTime, EVENT_ARRIVAL, &persons[numPerson], NULL));
            break;

        case EVENT_FINISH:
            curEvent.server->releaseServer(curEvent.eventOccurTime);
            break;
        }
    }

    // Emerge , Loss, Loss_rate
//    printf("emerge:%d, loss:%d, loss_rate:%f\n", numPerson, lossCount, (double)lossCount / (double)numPerson);
    cout << "Emerge: " << numPerson << endl;
    cout << "Loss: " << lossCount << endl;
    cout << "Loss_rate: " << (double)lossCount / (double)numPerson << endl;

    //終了処理
    for (int i = 0; i < numServer; i++) {
        delete svr[i];
    }

    delete [] svr;
    delete [] persons;

    return 0;
}

// rand()を用いて偏りのない[0,1]範囲の一様乱数を発生させる関数
double rnd_val2() {
    double returnValue = (double(rand()) + 0.5) / (RAND_MAX + 1.0);
    return returnValue;
}

// rnd_val()を用いた指数分布乱数
double rnd_exp2(double lambda) {
    return -1.0 / lambda * log(rnd_val2());
//    return (-1 * log(1.0 - rnd_val())) / lambda;
}
