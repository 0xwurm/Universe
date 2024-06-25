#pragma once
#include "arithmetics.h"

enum Axes{
    X, Y, Z
};

template <int D, class T = double>
class Vector{
private:
    T data[D];

public:
    template <typename... A>
    explicit Vector(A... args) :
        data{args...}
    {};
    explicit Vector(T args[D]) :
        data{}
    {
        for (int i = 0; i < D; i++)
            data[i] = args[i];
    };

    T length(){
        return sqrt(*this * *this);
    }

    // dot product
    T operator*(Vector<D, T> vector2) {
        T res{};
        for (int i = 0; i < D; i++)
            res += data[i] * vector2.data[i];
        return res;
    }
    Vector<D, T> operator+(Vector<D, T> vector2){
        T res_data[D];
        for (int i = 0; i < D; i++)
            res_data[i] = data[i] + vector2[i];
        return Vector<D, T>(res_data);
    }
    Vector<D, T> operator-(Vector<D, T> vector2){
        T res_data[D];
        for (int i = 0; i < D; i++)
            res_data[i] = data[i] - vector2.data[i];
        return Vector<D, T>(res_data);
    }
    Vector<D, T>& operator+=(Vector<D, T> vector2){
        for (int i = 0; i < D; i++)
            data[i] += vector2.data[i];
        return *this;
    }
    Vector<D, T>& operator-=(Vector<D, T> vector2){
        for (int i = 0; i < D; i++)
            data[i] -= vector2.data[i];
        return *this;
    }
    Vector<D, T> operator-(){
        T res_data[D];
        for (int i = 0; i < D; i++)
            res_data[i] = -data[i];
        return Vector<D, T>(res_data);
    }
    Vector<D, T> operator/(T scalar){
        return 1/scalar * *this;
    }
    template <class U>
    Vector<D, T>& operator*=(U scalar){
        for (int i = 0; i < D; i++)
            data[i] *= scalar;
        return *this;
    }

    template <class A, int B, class C>
    friend Vector<B, C> operator*(A, Vector<B, C>);

    template <int B, class C>
    friend C squared_magnitude(Vector<B, C>);

    T& operator[](int i){
        return data[i];
    }

};

template <class U, int D, class T>
Vector<D, T> operator*(U scalar, Vector<D, T> vector){
    T res_data[D];
    for (int i = 0; i < D; i++)
        res_data[i] = vector.data[i] * scalar;
    return Vector<D, T>(res_data);
}


template <int D, class T>
T squared_magnitude(Vector<D, T> vector){
    return vector * vector;
}
