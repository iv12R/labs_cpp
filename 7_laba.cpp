#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>
#include <fstream>

using namespace std;
unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
mt19937 gen(seed);
uniform_int_distribution<int> poryadok(1,4);

int M=0,N=0,value=0,srav_pos=0,srav_bin=0,st=1,checker=10,steps_straight=0,steps_center=0,steps_reverse=0;
string choise;
int choice=0;
string filename;
ofstream file;
ostream* output = &cout;
vector<vector<int>> vectr;
vector<int> vectrr;
vector<int> vectrrsort;
vector<vector<int>> tree; //значение и индекс в изначальном массиве

bool proverka1(string M1){
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

bool proverka2(string M1){
    int n=0;
    for(int i=0;i<M1.size();i++){
        if(isdigit(M1[i])){
            n+=1;
        }
    }
    if((n==M1.size())&&(stoi(M1)<100)){
        return true;
    }
    cout<<"Uncorrect input try again"<<endl;
    return false;
}

int randm(){
    int por = pow(10,poryadok(gen));
    uniform_int_distribution<int> chislo(1, por);
    return chislo(gen);
}

bool check_pos(int q){
    int num=vectrr[q];
    while((num!=0)&&(to_string(num).size()>=st)){
        srav_pos+=1;
        if(num%checker==value){
            return true;
        }
        num/=10;
    }
    return false;
}

int binsearch(){
    int m=0,s=0,e=vectrrsort.size()-1;
    while(e-s>0){
        srav_bin+=1;
        m=(s+e)/2;
        if(vectrrsort[m]>=value){
            e=m;
        }
        else{
            s=m+1;
        }
    }
    if(vectrrsort[s]==value){
        return s;
    }
    return -1;
}

void buildtree(int n, int s,int e){
    if (s > e) return;
    int m=(s+e)/2;
    tree[n][0]=vectrrsort[m];
    tree[n][1]=m;
    buildtree(2*n+1,s,m-1);
    buildtree(2*n+2,m+1,e);
}

void printTree() {
    *output<<"Дерево (индекс: значение):"<<endl;
    int l=0,ll=0;
    for (int i = 0; i < tree.size(); i++) {
        if (tree[i][0] != -1) {
            *output<<"  ["<<i<<"]:"<<tree[i][0];
            if(i==ll){
                *output<<endl;
                l+=1;
                ll=ll+pow(2,l);
            }
        }
    }
    *output<<endl;
}

int searchstraight(int i){
    if(i>=tree.size()||tree[i][0]==-1){
        return -1;
    }
    steps_straight+=1;
    *output<<"Шаг "<<steps_straight<<" Проверка "<<tree[i][0]<<" "<<i<<endl;
    if(tree[i][0]==value){
        return tree[i][1];
    }
    int res=searchstraight(2*i+1);
    if(res!=-1){
        return res;
    }
    return searchstraight(2*i+2);
}

int searchreverse(int i){
    if(i>=tree.size()||tree[i][0]==-1){
        return -1;
    }
    int resl=searchreverse(2*i+1);
    if(resl!=-1){
        return resl;
    }
    int resr=searchreverse(2*i+2);
    if(resr!=-1){
        return resr;
    }
    steps_reverse+=1;
    *output<<"Шаг "<<steps_reverse<<" Проверка "<<tree[i][0]<<" "<<i<<endl;
    if(tree[i][0]==value){
        return tree[i][1];
    }
    return -1;
}

int searchcenter(int i){
    if (i >= tree.size() || tree[i][0] == -1){
        return -1;
    }
    int resl = searchcenter(2*i+1);
    if (resl!=-1){
        return resl;
    }
    steps_center++;
    *output<<"Шаг "<<steps_center<<" Проверка "<<tree[i][0]<<" "<<i<<endl;
    if (tree[i][0]==value){
        return i;
    }
    return searchcenter(2*i+2);
}

bool fileExists(string& filenam) {
    ifstream file(filenam);
    return file.good();
}

int main(){
    cout<<"ВЫберите куда выводить файл. 1 - консоль. 2 - файл."<<endl;
    cin>>choise;
    while(choise!="1" && choise!="2"){
        cout<<"Uncorrect input"<<endl;
        cin>>choise;
    }
    choice=stoi(choise);
    if(choice==2){
        cout<<"Файл куда выводить: ";//надо добавить в папку с кодом
        cin>>filename;
        while((!(filename.substr(filename.size()-4)==".txt"))||(!fileExists(filename))){
            cout<<"Uncorrect input try again"<<endl;
            cin>>filename;
        }
        file.open(filename);
        output = &file;
    }
    else{
        cout<<"Вывод в консоль"<<endl;
    }
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
    *output<<"M: "<<M<<" N: "<<N<<endl;
    vectr.resize(M,vector<int>(N,0));
    for (int i=0;i<M;i++){
        for (int j=0;j<N;j++){
            vectr[i][j]+=randm();
            //cin>>vectr[i][j];
            vectrr.push_back(vectr[i][j]);
            vectrrsort.push_back(vectr[i][j]);
        }
    }
    sort(vectrrsort.begin(),vectrrsort.end());
    tree.resize(vectrr.size()*2, vector<int> (2,-1));
    *output<<"vector"<<endl;
    *output<<" ";
    for(int i=0;i<N;i++){
        *output<<"-------";
    }
    *output<<endl;
    for (int i=0;i<M;i++){
        for (int j=0;j<N;j++){
            *output<<"|"<<setw(5);
            *output<<vectr[i][j]<<setw(2);
        }
        *output<<"|"<<endl;
        *output<<" ";
        for(int a=0;a<N;a++){
            *output<<"-------";
        }
        *output<<endl;
    }
    *output<<endl;
    *output<<"sorted vector"<<endl;
    *output<<" ";
    for(int i=0;i<vectrrsort.size();i++){
        *output<<"-------";
    }
    *output<<endl;
    for (int i=0;i<1;i++){
        for (int j=0;j<vectrrsort.size();j++){
            *output<<"|"<<setw(5);
            *output<<vectrrsort[j]<<setw(2);
        }
        *output<<"|"<<endl;
        *output<<" ";
        for(int a=0;a<vectrrsort.size();a++){
            *output<<"-------";
        }
        *output<<endl;
    }
    *output<<endl;
    string value1;
    cout<<"Search value: ";
    cin>>value1;
    while(!proverka2(value1)){
        cin>>value1;
    }
    value=stoi(value1);
    *output<<"Search value: "<<value<<endl;
    if(value>9){
        st=2;
        checker=100;
    }
    int f=0;
    for(int i=0;i<vectrr.size();i++){
        if(check_pos(i)){
            *output<<"Индекс: "<<i<<" Значение: "<<vectrr[i]<<" Количество сравнений: "<<srav_pos<<endl;
            f+=1;
        }
    }
    if(f==0){
        *output<<"Число не найдено. Количество сравнений: "<<srav_pos<<endl;
    }
    *output<<endl;
    int res=binsearch();
    if(res!=-1){
        *output<<"Search value found, srav: "<<srav_bin<<endl;
    }
    else{
        *output<<"Search value not found, srav: "<<srav_bin<<endl;
    }
    *output<<endl;
    buildtree(0,0,vectrrsort.size()-1);
    //printTree();
    int res1=searchstraight(0);
    if(res1!=-1){
        *output<<"Результат: "<<res1<<" Значение: "<<vectrrsort[res1]<<" Шаги: "<<steps_straight<<endl;
        *output<<endl;
    }
    else{
        *output<<"Результат: число не найдено. Шаги: "<<steps_straight<<endl;
        *output<<endl;
    }
    int res2=searchreverse(0);
    if(res2!=-1){
        *output<<"Результат: "<<res2<<" Значение: "<<vectrrsort[res2]<<" Шаги: "<<steps_reverse<<endl;
        *output<<endl;
    }
    else{
        *output<<"Результат: число не найдено. Шаги: "<<steps_reverse<<endl;
        *output<<endl;
    }
    int res3=searchcenter(0);
    if(res3!=-1){
        *output<<"Результат: "<<res3<<" Значение: "<<vectrrsort[res3]<<" Шаги: "<<steps_center<<endl;
        *output<<endl;
    }
    else{
        *output<<"Результат: число не найдено. Шаги: "<<steps_center<<endl;
        *output<<endl;
    }
    return 0;
}