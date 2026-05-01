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
#include <windows.h>

using namespace std;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

bool isnumber(string s){
    if((s[0]=='0')||(s[0]=='-')){
        return 0;
    }
    else{
        int x=0;
        for (int i=0;i<s.size();i++){
            if(isdigit(s[i])){
                x++;
            }
        }
        if(x==s.size()){
            return 1;
        }
        return 0;
    }
}

int perevod(string s){
    int x=0;
    for (int i=0;i<s.size();i++){
        x+=(int(s[i])-48)*pow(10,s.size()-i-1);
    }
    return x;
}

bool nechet(string s){
    if((int(s[s.size()-1])-48)%2==1){
        return 1;
    }
    return 0;
}

void a(){
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO start_attribute;
	GetConsoleScreenBufferInfo(hStdOut, &start_attribute);
    SetConsoleTextAttribute(hStdOut, start_attribute.wAttributes);
}
int main(){
    a();
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand(time(0));
    int n=0;
    string n1;
    cout<<"N: ";
    cin>>n1;
    while((!isnumber(n1))||(!nechet(n1))){
        cout<<"������������ ����: "<<endl;
        cin>>n1;
    }
    n=perevod(n1);
    cout<<n<<endl;
    int **m=new int*[n];
    int **res=new int*[n];
    for (int i=0;i<n;i++){
        m[i]=new int[n];
        res[i]=new int[n];
        for (int j=0;j<n;j++){
            m[i][j]=rand()%100;
            res[i][j]=m[i][j];
        }
    }
    cout<<" ";
    for(int i=0;i<n;i++){
        cout<<"-----";
    }
    cout<<endl;
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            int color=15;
            if((i==j)&&(i==((n/2)))){
                color=5;
            }
            else if(i==j){
                color=1;
            }
            else if(i+j==n-1){
                color=2;
            }
            else if(i==((n/2))){
                color=3;
            }
            else if(j==((n/2))){
                color=4;
            }
            else{
                color=6;
            }
            cout<<"|"<<setw(3);
            setColor(color);
            cout<<m[i][j]<<setw(2);
            resetColor();
        }
        cout<<"|"<<endl;
        cout<<" ";
        for(int i=0;i<n;i++){
            cout<<"-----";
        }
        cout<<endl;
    }
    for(int i=0;i<n;i++){
        res[i][i]=m[i][n/2];
        res[i][n/2]=m[i][i];
        res[i][n-i-1]=m[n/2][n-i-1];
        res[n/2][n-i-1]=m[i][n-i-1];
    }
    cout<<" ";
    for(int i=0;i<n;i++){
        cout<<"-----";
    }
    cout<<endl;
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            int color=15;
            if((i==j)&&(i==((n/2)))){
                color=5;
            }
            else if(i==j){
                color=1;
            }
            else if(i+j==n-1){
                color=2;
            }
            else if(i==((n/2))){
                color=3;
            }
            else if(j==((n/2))){
                color=4;
            }
            else{
                color=6;
            }
            cout<<"|"<<setw(3);
            setColor(color);
            cout<<res[i][j]<<setw(2);
            resetColor();
        }
        cout<<"|"<<endl;
        cout<<" ";
        for(int i=0;i<n;i++){
            cout<<"-----";
        }
        cout<<endl;
    }
    for (int i = 0; i < n; i++) {
        delete[] m[i];
        delete[] res[i];
    }
    delete[] m;
    delete[] res;
    return 0;
}
/*#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h> // ��� �������� ������ � Windows

using namespace std;

// ������� ��� ��������� ����� ������ � �������
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// ������� ��� �������������� ����� �� ���������
void resetColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand(time(NULL));

    int N;
    cout << "������� �������� N (����������� �������): ";
    cin >> N;

    if (N % 2 == 0) {
        cout << "N ������ ���� ��������. ������� �����: ";
        cin >> N;
    }

    int K;
    cout << "������� K (�������� ��������� ����� [-K; K]): ";
    cin >> K;

    // �������� �������
    int **A = new int*[N];
    for (int i = 0; i < N; i++) {
        A[i] = new int[N];
    }

    // ���������� ���������� �������
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % (2 * K + 1) - K;
        }
    }

    int center = N / 2; // ������ ����������� ������ � �������

    cout << "\n������ � ����������� ����������:\n";
    cout << "�����:\n";
    cout << "� ������� ��������� - �������\n";
    cout << "� �������� ��������� - �������\n";
    cout << "� ������� ������ - �������\n";
    cout << "� ������� ������� - ������\n";
    cout << "� ����������� - ����������\n";
    cout << "� ��������� - �����\n\n";

    // ����� ������� � ���������� ������
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            bool isMainDiagonal = (i == j);
            bool isSecondaryDiagonal = (i + j == N - 1);
            bool isCenterRow = (i == center);
            bool isCenterCol = (j == center);

            // ���������� ���� ��������
            int color;

            // ��������� ����������� (����� ������� ����������)
            if (isMainDiagonal && isSecondaryDiagonal && isCenterRow && isCenterCol) {
                // ����������� ������� (����������� �����)
                color = 13; // ����������
            }
            else if ((isMainDiagonal && isCenterCol) ||
                     (isSecondaryDiagonal && isCenterRow) ||
                     (isMainDiagonal && isCenterRow) ||
                     (isSecondaryDiagonal && isCenterCol)) {
                // ����������� ���� �����
                color = 13; // ����������
            }
            else if (isMainDiagonal) {
                color = 10; // �������
            }
            else if (isSecondaryDiagonal) {
                color = 12; // �������
            }
            else if (isCenterRow) {
                color = 11; // �������
            }
            else if (isCenterCol) {
                color = 14; // ������
            }
            else {
                color = 15; // �����
            }

            setColor(color);
            printf("%4d", A[i][j]);
            resetColor();
        }
        cout << endl;
    }

    // ������� � ����� ����������
    cout << "\n���������� � ���������� ���������:\n";
    cout << "=================================\n";

    // ������� ���������
    cout << "������� ��������� (i = j): ";
    setColor(10);
    for (int i = 0; i < N; i++) {
        cout << A[i][i];
        if (i < N - 1) cout << ", ";
    }
    resetColor();
    cout << endl;

    // �������� ���������
    cout << "�������� ��������� (i + j = N-1): ";
    setColor(12);
    for (int i = 0; i < N; i++) {
        cout << A[i][N - 1 - i];
        if (i < N - 1) cout << ", ";
    }
    resetColor();
    cout << endl;

    // ������� ������
    cout << "������� ������ (������ " << center << "): ";
    setColor(11);
    for (int j = 0; j < N; j++) {
        cout << A[center][j];
        if (j < N - 1) cout << ", ";
    }
    resetColor();
    cout << endl;

    // ������� �������
    cout << "������� ������� (������� " << center << "): ";
    setColor(14);
    for (int i = 0; i < N; i++) {
        cout << A[i][center];
        if (i < N - 1) cout << ", ";
    }
    resetColor();
    cout << endl;

    // ������������ ������
    for (int i = 0; i < N; i++) {
        delete[] A[i];
    }
    delete[] A;

    cout << "\n���� ������� ������������.\n";

    return 0;
}
*/
