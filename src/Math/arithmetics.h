#pragma once
#include <xmmintrin.h>

template <class T>
T pow(T a, unsigned int b){
    if (!b) return 1;

    double res = a;
    while (--b) res *= a;
    return res;
}

double sqrt(double a){
    __m128d temp = _mm_set_sd(a);
    temp = _mm_sqrt_sd(temp, temp);
    return _mm_cvtsd_f64(temp);
}

template <class T>
T abs(T x){
    if (x < 0) return -x;
    return x;
}
