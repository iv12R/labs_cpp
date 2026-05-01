#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;
unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
mt19937 gen(seed);
uniform_int_distribution<int> poryadok(1,4);

struct res
{
    int srav=0;
    int peres=0;
};
res bubl,otbor,vstavka,fust,shel;

int M=0,N=0;
vector<vector<int>> vectr;
vector<vector<int>> vectrsort;
vector<vector<int>> revectr;

int randm(){
    int por = pow(10,poryadok(gen));
    uniform_int_distribution<int> chislo(1, por);
    return chislo(gen);
}

int srt(int num){
    int n=0;
    vector<int> chisla;
    while(num>0){
        chisla.push_back(num%10);
        num/=10;
    }
    sort(chisla.begin(),chisla.end(),greater<int>());
    for (int i=0;i<chisla.size();i++){
        n+=chisla[i]*pow(10,i);
    }
    return n;
}

void bublsort(vector<vector<int>>& vec){
    for(int a=0;a<N;a++){
        for(int i=0;i<M-1;i++){
            for(int j=0;j<M-i-1;j++){
                if(vec[a][j]<vec[a][j+1]){
                    swap(vec[a][j],vec[a][j+1]);
                    bubl.peres+=1;
                }
                bubl.srav+=1;

            }
        }
    }
}

void otborsort(vector<vector<int>>& vec){
    for(int a=0;a<N;a++){
        for(int i=0;i<M-1;i++){
            int mx_ind=i;
            for(int j=i+1;j<M;j++){
                if(vec[a][mx_ind]<vec[a][j]){
                    mx_ind=j;
                }
                otbor.srav+=1;
            }
            if(mx_ind!=i){
                otbor.peres+=1;
                swap(vec[a][i],vec[a][mx_ind]);
            }
        }
    }
}

void vstavkasort(vector<vector<int>>& vec){
    for(int a=0;a<N;a++){
        for(int i=1;i<M;i++){
            if(vec[a][i]<=vec[a][i-1]){
                vstavka.srav+=1;
            }
            else{
                for(int j=i;((j>0)&&(vec[a][j]>vec[a][j-1]));j--){
                    vstavka.srav+=1;
                    swap(vec[a][j],vec[a][j - 1]);
                    if((j-1>0)&&(vec[a][j-1]<vec[a][j-2])){
                        vstavka.srav+=1;
                    }
                }
                vstavka.peres+=1;
            }
        }
    }
}

void quicksort(vector<int>& vec, int start, int end){
    if(start<end){
        int p = vec[start];
        int i = start;
        for(int j=start+1;j<=end;j++){
            fust.srav+=1;
            if(vec[j]>=p){
                i+=1;
                if((j!=i)&&(vec[j]!=vec[i])){
                    swap(vec[j],vec[i]);
                    fust.peres+=1;
                }
            }
        }
        if((start!=i)&&(vec[start]!=vec[i])){
            swap(vec[start],vec[i]);
            fust.peres+=1;
        }
        quicksort(vec,start,i-1);
        quicksort(vec,i+1,end);
    }
}

void fustsort(vector<vector<int>>& vec){
    for(int a=0;a<N;a++){
        quicksort(vec[a],0,vec[a].size()-1);
    }
}

void shelsort(vector<vector<int>>& vec){
    for(int a=0;a<N;a++){
        for(int gap=M/2;gap>0;gap/=2){
            for(int i=gap;i<M;i++){
                int temp=vec[a][i];
                int j=i;
                while(j>=gap){
                    shel.srav+=1;
                    if(vec[a][j-gap]<temp){
                        vec[a][j]=vec[a][j-gap];
                        j-=gap;
                        shel.peres+=1;
                    }
                    else{
                        break;
                    }
                }
                if(j!=i){
                    vec[a][j]=temp;
                }
            }
        }
    }
}

bool proverka(string M1){
    int n=0;
    if(M1[0]!='0'){
        for(int i=0;i<M1.size();i++){
            if(isdigit(M1[i])){
                n+=1;
            }
        }
        if(n==M1.size()&&(M1.size()<=2)){
            return true;
        }
    }
    cout<<"Uncorrect input try again"<<endl;
    return false;
}

