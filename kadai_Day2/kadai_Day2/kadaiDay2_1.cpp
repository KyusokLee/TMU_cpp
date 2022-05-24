//
//  kadaiDay2_1.cpp
//  kadai_Day2
//
//  Created by Kyus'lee on 2022/05/19.
//

#include <iostream>
#include <stdio.h>

using namespace std;

//Define Person Class
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

int main_1() {
    Person a;
    a.setPersonProperty(3, 15);
    a.showData();
    
    return 0;
}
