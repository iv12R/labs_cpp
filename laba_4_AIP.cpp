#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

double perevod(string s){
    double x=0;
    if(s.size()==0){
        return 0;
    }
    else{
        if(s[0]=='0'){
            for (int i=2;i<s.size();i++){
                x+=(int(s[i])-48)*pow(10,-i+1);
            }
            return x;
        }
        else{
            for (int i=3;i<s.size();i++){
                x+=(int(s[i])-48)*pow(10,-i+2);
            }
            return -x;
        }

    }
}

bool odin(string s){
    if(s[0]=='0'){
        return 1;
    }
    else if((s[0]=='-')&&(s[1]=='0')){
        return 1;
    }
    else{
        return 0;
    }
}

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

bool desyat(string s){
    if(s[s.size()-1]=='1'){
        int x=0;
        for (int i=s.size()-2;i>1;i--){
            if(s[i]=='0'){
                x++;
            }
        }
        if(x==s.size()-3){
            return 1;
        }
        return 0;
    }
    else{
        return 0;
    }
}

double Fx(double x) {
    return 1.0 / ((1.0 + x) * (1.0 + x));
}

double fx(double x,double e){
    double fx1=1,fx2=-2*x,sum=fx1+fx2;
    int k=2;
    while(abs(fx2-fx1)>e){
        fx1=fx2;
        k++;
        fx2*=(((-1)*x*k)/(k-1));
        sum+=fx2;
    }
    return sum;
}

int main(){
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    string e1,xs1,xe1,dx1,xi1;
    double e=0,xs=0,xe=0,dx=0,xi=0;
    cout<<"epsilon: ";
    cin>>e1;
    while((!isnumber(e1))||(!(e1[0]=='0'))||(!desyat(e1))){
        cout<<"Неправильный ввод: ";
        cin>>e1;
    }
    e=perevod(e1);
    cout<<"x_start: ";
    cin>>xs1;
    while((!isnumber(xs1))||(!odin(xs1))){
        cout<<"Неправильный ввод: ";
        cin>>xs1;
    }
    xs=perevod(xs1);
    cout<<"x_end: ";
    cin>>xe1;
    while((!isnumber(xe1))||(!odin(xe1))||(!(xs<=perevod(xe1)))){
        cout<<"Неправильный ввод: ";
        cin>>xe1;
    }
    xe=perevod(xe1);
    cout<<"delta x: ";
    cin>>dx1;
    while((!isnumber(dx1))||(!odin(dx1))||(!(dx1!="0"))){
        cout<<"Неправильный ввод: ";
        cin>>dx1;
    }
    dx=perevod(dx1);
    cout<<"|"<<setw(10)<<"x"<<setw(10)<<"|"<<setw(12)<<"f(x)"<<setw(8)<<"|"<<setw(12)<<"F(x)"<<setw(8)<<"|"<<setw(13)<<"sigma"<<setw(7)<<"|"<<endl;
    cout<<" -------------------------------------------------------------------------------"<<endl;
    for (int i=0;i<((xe-xs)/dx);i++){
        cout<<"|"<<setw(10)<<xs+dx*i<<setw(10)<<"|"<<setw(12)<<fx(xs+dx*i,e)<<setw(8)<<"|"<<setw(12)<<Fx(xs+dx*i)<<setw(8)<<"|"<<setw(15)<<sqrt(abs(pow(fx(xs+dx*i,e),2)-pow(Fx(xs+dx*i),2)))<<setw(5)<<"|"<<endl;
        cout<<" -------------------------------------------------------------------------------"<<endl;
    }
    cout<<"x_ideal: ";
    cin>>xi1;
    while((!isnumber(xi1))||(!odin(xi1))){
        cout<<"Неправильный ввод: ";
        cin>>xi1;
    }
    xi=perevod(xi1);
    cout<<"|"<<setw(10)<<"e"<<setw(10)<<"|"<<setw(12)<<"f(x)"<<setw(8)<<"|"<<setw(12)<<"F(x)"<<setw(8)<<"|"<<setw(13)<<"sigma"<<setw(7)<<"|"<<endl;
    cout<<" -------------------------------------------------------------------------------"<<endl;
    for (int i=0;i<7;i++){
        cout<<"|"<<setw(10)<<fixed<<setprecision(7)<<pow(10,-(i+1))<<setw(10)<<"|"<<setw(10)<<fx(xi,pow(10,-(i+1)))<<setw(10)<<"|"<<setw(12)<<Fx(xi)<<setw(8)<<"|"<<setw(15)<<sqrt(abs(pow(fx(xi,pow(10,-(i+1))),2)-pow(Fx(xi),2)))<<setw(5)<<"|"<<endl;
        cout<<" -------------------------------------------------------------------------------"<<endl;
    }
    return 0;
}


