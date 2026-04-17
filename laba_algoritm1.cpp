#include <bits/stdc++.h>

using namespace std;

bool isnumber(string s){
    if(s[0]=='-'){
        if(s[1]=='0'){
            if((s[2]=='.') && (s.size()>3)){
                for(int i=3;i<s.size();i++){
                    if(!isdigit(s[i])){
                        return 0;
                    }
                }
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            for(int i=1;i<s.size();i++){
                if(!isdigit(s[i])){
                    return 0;
                }
            }
            return 1;
        }
    }
    else{
        if(s[0]=='0'){
            if(s.size()==1){
               return 1;
            }
            else if((s[1]=='.') && (s.size()>2)){
                for(int i=2;i<s.size();i++){
                    if(!isdigit(s[i])){
                        return 0;
                    }
                }
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            for(int i=0;i<s.size();i++){
                if(!isdigit(s[i])){
                    return 0;
                }
            }
            return 1;
        }
    }
}

void f(int number, double a,double x){
    if((sin(x)>=0.5)&&(a!=sqrt(sin(x)-0.5))){
        double func=2/(a-sqrt(sin(x)-0.5));
        cout << "---------------------------------------------\n";
        cout << "|" << setw(10) << number;
        cout << "|" << setw(10) << x;
        cout << "|" << setw(10) << a;
        cout << "|" << setw(10) << func;
        cout << "|\n";
    }
    else{
        cout << "---------------------------------------------\n";
        cout << "|" << setw(10) << number;
        cout << "|" << setw(10) << x;
        cout << "|" << setw(10) << a;
        cout << "|" << setw(10) << "Err";
        cout << "|\n";
    }
}

double x1 = -12,x2=-7,x3=0.5;
string s;
int main(){
    double a=0;
    int coun=1;
    cout<<"Enter a"<<endl;
    cin>>s;
    cout << "---------------------------------------------\n";
    cout << "|" << setw(10) << "number";
    cout << "|" << setw(10) << "x";
    cout << "|" << setw(10) << "a";
    cout << "|" << setw(10) << "Err";
    cout << "|\n";

    if(!isnumber(s)){
        for (double i=x1;i<=x2;i+=x3){
            cout << "---------------------------------------------\n";
            cout << "|" << setw(10) << coun;
            cout << "|" << setw(10) << i;
            cout << "|" << setw(10) << "None";
            cout << "|" << setw(10) << "Err";
            cout << "|\n";
            coun++;
        }
        cout << "---------------------------------------------\n";
        return 0;
    }
    a=stod(s);
    if((a>1000000)||(a<-1000000)||((a>-0.000001)&&(a<0.000001)&&(a!=0))){
        for (double i=x1;i<=x2;i+=x3){
            cout << "---------------------------------------------\n";
            cout << "|" << setw(10) << coun;
            cout << "|" << setw(10) << i;
            cout << "|" << setw(10) << "None";
            cout << "|" << setw(10) << "Err";
            cout << "|\n";
            coun++;
        }
        cout << "---------------------------------------------\n";
        return 0;
    }
    for (double i=x1;i<=x2;i+=x3){
        f(coun,a,i);
        coun+=1;
    }
    cout << "---------------------------------------------\n";
    return 0;
}
