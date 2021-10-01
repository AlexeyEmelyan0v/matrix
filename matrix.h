#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

template <typename T>
class matrix{
    int n;
    int m;
    vector<vector<T>> data;
public:
    matrix(vector<vector<T>>);
    matrix(int n1,int m1);
    int size() const { return n; };
    const matrix operator+(const matrix&) const;
    const matrix operator*(T) const;
    const matrix operator*(const matrix&) const;
    vector<T>& operator[](int i){ return data[i]; };
    const vector<T>& operator[](int i) const { return data[i]; };
    template<typename Type> friend istream& operator>>(istream&, matrix<Type>&);
    template<typename Type> friend ostream& operator<<(ostream&, const matrix<Type>&);
    const matrix transpose() const;
    const matrix fastpow(int) const;
};

template<typename T>
matrix<T>::matrix(vector<vector<T>> v) {
    data=v;
    n=v.size();
    m=v[0].size();
}

template<typename T>
matrix<T>::matrix(int n1,int m1) {
    n=n1;
    m=m1;
    vector<vector<T>> a(n,vector<T>(m,0));
    data=a;
}

template<typename T>
ostream& operator<<(ostream& out, const matrix<T>& a) {
    for(int i=0;i<a.size();i++) {
        for (int j = 0; j < a[i].size(); j++) {
            out << a[i][j] << " ";
        }
        out << "\n";
    }
    return out;
}

template<typename T>
istream &operator>>(istream& in, matrix<T>& a) {
    for(int i=0;i<a.size();i++) {
        for (int j = 0; j < a[i].size(); j++) {
            in >> a[i][j];
        }
    }
    return in;
}

template<typename T>
const matrix<T> matrix<T>::operator+(const matrix& a) const {
    if(a.size()!=n || a[0].size()!=m){
        throw "Matrices have different sizes";
    }
    vector<vector<T>> res(n,vector<T>(m));
    if(a.size()==n && a[0].size()==m) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res[i][j] = data[i][j] + a[i][j];
            }
        }
    }
    return matrix(res);
}

template<typename T>
const matrix<T> matrix<T>::operator*(T k) const {
    vector<vector<T>> res(n,vector<T>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            res[i][j]=data[i][j]*k;
        }
    }
    return matrix(res);
}

template<typename T>
const matrix<T> matrix<T>::operator*(const matrix& a) const {
    if(m!=a.size()){
        throw "Matrices have wrong sizes for their multiplication";
    }
    vector<vector<T>> res(n,vector<T>(a.m));
    if(m==a.size()) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < a.m; j++) {
                for (int r = 0; r < m; r++) {
                    res[i][j] += data[i][r] * a[r][j];
                }
            }
        }
    }
    return matrix(res);
}

template<typename T>
const matrix<T> matrix<T>::transpose() const {
    vector<vector<T>> res(m,vector<T>(n));
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            res[i][j]=data[j][i];
        }
    }
    return matrix(res);
}

template<typename T>
const matrix<T> matrix<T>::fastpow(int k) const{
    matrix<int> res(data);
    matrix<int> value(data);
    int q=k-1;
    if(n!=m){
        throw "First matrix isn't a square";
    }
    if(n==m) {
        while (q > 0) {
            if (q % 2 == 1) {
                res = res * value;
                q--;
            } else {
                q /= 2;
                value = value * value;
            }
        }
    }
    return res;
}

#endif //MATRIX_MATRIX_H
