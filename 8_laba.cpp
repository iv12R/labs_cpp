#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>

using namespace std;

struct zapis
{
    string surname, name, patronymic, number;
};

vector<vector<zapis>> table(21);

hash<string> hash_fn;

bool fileExists(string& filenam) {
    ifstream file(filenam);
    return file.is_open();
}

bool proverka(string v){
    if((v.size()==15)&&(v[0]=='+')&&(v[1]=='7')&&(isdigit(v[2]))&&(isdigit(v[3]))&&(isdigit(v[4]))&&(v[5]=='-')&&(isdigit(v[6]))&&(isdigit(v[7]))&&(isdigit(v[8]))&&(v[9]=='-')&&(isdigit(v[10]))&&(isdigit(v[11]))&&(v[12]=='-')&&(isdigit(v[13]))&&(isdigit(v[14]))){
        return true;
    }
    return false;
}

int main(){
    string filename;
    cout<<"Filename: ";
    cin>>filename;
    while((!(filename.substr(filename.size()-4)==".txt"))||(!fileExists(filename))){
        cout<<"Uncorrect input try again"<<endl;
        cin>>filename;
    }
    string line;
    ifstream file(filename);
    while(getline(file,line)){
        //cout<<line<<endl;
        stringstream ss(line);
        zapis a;
        getline(ss,a.surname,';');
        getline(ss,a.name,';');
        getline(ss,a.patronymic,';');
        getline(ss,a.number,';');
        auto ind=hash_fn(a.number)%table.size();
        //cout<<ind<<" "<<hash_fn(a.number)<<endl;
        table[ind].push_back(a);
    }
    file.close();
    cout<<"Table created"<<endl;
    // for (int i=0;i<table.size();i++){
    //     for (int j=0;j<table[i].size();j++){
    //         cout<<table[i][j].surname<<";"<<table[i][j].name<<";"<<table[i][j].patronymic<<";"<<table[i][j].number<<" ";
    //     }
    //     cout<<endl;
    // }
    string number;
    cout<<"Search number: ";
    cin>>number;
    while(!proverka(number)){
        cout<<"Uncorrect input try again"<<endl;
        cin>>number;
    }
    cout<<"Search number: "<<number<<endl;
    auto ind=hash_fn(number)%table.size();
    if(table[ind].empty()){
        cout<<"Number not found"<<endl;
    }
    else{
        for(int i=0;i<table[ind].size();i++){
            if(table[ind][i].number==number){
                cout<<"Number found"<<endl;
                cout<<"Correct number: "<<table[ind][i].surname<<" "<<table[ind][i].name<<" "<<table[ind][i].patronymic<<" "<<table[ind][i].number<<endl;
            }
            else{
                cout<<"Error happened"<<endl;
                cout<<"Uncorrect number: "<<table[ind][i].surname<<" "<<table[ind][i].name<<" "<<table[ind][i].patronymic<<" "<<table[ind][i].number<<endl;
            }
        }
    }
    return 0;
}