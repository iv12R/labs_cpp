#include <iostream>
#include <bits/stdc++.h>

using namespace std;

bool isnumber(string num){
    int i=0;
    for (int q=0;q<num.size();q++){
        if(isdigit(num[q])){
            i+=1;
        }
    }
    if(i==num.size()){
        return true;
    }
    return false;
}

bool ogr(string num){
    if(num.size()>10){
        return 0;
    }
    else if((num.size()==10 )&&(int(num[0])-48>2)){
        return 0;
    }
    return 1;
}
int main(){
    vector <string> word;
    vector <string> res;
    string words;
    string file;
    string num;
    int number=0,i=0;
    cout<<"file:";
    cin>>file;
    while(!(file.substr(file.size()-4)==".txt")){
        cout<<"Uncorrect input"<<endl;
        cin>>file;
    }
    ifstream in(file);
    getline(in,words);
    //cout<<words<<endl;
    cout<<"NUMBER:";
    cin>>num;
    while((!isnumber(num))||(!ogr(num))){
        cout<<"Uncorrect input"<<endl;
        cin>>num;
    }
    /*while(!(isdigit(num))){
        cout<<"Uncorrect input"<<endl;
        cin>>num;
    }*/
    for(int i=0;i<num.size();i++){
        number+=(int(num[i])-48)*pow(10,num.size()-i-1);
    }
    cout<<number<<" "<<num<<endl;
    while(i<words.size()){
        int i0=i;
        while(i+1<words.size() and words[i+1]!=' '){
            i++;
        }
        word.push_back(words.substr(i0,i-i0+1));
        i+=2;
    }
    for (int r=0;r<word.size();r++){
        res.push_back(word[r].substr(word[r].size()-number%word[r].size(),number%word[r].size())+word[r].substr(0,word[r].size()-number%word[r].size()));
        cout<<res[r]<<" ";
    }
    return 0;
}
