#include <iostream>
#include <fstream>

using namespace std;

struct Book {
    struct Publication_date pub;
    struct Author auth;
    string Title;
    float cost;
    int Type;
    void storeToStruct(string data, int type){
        switch (type){
            case 0:
            convertPubDate(data);
            break;
            case 1:
            convertAuthor(data);
            break;
            case 2:
            convertTitle(data);
            break;
            case 3:
            convertCost(data);
            break;
            case 4:
            convertType(data);
            break;
        }
    }
    bool isFull(){
        if (pub.isFull() && auth.isFull() 
            && (Title.size() > 0) && cost >= 0 && Type >= 0){
            return true;
        } else return false;
    }
    void clear(){
        Title = "";
        cost = 0;
        Type = 0;
        pub.clear();
        auth.clear();
    }
};

struct Author {
    string First_name;
    string Middle_name;
    string Last_name;
    bool isFull(){
        if ((First_name.size() > 0) && (Middle_name.size() > 0) 
            && (Last_name.size() > 0))
            return true;
        else 
            return false;
    }
    void clear(){
        First_name = "";
        Middle_name = "";
        Last_name = "";
    }
};

struct Publication_date {
    int month;
    int day;
    int year;
    bool isFull(){
        if ((month > 0) && (day > 0) && (year > 0))
            return true;
        else 
            return false;
    }
    void clear(){
        month = 0;
        day = 0;
        year = 0;
    }
};

void printStruct(struct Book book){
    cout << book.Title << endl;
}

int main(){
    string line, info;
    ifstream infile;
    struct Book temp;
    // opens file to be read
    infile.open("record.dat");
    char c;
    int count = 0;
    do {
        infile.get(c);
        if (c == '\n'){
            if (temp.isFull()){
                //line has been created
                printStruct(temp);
                count = 0;
                line = "";
                continue;
            }
            temp.storeToStruct(line, count);
            line = "";
            count++;
            continue;
        }
        line += c;
    } while (c != EOF);
    infile.close();
}