/*#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Рядная функция f(x) = 1/(1+x)^2 с рекуррентной формулой
double series_f(double x, double eps, int& iterations) {
    // Первый член ряда: a_1 = 1
    double a_k = 1.0;      // текущий член ряда
    double sum = a_k;      // накопленная сумма
    iterations = 1;        // учли первый член

    double prev_sum = sum; // для условия остановки
    int k = 2;             // номер следующего члена

    while (true) {
        // Сохраняем предыдущую сумму для проверки условия
        prev_sum = sum;

        // Рекуррентная формула: a_k = a_{k-1} * (-x) * (k/(k-1))
        a_k *= -x * (static_cast<double>(k) / (k - 1));

        // Добавляем текущий член к сумме
        sum += a_k;
        iterations++;

        // Условие остановки: |f_k(x) - f_{k-1}(x)| < eps
        if (fabs(sum - prev_sum) < eps) {
            break;
        }

        k++;
    }

    return sum;
}

// Библиотечная функция F(x) = 1/(1+x)^2
double library_F(double x) {
    return 1.0 / ((1.0 + x) * (1.0 + x));
}

// Вычисление невязки delta по формуле (1)
double compute_delta(double f_val, double F_val) {
    return sqrt(fabs(f_val * f_val - F_val * F_val));
}

// Функция для вывода горизонтальной линии таблицы
void print_line(int width) {
    cout << string(width, '-') << endl;
}

int main() {
    double eps, x_start, x_end, step, x_ideal;

    // Ввод основных параметров
    cout << "Введите точность epsilon: ";
    cin >> eps;
    cout << "Введите начало интервала x_start: ";
    cin >> x_start;
    cout << "Введите конец интервала x_end: ";
    cin >> x_end;
    cout << "Введите шаг delta_x: ";
    cin >> step;

    // Таблица 1: вычисление на отрезке
    cout << "\n" << string(70, '=') << endl;
    cout << "Таблица 1: вычисление на отрезке [" << x_start << ", "
         << x_end << "] с шагом " << step << endl;
    cout << "Точность epsilon = " << eps << endl;
    print_line(70);

    cout << fixed << setprecision(8);
    cout << setw(12) << "x"
         << setw(15) << "f(x) ряд"
         << setw(15) << "F(x) библ"
         << setw(15) << "delta"
         << setw(10) << "итерации" << endl;
    print_line(70);

    // Вычисление и вывод для каждого x на отрезке
    for (double x = x_start; x <= x_end + 1e-9; x += step) {
        int iterations;
        double f_val = series_f(x, eps, iterations);
        double F_val = library_F(x);
        double delta = compute_delta(f_val, F_val);

        cout << setw(12) << x
             << setw(15) << f_val
             << setw(15) << F_val
             << setw(15) << delta
             << setw(10) << iterations << endl;
    }

    // Ввод x_ideal для детального анализа
    cout << "\n" << string(70, '=') << endl;
    cout << "Введите x_ideal для точного расчета: ";
    cin >> x_ideal;

    // Проверка корректности x_ideal (ряд сходится при |x| < 1)
    if (fabs(x_ideal) >= 1.0) {
        cout << "Внимание: ряд сходится только при |x| < 1!" << endl;
        cout << "Для |x| >= 1 результаты могут быть некорректными." << endl;
    }

    // Таблица 2: вычисление для x_ideal с разными точностями
    cout << "\n" << string(70, '=') << endl;
    cout << "Таблица 2: вычисление для x = " << x_ideal
         << " с разными значениями точности" << endl;
    print_line(70);

    cout << setw(12) << "epsilon"
         << setw(15) << "f(x) ряд"
         << setw(15) << "F(x) библ"
         << setw(15) << "delta"
         << setw(10) << "итерации" << endl;
    print_line(70);

    // Массив значений точности от 10^-1 до 10^-7
    double epsilons[] = {1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7};
    double F_ideal = library_F(x_ideal);  // точное значение один раз

    for (double e : epsilons) {
        int iterations;
        double f_val = series_f(x_ideal, e, iterations);
        double delta = compute_delta(f_val, F_ideal);

        // Для первой колонки используем scientific, для остальных fixed
        cout << scientific << setprecision(0) << setw(12) << e
             << fixed << setprecision(10)
             << setw(15) << f_val
             << setw(15) << F_ideal
             << setw(15) << delta
             << setw(10) << iterations << endl;
    }

    // Дополнительный анализ: сравнение значений
    cout << "\n" << string(70, '=') << endl;
    cout << "Анализ сходимости для x = " << x_ideal << ":" << endl;
    cout << "Библиотечное значение F(x) = " << fixed << setprecision(12)
         << F_ideal << endl;

    // Вычисление относительной погрешности для каждой точности
    cout << "\nОтносительная погрешность (|f-F|/|F|):" << endl;
    print_line(50);
    cout << setw(12) << "epsilon" << setw(20) << "отн. погрешность"
         << setw(15) << "delta" << endl;
    print_line(50);

    for (double e : epsilons) {
        int iterations;
        double f_val = series_f(x_ideal, e, iterations);
        double rel_error = fabs(f_val - F_ideal) / fabs(F_ideal);
        double delta = compute_delta(f_val, F_ideal);

        cout << scientific << setprecision(0) << setw(12) << e
             << fixed << setprecision(10)
             << setw(20) << rel_error
             << setw(15) << delta << endl;
    }

    return 0;
}



/*#include <bits/stdc++.h>

using namespace std;

// Рядная функция f(x) = 1/(1+x)^2
double series_f(double x, double eps, int& iterations) {
    double sum = 0.0;
    double prev_term = 0.0;
    double current_term;
    iterations = 0;

    int k = 1;
    while (true) {
        current_term = pow(-1, k-1) * k * pow(x, k-1);
        sum += current_term;
        iterations++;

        // Проверка условия сходимости (разность двух соседних членов)
        if (k > 1 && fabs(current_term - prev_term) < eps) {
            break;
        }

        prev_term = current_term;
        k++;
    }

    return sum;
}

// Библиотечная функция F(x) = 1/(1+x)^2
double library_F(double x) {
    return 1.0 / pow(1.0 + x, 2);
}

// Вычисление невязки delta
double compute_delta(double f_val, double F_val) {
    return sqrt(fabs(f_val * f_val - F_val * F_val));
}

int main() {
    double eps, x_start, x_end, step, x_ideal;

    // Ввод данных
    cout << "epsilon: ";
    cin >> eps;
    cout << "x_start: ";
    cin >> x_start;
    cout << "x_end: ";
    cin >> x_end;
    cout << "delta_x: ";
    cin >> step;

    // Таблица 1: вычисление на отрезке
    cout << "\nTable 1: [" << x_start << ", " << x_end << "] delta:" << step << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << setw(12) << "x"
         << setw(15) << "f(x)"
         << setw(15) << "F(x)"
         << setw(15) << "delta"
         << setw(10) << "i" << endl;
    cout << "----------------------------------------------------------------" << endl;

    for (double x = x_start; x <= x_end + 1e-9; x += step) {
        int iter;
        double f_val = series_f(x, eps, iter);
        double F_val = library_F(x);
        double delta = compute_delta(f_val, F_val);

        cout << fixed << setprecision(6)
             << setw(12) << x
             << setw(15) << f_val
             << setw(15) << F_val
             << setw(15) << delta
             << setw(10) << iter << endl;
    }

    // Ввод x_ideal
    cout << "\nВведите x_ideal для точного расчета: ";
    cin >> x_ideal;

    // Таблица 2: вычисление для x_ideal с разными eps
    cout << "\nТаблица 2: вычисление для x = " << x_ideal << " с разной точностью" << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << setw(12) << "epsilon"
         << setw(15) << "f(x) ряд"
         << setw(15) << "F(x) библ"
         << setw(15) << "delta"
         << setw(10) << "итерации" << endl;
    cout << "----------------------------------------------------------------" << endl;

    double eps_vals[] = {1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7};
    for (double e : eps_vals) {
        int iter;
        double f_val = series_f(x_ideal, e, iter);
        double F_val = library_F(x_ideal);
        double delta = compute_delta(f_val, F_val);

        cout << scientific << setprecision(1) << setw(12) << e
             << fixed << setprecision(10)
             << setw(15) << f_val
             << setw(15) << F_val
             << setw(15) << delta
             << setw(10) << iter << endl;
    }

    return 0;
}*/
