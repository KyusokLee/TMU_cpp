//
//  kadai1_3.hpp
//  kadai_Day1
//
//  Created by Kyus'lee on 2022/05/12.
//

#ifndef kadai1_2_hpp
#define kadai1_2_hpp

#include <stdio.h>
#include <random>
#include <stdlib.h>
#include <cmath>
//逆間数方を用いた乱数生成の方法

// rand()を用いて偏りのない[0,1]範囲の一様乱数を発生させる関数
double rnd_val1(int putData) {
    double returnValue = (double(putData) + 0.5) / (RAND_MAX + 1.0);
    return returnValue;
}

//[a, b]の２変数を引数として受け取る一様分布
double rnd_uni(int a, int b, double getValue) {
    return a + (b - a) * getValue;
}

double rnd_exp(double lamda, double getValue) {
    return (-1 * log(1.0 - getValue)) / lamda;
}

#endif /* kadai1_2_hpp */
