#include <iostream>
#include "matrix.h"
using namespace std;

int main() {
    int n,m,k,q;
    cout<<"Input first matrix size:\n";
    cin>>n>>m;
    matrix<int> a(n,m);
    cout<<"Input first matrix:\n";
    cin>>a;
    cout<<"Input second matrix size:\n";
    cin>>n>>m;
    matrix<int> b(n,m);
    cout<<"Input second matrix:\n";
    cin>>b;
    cout<<"Input an integer for multiplication:\n";
    cin>>k;
    cout<<"Input an integer for fast exponentiation:\n";
    cin>>q;
    try {
        cout << "Sum of matrices:\n" << a + b << endl;
    }
    catch(const char* msg){
        cerr<<"Exception caught: "<<msg<<endl;
    }
    cout<<"First matrix multiplied by "<<k<<":\n"<<a*k<<endl;
    try{
        cout<<"Multiplication of matrices:\n"<<a*b<<endl;
    }
    catch(const char* msg){
        cerr<<"Exception caught: "<<msg<<endl;
    }
    cout<<"Transposed first matrix:\n"<<a.transpose()<<endl;
    try{
        cout<<"First matrix raised to the "<<q;
        if(q%10==1){
            cout<<"st power:\n";
        }
        if(q%10==2){
            cout<<"nd power:\n";
        }
        if(q%10==3){
            cout<<"rd power:\n";
        }
        cout<<a.fastpow(q)<<endl;
    }
    catch(const char* msg){
        cerr<<"Exception caught: "<<msg<<endl;
    }
    return 0;
}
