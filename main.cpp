#include <iostream>
#include <fstream>

using namespace std;

struct Book {
    struct Publication_date;
    struct Author;
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
        if (Publication_date && Author && Title && cost && Type){
            return true;
        } else return false;
    }
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

bool parse(string line, struct Book book) {
    string substring;
    int dataCount = 0;
    for (int i = 0; i < line.size(); i++){
        if (line.at(i) == ' '){
            //do something with the line
            dataCount++;
        } else {
            substring += line.at(i);
        }
    }
}

void printStruct(struct Book book){
    
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
            if (count == 4){
                //line has been created
                cout << " " << endl;
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