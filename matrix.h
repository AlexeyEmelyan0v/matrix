#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <math.h>

using namespace std;

template <typename T>
class matrix {
    int n;
    int m;
    vector<vector<T>> data;
public:
    matrix(vector<vector<T>> a);

    matrix(int n1, int m1);

    int size() const { return n; };

    const matrix operator+(const matrix &) const;

    const matrix operator*(T) const;

    const matrix operator*(const matrix &) const;

    vector<T> &operator[](int i) { return data[i]; };

    const vector<T> &operator[](int i) const { return data[i]; };

    template<typename Type>
    friend istream &operator>>(istream &, matrix<Type> &);

    template<typename Type>
    friend ostream &operator<<(ostream &, const matrix<Type> &);

    const matrix transpose() const;

    const matrix fastpow(int) const;

    T det() const;

    const matrix<T> gauss() const;

    const matrix<T> idenmat() const;
};

template<typename T>
matrix<T>::matrix(vector<vector<T>> v) {
    data = v;
    n = v.size();
    m = v[0].size();
}

template<typename T>
matrix<T>::matrix(int n1,int m1) {
    n = n1;
    m = m1;
    vector<vector<T>> a(n, vector<T>(m, 0));
    data = a;
}

template<typename T>
ostream& operator<<(ostream& out, const matrix<T>& a) {
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[i].size(); j++) {
            out << a[i][j] << " ";
        }
        out << "\n";
    }
    return out;
}

template<typename T>
istream &operator>>(istream& in, matrix<T>& a) {
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[i].size(); j++) {
            in >> a[i][j];
        }
    }
    return in;
}

template<typename T>
const matrix<T> matrix<T>::operator+(const matrix& a) const {
    if (a.size() != n || a[0].size() != m) {
        throw "Matrices have different sizes";
    }
    vector<vector<T>> res(n, vector<T>(m));
    if (a.size() == n && a[0].size() == m) {
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
    vector<vector<T>> res(n, vector<T>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            res[i][j] = data[i][j] * k;
        }
    }
    return matrix(res);
}

template<typename T>
const matrix<T> matrix<T>::operator*(const matrix& a) const {
    if (m != a.size()) {
        throw "Matrices have wrong sizes for their multiplication";
    }
    vector<vector<T>> res(n, vector<T>(a.m));
    if (m == a.size()) {
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
    vector<vector<T>> res(m, vector<T>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = data[j][i];
        }
    }
    return matrix(res);
}

template<typename T>
const matrix<T> matrix<T>::fastpow(int k) const {
    matrix<int> res(data);
    matrix<int> value(data);
    int q = k - 1;
    if (n != m) {
        throw "First matrix isn't a square";
    }
    if (n == m) {
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

template<typename T>
T matrix<T>::det() const {
    if (n != m) {
        throw "First matrix isn't a square";
    }
    vector<int> p(n);
    T res = 0;
    if (n == m) {
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }

        int sl = 1;
        int sigma;
        for (int i = 0; i < n; i++) {
            sl *= data[i][p[i]];
        }
        res += sl;
        while (next_permutation(p.begin(), p.end())) {
            sigma = 0;
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    if (p[j] < p[i]) {
                        sigma++;
                    }
                }
            }
            sigma = sigma % 2;
            sl = 1;
            for (int i = 0; i < n; i++) {
                sl *= data[i][p[i]];
            }
            if (sigma % 2 == 0) {
                res += sl;
            } else {
                res -= sl;
            }
        }
    }
    return res;
}

template<typename T>
const matrix<T> matrix<T>::gauss() const {
    matrix<T> res(data);
    bool q = 1;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (q == 0) {
                break;
            }
            if (res[i][i] == 0) {
                int l = i;
                while (res[l][i] == 0) {
                    if (l == n - 1) {
                        q = 0;
                        throw "Bad matrix: determinant = 0";
                        break;
                    }
                    l++;
                }
                if (q == 0) {
                    break;
                }
                if (q && l < n && l != i) {
                    for (int p = i; p < m; p++) {
                        swap(res[i][p], res[l][p]);
                    }
                }
            }
            if (q) {
                double k = res[j][i] / res[i][i];
                for (int l = 0; l < m; l++) {
                    res[j][l] -= res[i][l] * k;
                }
            }
        }
        if (i == n - 1 && res[i][i] == 0) {
            q = 0;
        }
        if (q == 0) {
            break;
        }
    }
    if (q == 0) {
        throw "Bad matrix: determinant = 0";
    }
    return res;
}

template<typename T>
const matrix<T> matrix<T>::idenmat() const {
    matrix<T> res(n, m);
    if (n != m) {
        throw "wrong size";
    }
    if (n == m) {
        matrix<T> b(n, 2 * m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                b[i][j] = data[i][j];
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = m; j < 2 * m; j++) {
                if (i == j - m) {
                    b[i][j] = 1;
                } else {
                    b[i][j] = 0;
                }
            }
        }
        b = b.gauss();
        for (int i = n - 1; i >= 0; i--) {
            double k=1/b[i][i];
            for (int j = 0; j < 2 * m; j++) {
                b[i][j] *= k;
            }
            for (int j = 0; j < i; j++) {
                double k = b[j][i];
                for (int l = 0; l < 2 * m; l++) {
                    b[j][l] -= b[i][l] * k;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = m; j < 2 * m; j++) {
                res[i][j - m] = b[i][j];
            }
        }
    }
    return res;
}

#endif //MATRIX_MATRIX_H