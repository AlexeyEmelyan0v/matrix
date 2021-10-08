#include <iostream>
#include "matrix.h"
#include <cassert>
using namespace std;
int n,m;
int x,y;
vector<double> solution(matrix<double>& a) {
    if (n != m - 1) {
        throw "wrong size";
    }
    vector<double> sol(n, 0);
    vector<double> b(n);
    matrix<double> g(n, m);
    if (n == m - 1) {
        g = a.gauss();
        for (int i = 0; i < n; i++) {
            b[i] = g[i][m - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            double str = b[i];
            for (int j = n - 1; j > i; j--) {
                str -= sol[j] * g[i][j];
            }
            sol[i] = str / g[i][i];
        }
    }
    return sol;
}

int main() {
    cout << "Input size of 1st matrix:\n";
    cin >> n >> m;
    matrix<double> a(n, m);
    cout << "Input matrix of system of equations:\n";
    cin >> a;
    cout << "Input size of 2nd matrix:\n";
    cin >> x >> y;
    matrix<double> b(x, y);
    cout << "Input matrix to find identity matrix:\n";
    cin >> b;
    vector<double> sol;
    try {
        cout << "Solution:\n";
        sol = solution(a);
        for (int i = 0; i < sol.size(); i++) {
            cout << sol[i] << "\n";
        }
    }
    catch (const char *msg) {
        cerr << "Exception caught: " << msg << endl;
    }
    try {
        cout<<"Identity matrix:\n";
        cout<<b.idenmat()<<endl;
    }
    catch (const char *msg) {
        cerr << "Exception caught: " << msg << endl;
    }
    return 0;
}
