#include <iostream>
#include "matrix.h"
#include <cstdio>

using namespace std;
int n,m;

void solution(matrix<double>& a) {
    matrix<double> g = a.gauss();
    vector<int> fv(m, 0);
    int cntfv = m;
    for (int i = 0; i < n; i++) {
        int j = 0;
        while (g[i][j] == 0) {
            if (j == m - 1) {
                break;
            }
            j++;
        }
        if (g[i][j] != 0) {
            fv[j] = 1;
            cntfv--;
        }
    }
    if (cntfv > 0) {
        cout << "Free variables: ";
        for (int i = 0; i < m; i++) {
            if (!fv[i]) {
                cout << "x" << i + 1 << " ";
            }
        }
        cout << endl;
    }
    for (int i = 0; i < n; i++) {
        int j = 0;
        while (g[i][j] == 0) {
            if (j == m - 1) {
                break;
            }
            j++;
        }
        if (g[i][j] != 0) {
            cout << "x" << j + 1 << " = " << g[i][m];
            for (int l = j + 1; l < m; l++) {
                if (g[i][l] != 0) {
                    cout << " - " << g[i][l] << " * x" << l + 1;
                }
            }
            cout << endl;
        }
    }
}


int main() {
    int t;
    freopen("input.txt","r",stdin);
    cin>>t;
    for(int i=0;i<t;i++){
        cin>>n>>m;
        matrix<double> a(n, m+1);
        cin>>a;
        cout<<"Case #"<<i+1<<endl;
        try {
            solution(a);
        }catch(const char *msg){
            cerr<<msg<<endl;
        }
        cout<<endl;
    }
    fclose(stdin);
    return 0;
}
