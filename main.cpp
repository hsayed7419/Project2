#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

#define LIB_SIZE 10
#define DEBUG false

using namespace std;

/* Used to simplify the stoi call
 * Will not compile in MinGW v 1.7-1.9
 */
int stringToInt(string data) {
	size_t *size = 0;
	return stoi(data, size, 10);
}

/* Used to simplify the stof call
 * Will not compile in MinGW v 1.7-1.9
 */
float stringToFloat(string data) {
	size_t *size = 0;
	return stof(data, size);
}

// Struct to stor the author struct inside
struct Author {
	string First_name;
	string Middle_name;
	string Last_name;
    
    // Inate function to determine if all of the values inside this struct have been set
	bool isFull() {
		if ((First_name.length() > 0) && (Middle_name.length() > 0)
			&& (Last_name.length() > 0))
			return true;
		else
			return false;
	}
    
	// Reset the struct values
	void clear() {
		First_name.clear();
		Middle_name.clear();
		Last_name.clear();
	}
    
    // Used to extract the authors first, middle, and last name
	void convertAuthor(string data) {
		string temp;
		char c;
		int count = 0;
		for (unsigned int i = 0; i < data.length(); i++) {
			if ((c = data.at(i)) == ' ') {
				switch (count) {
				case 0:
					First_name = temp;
					break;
				case 1:
					Middle_name = temp;
					break;
				default:
					cout << "Error in Author name format" << endl;
				}
				count++;
                temp.clear();
			}
			else {
				temp += c;
			}
		}
        Last_name = temp;
	}
};

// Struct used to store the publication date in
struct Publication_date {
	int month;
	int day;
	int year;
    
    // Inate function used to test if each variable in the struct have been set
	bool isFull() {
		if ((month >= 0) && (day >= 0) && (year >= 0))
			return true;
		else {
			return false;
		}
	}
    
	//reset the struct values
	void clear() {
		month = -1;
		day = -1;
		year = -1;
	}
    
	// rip the integers from the string data
	void convertPubDate(string data) {
		string temp;
		char c;
		int count = 0;
		int yearAt = 0;
		for (unsigned int i = 0; i < data.length(); i++) {
			c = data.at(i);
			if (c == ' ') {
				switch (count) {
				case 0:
					month = stringToInt(temp);
					break;
				case 1:
					day = stringToInt(temp);
					yearAt = i;
					break;
				default:
					cout << "Error in Publication_date format" << endl;
					break;
				}
				temp.clear();
				count++;
			}
			else {
				temp += c;
			}
		}
		year = stringToInt(data.substr(yearAt, data.length() - yearAt));
	}
};

// Struct to store all information of each book in
struct Book {
	Publication_date pub;
	Author auth;
	string Title;
	float cost;
	int Type;
    
    // Sorts each line and stores to the proper variable/struct
	void storeToStruct(string data, int type) {
		switch (type) {
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
			cost = stringToFloat(data);
			break;
		case 4:
			Type = stringToInt(data);
			break;
		default:
			cout << "Error in Book structure" << endl;
		}
	}
    
	//tests if all values have been filled
	bool isFull() {
		if (pub.isFull() && auth.isFull()
			&& (Title.length() > 0) && cost >= 0.0 && Type >= 0) {
			return true;
		}
        return false;
	}
    
	//reset the struct values
	void clear() {
		Title.clear();
		cost = -1;
		Type = -1;
		pub.clear();
		auth.clear();
	}
};

// Copies each variable to the struct since struct = struct does not work
void copyStruct(Book saveto, Book book){
    saveto.pub.month = book.pub.month;
    saveto.pub.day = book.pub.day;
    saveto.pub.year = book.pub.year;
    saveto.auth.First_name = book.auth.First_name;
    saveto.auth.Middle_name = book.auth.Middle_name;
    saveto.auth.Last_name = book.auth.Last_name;
    saveto.Title = book.Title;
    saveto.cost = book.cost;
    saveto.Type = book.Type;
}

// Ouputs the array of structures into a file "grouped_record.dat"
void writeStruct(Book book[]) {
    ofstream out;
    out.open("grouped_record.dat");
    if (out.is_open() && DEBUG){
        cout << "Write open was a success" << endl;
    }
    
    int numBooks = 0;
    for (int i = 0; i < LIB_SIZE; i++) {
        if (!book[i].isFull()) break;
        else numBooks++;
    }
    
    Book temp;
    temp.clear();
    for (int i = 0; i < numBooks; i++){
        for (int j = 1; j < numBooks; j++) {
            if (book[j - 1].Type < book[j].Type) {
                continue;
            } else {
                copyStruct(temp, book[j - 1]);
                copyStruct(book[j - 1], book[j]);
                copyStruct(book[j], temp);
            }
        }
    }
    
    for(int i = 0; i < numBooks; i ++) {
        out << "Publication_date: " << book[i].pub.month << " " << book[i].pub.day << " " << book[i].pub.year << endl;
        out << "Author: " << book[i].auth.First_name << " " << book[i].auth.Middle_name << " " 
            << book[i].auth.Last_name << endl;
        out << "Title: " << book[i].Title << endl;
        out << "Cost: " << book[i].cost << endl;
        out << "Type: " << book[i].Type << endl;
    }
    out.close();
}

int main() {
	string line, info;
	ifstream infile;
	// opens file to be read
	infile.open("record.dat");
	if (infile.is_open()) {
        if (DEBUG == true) cout << "Open was a success" << endl;
		Book temp[LIB_SIZE];
        for (int i = 0; i < LIB_SIZE; i++) {
            temp[i].clear();
        }
		int count;
        int current = 0;
		count = 0;
		while (getline(infile, line)) {
            temp[current].storeToStruct(line, count);
			if (temp[current].isFull()) {
				//struct has been created
				count = 0;
				line.clear();
                current++;
				continue;
			}

			line.clear();
			count++;
		}
        writeStruct(temp);
	}

	infile.close();
}