int main(){
    string M1;
    cout<<"M: ";
    cin>>M1;
    while(!proverka(M1)){
        cin>>M1;
    }
    M=stoi(M1);
    string N1;
    cout<<"N: ";
    cin>>N1;
    while(!proverka(N1)){
        cin>>N1;
    }
    N=stoi(N1);
    cout<<"M: "<<M<<" N: "<<N<<endl;
    vectr.resize(M, vector<int> (N,0));
    vectrsort.resize(M, vector<int> (N,0));
    revectr.resize(N,vector<int>(M,0));
    vector<vector<int>> vectrbubl(N,vector<int>(M,0));
    vector<vector<int>> vectrotbor(N,vector<int>(M,0));
    vector<vector<int>> vectrvstavka(N,vector<int>(M,0));
    vector<vector<int>> vectrfust(N,vector<int>(M,0));
    vector<vector<int>> vectrshel(N,vector<int>(M,0));
    for (int i=0;i<M;i++){
        for (int j=0;j<N;j++){
            vectr[i][j]=5;//randm();
            //cin>>vectr[i][j];
            vectrsort[i][j]+=srt(vectr[i][j]);
        }
    }
    
    for(int i=0;i<vectrsort[0].size();i++){
        for (int j=0;j<vectrsort.size();j++){
            revectr[i][j]+=vectrsort[j][i];
            vectrbubl[i][j]+=vectrsort[j][i];
            vectrotbor[i][j]+=vectrsort[j][i];
            vectrvstavka[i][j]+=vectrsort[j][i];
            vectrfust[i][j]+=vectrsort[j][i];
            vectrshel[i][j]+=vectrsort[j][i];
        }
    }
    bublsort(vectrbubl);
    otborsort(vectrotbor);
    vstavkasort(vectrvstavka);
    fustsort(vectrfust);
    shelsort(vectrshel);
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
    cout<<"right numbers"<<endl;
    cout<<" ";
    for(int i=0;i<N;i++){
        cout<<"-------";
    }
    cout<<endl;
    for (int i=0;i<M;i++){
        for (int j=0;j<N;j++){
            cout<<"|"<<setw(5);
            cout<<vectrsort[i][j]<<setw(2);
        }
        cout<<"|"<<endl;
        cout<<" ";
        for(int a=0;a<N;a++){
            cout<<"-------";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"bubl sort"<<endl;
    cout<<" ";
    for(int i=0;i<N;i++){
        cout<<"-------";
    }
    cout<<endl;
    for (int i=0;i<M;i++){
        for (int j=0;j<N;j++){
            cout<<"|"<<setw(5);
            cout<<vectrbubl[j][i]<<setw(2);
        }
        cout<<"|"<<endl;
        cout<<" ";
        for(int a=0;a<N;a++){
            cout<<"-------";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"selection sort"<<endl;
    cout<<" ";
    for(int i=0;i<N;i++){
        cout<<"-------";
    }
    cout<<endl;
    for (int i=0;i<M;i++){
        for (int j=0;j<N;j++){
            cout<<"|"<<setw(5);
            cout<<vectrotbor[j][i]<<setw(2);
        }
        cout<<"|"<<endl;
        cout<<" ";
        for(int a=0;a<N;a++){
            cout<<"-------";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"insertion sort"<<endl;
    cout<<" ";
    for(int i=0;i<N;i++){
        cout<<"-------";
    }
    cout<<endl;
    for (int i=0;i<M;i++){
        for (int j=0;j<N;j++){
            cout<<"|"<<setw(5);
            cout<<vectrvstavka[j][i]<<setw(2);
        }
        cout<<"|"<<endl;
        cout<<" ";
        for(int a=0;a<N;a++){
            cout<<"-------";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"quick sort"<<endl;
    cout<<" ";
    for(int i=0;i<N;i++){
        cout<<"-------";
    }
    cout<<endl;
    for (int i=0;i<M;i++){
        for (int j=0;j<N;j++){
            cout<<"|"<<setw(5);
            cout<<vectrfust[j][i]<<setw(2);
        }
        cout<<"|"<<endl;
        cout<<" ";
        for(int a=0;a<N;a++){
            cout<<"-------";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"Shell sort"<<endl;
    cout<<" ";
    for(int i=0;i<N;i++){
        cout<<"-------";
    }
    cout<<endl;
    for (int i=0;i<M;i++){
        for (int j=0;j<N;j++){
            cout<<"|"<<setw(5);
            cout<<vectrshel[j][i]<<setw(2);
        }
        cout<<"|"<<endl;
        cout<<" ";
        for(int a=0;a<N;a++){
            cout<<"-------";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<" --------------------------"<<endl;
    cout<<"|   sort    | "<<setw(3)<<"srav"<<setw(2)<<" | "<<setw(3)<<"peres|"<<endl;
    cout<<" --------------------------"<<endl;
    cout<<"|   bubl    | "<<setw(3)<<bubl.srav<<setw(3)<<"  | "<<setw(3)<<bubl.peres<<setw(3)<<"  |"<<endl;
    cout<<" --------------------------"<<endl;
    cout<<"| selection | "<<setw(3)<<otbor.srav<<setw(3)<<"  | "<<setw(3)<<otbor.peres<<setw(3)<<"  |"<<endl;
    cout<<" --------------------------"<<endl;
    cout<<"| insertion | "<<setw(3)<<vstavka.srav<<setw(3)<<"  | "<<setw(3)<<vstavka.peres<<setw(3)<<"  |"<<endl;
    cout<<" --------------------------"<<endl;
    cout<<"|   quick   | "<<setw(3)<<fust.srav<<setw(3)<<"  | "<<setw(3)<<fust.peres<<setw(3)<<"  |"<<endl;
    cout<<" --------------------------"<<endl;
    cout<<"|   Shell   | "<<setw(3)<<shel.srav<<setw(3)<<"  | "<<setw(3)<<shel.peres<<setw(3)<<"  |"<<endl;
    cout<<" --------------------------"<<endl;
    return 0;
}
