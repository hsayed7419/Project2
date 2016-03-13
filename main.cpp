#include <iostream>

using namespace std;

struct Book {
    struct Publication_date;
    struct Author;
    string Title;
    float cost;
    int Type;
}

struct Author {
    string First_name;
    string Middle_name;
    string Last_name;
}

struct Publication_date {
    int month;
    int day;
    int year;
}

int main(){
    
}