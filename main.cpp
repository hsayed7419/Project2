#include <iostream>
#include <fstream>

using namespace std;

struct Book {
    struct Publication_date;
    struct Author;
    string Title;
    float cost;
    int Type;
};

struct Author {
    string First_name;
    string Middle_name;
    string Last_name;
};

struct Publication_date {
    int month;
    int day;
    int year;
};

bool parseAndStore(string line, struct Book book) {
    for (
    line.at(i)
}

void printStruct(struct Book book){
    cout << book.Publication_date.day << endl;
}

int main(){
    string line;
    ifstream infile;
    // opens file to be read
    infile.open("record.dat");
    char c;
    do {
        infile.get(c);
        if (c == '\n'){
            //line has been created
            cout << line << endl;
            line = "";
            continue;
        }
        line += c;
    } while (c != EOF);
    infile.close();
}