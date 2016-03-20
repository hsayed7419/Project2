#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

using namespace std;

int stringToInt(string data) {
	size_t *size = 0;
	return stoi(data, size, 10);
}

float stringToFloat(string data) {
	size_t *size = 0;
	return stof(data, size);
}

struct Author {
	string First_name;
	string Middle_name;
	string Last_name;
	bool isFull() {
		if ((First_name.length() > 0) && (Middle_name.length() > 0)
			&& (Last_name.length() > 0))
			return true;
		else
			return false;
	}
	//reset the struct values
	void clear() {
		First_name.clear();
		Middle_name.clear();
		Last_name.clear();
	}
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
				case 2:
					Last_name = temp;
					break;
				default:
					cout << "Error in Author name format" << endl;
				}
				if (count == 3) break;
				count++;
			}
			else {
				temp += c;
			}
		}
	}
};

struct Publication_date {
	int month;
	int day;
	int year;
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

struct Book {
	Publication_date pub;
	Author auth;
	string Title;
	float cost;
	int Type;
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

void printStruct(Book book) {
	cout << "Title: " << book.Title << endl;
}

int main() {
	bool DEBUG = true;
	string line, info;
	ifstream infile;
	// opens file to be read
	infile.open("record.dat");
	if (infile.is_open() && DEBUG == true) {
		cout << "Open was a success" << endl;
		Book temp;
		temp.clear();
		int count;
		count = 0;
		while (getline(infile, line)) {
			cout << line << endl;
			if (temp.isFull()) {
				//struct has been created
				printStruct(temp);
				count = 0;
				line.clear();
				temp.clear();
				continue;
			}

			temp.storeToStruct(line, count);
			line.clear();
			count++;
		}
	}

	infile.close();
}