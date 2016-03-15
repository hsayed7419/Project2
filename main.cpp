#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

int charToInt(char c){
    switch (c) {
        case '0':
        return 0;
        case '1':
        return 1;
        case '2':
        return 2;
        case '3':
        return 3;
        case '4':
        return 4;
        case '5':
        return 5;
        case '6':
        return 6;
        case '7':
        return 7;
        case '8':
        return 8;
        case '9':
        return 9;
        case '.':
        return -2;
        default:
        return -1;
    }
}

int stringToInt(string data) {
    int total = 0;
    for (int i = 0; i < data.size(); i++) {
        total += charToInt(data.at(i)) * pow(10, data.size() - i - 1);
    }
    return total;
}

float stringToFloat(string data){
    float total = 0;
    char c;
    int sub;
    string subString;
    int power = 0;  //x to the power of [power]
    for (int i = data.size() - 1; i >= 0; i--) {
        if (data.at(i) == '.'){
            break;
        }
        power++;
    }
    int i;
    for (i = data.size() - 1; i >= 0; i--){
        c = data.at(i);
        if ((sub = charToInt(c)) == -2){
            break;
        } 
        total += sub * pow(10, power * (-1));
    }
    total += stringToInt(data.substr(0, i - 1));
    return total;
}

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
    //reset the struct values
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
    //reset the struct values
    void clear(){
        month = 0;
        day = 0;
        year = 0;
    }
    // rip the integers from the string data
    void convertPubDate(string data){
        string temp;
        char c;
        int count = 0;
        for (int i = 0; i < data.size(); i++){
            c = data.at(i);
            if (c == ' '){
                switch (count){
                    case 0:
                    month = stringToInt(temp);
                    break;
                    case 1:
                    day = stringToInt(temp);
                    break;
                    case 2:
                    year = stringToInt(temp);
                    break;
                    default:
                    cout << "Error in Publication_date format" << endl;
                    break;
                }
                temp = "";
                count = 0;
            } else {
                temp += c;
                count++;
            }
        }
    }
};

struct Book {
    Publication_date pub;
    Author auth;
    string Title;
    float cost;
    int Type;
    void storeToStruct(string data, int type){
        switch (type){
            case 0:
            pub.convertPubDate(data);
            break;
            case 1:
            auth.convertAuthor(data);
            break;
            case 2:
            Title = data;
            break;
            case 3:
            convertCost(data);
            break;
            case 4:
            Type = stringToInt(data);
            break;
        }
    }
    //tests if all values have been filled
    bool isFull(){
        if (pub.isFull() && auth.isFull() 
            && (Title.size() > 0) && cost >= 0 && Type >= 0){
            return true;
        } else return false;
    }
    //reset the struct values
    void clear(){
        Title = "";
        cost = 0;
        Type = 0;
        pub.clear();
        auth.clear();
    }
};

void printStruct(Book book){
    cout << book.Title << endl;
}

int main(){
    string line, info;
    ifstream infile;
    Book temp;
    char c;
    int count
    // opens file to be read
    infile.open("record.dat");
    temp.clear();
    
    count = 0;
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