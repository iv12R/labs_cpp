#include <bits/stdc++.h>

using namespace std;

struct Date{
    int d;
    int m;
    int y;
};
bool isfriday (Date& date){
    int res=0,k=0,j=0;
    k=date.y%100;
    j=date.y/100;
    res= (date.d+((13*(date.m+1))/5)+k+(k/4)+(j/4)-2*j)%7;//0 = Saturday, 1 = Sunday, 2 = Monday, ..., 6 = Friday
    if (res==6){
        return true;
    }
    else{
        return false;
    }
}

bool isLeapYear(Date& date) {
    return (date.y % 4 == 0 && date.y % 100 != 0) || (date.y % 400 == 0);
}

bool check(Date& date){
    return ((date.d==13)&&(isfriday(date)));
}

Date plus28(Date& date){
    date.d+=28;
    if((date.m==1)&&(date.d>31)){
        date.m+=1;
        date.d-=31;
    }
    else if((isLeapYear(date))&&(date.m==2)&&(date.d>29)){
        date.m+=1;
        date.d-=29;
    }
    else if((date.m==2)&&(date.d>28)){
        date.m+=1;
        date.d-=28;
    }
    else if((date.m==3)&&(date.d>31)){
        date.m+=1;
        date.d-=31;
    }
    else if((date.m==4)&&(date.d>30)){
        date.m+=1;
        date.d-=30;
    }
    else if((date.m==5)&&(date.d>31)){
        date.m+=1;
        date.d-=31;
    }
    else if((date.m==6)&&(date.d>30)){
        date.m+=1;
        date.d-=30;
    }
    else if((date.m==7)&&(date.d>31)){
        date.m+=1;
        date.d-=31;
    }
    else if((date.m==8)&&(date.d>31)){
        date.m+=1;
        date.d-=31;
    }
    else if((date.m==9)&&(date.d>30)){
        date.m+=1;
        date.d-=30;
    }
    else if((date.m==10)&&(date.d>31)){
        date.m+=1;
        date.d-=31;
    }
    else if((date.m==11)&&(date.d>30)){
        date.m+=1;
        date.d-=30;
    }
    else if((date.m==12)&&(date.d>31)){
        date.m=1;
        date.d-=31;
        date.y+=1;
    }
}

bool isValidDate(int day, int month, int year) {
    if (year < 1 || year > 9999) return false;
    if (month < 1 || month > 12) return false;
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (isLeap) {
            if (day < 1 || day > 29) return false;
        } else {
            if (day < 1 || day > 28) return false;
        }
    } else {
        if (day < 1 || day > daysInMonth[month - 1]) return false;
    }
    return true;
}

bool validateDateRegex(const std::string& input) {
    std::regex datePattern(R"(^\s*(\d{1,2})\.(\d{1,2})\.(\d{1,4})\s*$)");
    std::smatch matches;
    if (std::regex_match(input, matches, datePattern)) {
        try {
            int day = std::stoi(matches[1].str());
            int month = std::stoi(matches[2].str());
            int year = std::stoi(matches[3].str());
            return isValidDate(day, month, year);
        } catch (const std::exception& e) {
            return false;
        }
    }
    return false;
}

int main() {
    Date date;
    cout<<"Enter date DD.MM.YYYY"<<endl;
    string input;
    cin>>input;
    while(!((validateDateRegex(input))&&(input.size()==10))){
        cout<<"Uncorrect input try again"<<endl;
        cout<<"Enter date DD.MM.YYYY"<<endl;
        cin>>input;
    }
    cout<<"Correct input"<<endl;
    date.d=(input[0]-48)*10+(input[1]-48);
    date.m=(input[3]-48)*10+(input[4]-48);
    date.y=(input[6]-48)*1000+(input[7]-48)*100+(input[8]-48)*10+(input[9]-48);
    while(!check(date)){
        plus28(date);
    }
    cout<<"Result: "<<date.d<<"."<<date.m<<"."<<date.y<<endl;
    return 0;
}
/*
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <ctime>

bool isValidDate(int day, int month, int year) {
    // Проверяем корректность года, месяца и дня
    if (year < 1 || year > 9999) return false;
    if (month < 1 || month > 12) return false;

    // Проверяем количество дней в месяце
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Проверяем високосный год
    if (month == 2) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (isLeap) {
            if (day < 1 || day > 29) return false;
        } else {
            if (day < 1 || day > 28) return false;
        }
    } else {
        if (day < 1 || day > daysInMonth[month - 1]) return false;
    }

    return true;
}

bool validateDateRegex(const std::string& input) {
    // Регулярное выражение для проверки формата ДД.ММ.ГГГГ
    std::regex datePattern(R"(^\s*(\d{1,2})\.(\d{1,2})\.(\d{1,4})\s*$)");
    std::smatch matches;

    if (std::regex_match(input, matches, datePattern)) {
        try {
            int day = std::stoi(matches[1].str());
            int month = std::stoi(matches[2].str());
            int year = std::stoi(matches[3].str());

            return isValidDate(day, month, year);
        } catch (const std::exception& e) {
            return false;
        }
    }
    return false;
}

/*bool validateDateManual(const std::string& input) {
    // Ручной разбор строки
    std::string trimmed = input;

    // Удаляем пробелы в начале и конце
    size_t start = trimmed.find_first_not_of(" \t");
    size_t end = trimmed.find_last_not_of(" \t");

    if (start == std::string::npos) return false; // строка состоит только из пробелов

    trimmed = trimmed.substr(start, end - start + 1);

    // Ищем точки-разделители
    size_t dot1 = trimmed.find('.');
    if (dot1 == std::string::npos) return false;

    size_t dot2 = trimmed.find('.', dot1 + 1);
    if (dot2 == std::string::npos) return false;

    // Проверяем, что после второй точки нет других точек
    if (trimmed.find('.', dot2 + 1) != std::string::npos) return false;

    try {
        // Извлекаем части даты
        std::string dayStr = trimmed.substr(0, dot1);
        std::string monthStr = trimmed.substr(dot1 + 1, dot2 - dot1 - 1);
        std::string yearStr = trimmed.substr(dot2 + 1);

        // Проверяем, что все части состоят только из цифр
        for (char c : dayStr) if (!isdigit(c)) return false;
        for (char c : monthStr) if (!isdigit(c)) return false;
        for (char c : yearStr) if (!isdigit(c)) return false;

        // Преобразуем в числа
        int day = std::stoi(dayStr);
        int month = std::stoi(monthStr);
        int year = std::stoi(yearStr);

        return isValidDate(day, month, year);

    } catch (const std::exception& e) {
        return false;
    }
}

int main() {
    std::string input;

    std::cout << "Введите дату в формате ДД.ММ.ГГГГ: ";
    std::getline(std::cin, input);

    // Используем оба метода для проверки
    bool isValidRegex = validateDateRegex(input);
    //bool isValidManual = validateDateManual(input);

    // Для надежности проверяем обоими методами
    if (isValidRegex && isValidManual) {
        std::cout << "Correct: " << input << std::endl;
    } else {
        std::cout << "Uncorrect" << std::endl;
    }

    return 0;
}
*/
