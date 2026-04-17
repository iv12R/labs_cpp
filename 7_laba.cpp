#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>
#include <iomanip>

using namespace std;
unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
mt19937 gen(seed);
uniform_int_distribution<int> poryadok(1,4);

int M=0,N=0,value=0;
vector<vector<int>> vectr;

bool proverka1(string M1){
    int n=0;
    if(M1[0]!='0'){
        for(int i=0;i<M1.size();i++){
            if(isdigit(M1[i])){
                n+=1;
            }
        }
        if(n==M1.size()){
            return true;
        }
    }
    cout<<"Uncorrect input try again"<<endl;
    return false;
}

bool proverka2(string M1){
    int n=0;
    if(M1[0]!='0'){
        for(int i=0;i<M1.size();i++){
            if(isdigit(M1[i])){
                n+=1;
            }
        }
        if((n==M1.size())&&(stoi(M1)<100)){
            return true;
        }
    }
    cout<<"Uncorrect input try again"<<endl;
    return false;
}

int randm(){
    int por = pow(10,poryadok(gen));
    uniform_int_distribution<int> chislo(1, por);
    return chislo(gen);
}

int main(){
    string M1;
    cout<<"M: ";
    cin>>M1;
    while(!proverka1(M1)){
        cin>>M1;
    }
    M=stoi(M1);
    string N1;
    cout<<"N: ";
    cin>>N1;
    while(!proverka1(N1)){
        cin>>N1;
    }
    N=stoi(N1);
    cout<<"M: "<<M<<" N: "<<N<<endl;
    vectr.resize(M,vector<int>(N,0));
    for (int i=0;i<M;i++){
        for (int j=0;j<N;j++){
            vectr[i][j]+=randm();
            //cin>>vectr[i][j];
        }
    }
    cout<<"vector"<<endl;
    cout<<" ";
    for(int i=0;i<N;i++){
        cout<<"-------";
    }
    cout<<endl;
    for (int i=0;i<M;i++){
        for (int j=0;j<N;j++){
            cout<<"|"<<setw(5);
            cout<<vectr[i][j]<<setw(2);
        }
        cout<<"|"<<endl;
        cout<<" ";
        for(int a=0;a<N;a++){
            cout<<"-------";
        }
        cout<<endl;
    }
    cout<<endl;
    string value1;
    cout<<"Search value: ";
    cin>>value1;
    while(!proverka2(value1)){
        cin>>value1;
    }
    value=stoi(value1);
    cout<<"Search value: "<<value<<endl;
    return 0;
}