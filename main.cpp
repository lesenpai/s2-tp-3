/* 
	from 27.12.2019
	- sorting FIXED
*/

#include <iostream>
#include <string>
#include <memory>
#include <iomanip> 
#include "Circle.h"
#include "Array.h"
#include "utils.h"
#include "Table.h"
using namespace std;

#define DO_CLEAR_SCREEN system("cls")
#define DO_WAIT_BUTTON_DOWN system("pause>nul")

void mainMenu(const string& path="");
void arrayMenu(const string& _path="");
Array getArrayMenu(const string& path="");
Array selfInputArray(const string& path="");
Array autoArrayMenu(const string& path="");
Circle parseCircle(const string&);
void printArray(Array& arr);
void sortArrayMenu(Array& arr, const string& path = "");
void printArrayMenu(const Array& _arr, const string& _path = "");
void clearArrayMenu(Array& arr, const string& path = "");

const string ARROW_TEXT = " -> ";

int main() {
	mainMenu("");
	cout << endl;
	system("pause");
}

void mainMenu(const string& path) {
	string in;
	Array Array; // array of circles
	string MAIN_MENU_TEXT = "MAIN MENU";

	while (true) {
		cout << MAIN_MENU_TEXT << "\n\n";
		cout << "Go/Exit (g/e) ? ";
		in = getWord();
		switch (sci(in.c_str())) {
			case sci("g"):
				DO_CLEAR_SCREEN;
				arrayMenu(MAIN_MENU_TEXT);
				break;

			case sci("e"):
				DO_CLEAR_SCREEN;
				sayLog("Exit");
				return;

			default:
				sayErr("Wrong input");
				DO_WAIT_BUTTON_DOWN;
				DO_CLEAR_SCREEN;
				continue;
				break;
		}
	}
}

Array getArrayMenu(const string& path) {
	string in;
	Array arr = Array();
	string THIS_MENU_TEXT = "GET";

start:
	while (true) {
		cout << path << ARROW_TEXT << THIS_MENU_TEXT << "\n\n";
		cout << "Get array from: self/auto|back (s/a|b) ? ";
		in = getWord();
		switch (sci(in.c_str())) {
			case sci("s"): // self in;put
				DO_CLEAR_SCREEN;
				arr = selfInputArray(path + ARROW_TEXT + THIS_MENU_TEXT);
				cout << endl;
				printArray(arr);
				DO_WAIT_BUTTON_DOWN;
				DO_CLEAR_SCREEN;
				break;

			case sci("a"): // auto input
				try {
					DO_CLEAR_SCREEN;
					arr = autoArrayMenu(path + ARROW_TEXT + THIS_MENU_TEXT);
					DO_CLEAR_SCREEN;
				}
				catch (exception & ex) {
					sayLog(ex.what());
					goto start;
				}
				break;

			case sci("b"):
				sayLog("back");
				DO_CLEAR_SCREEN;
				return arr;

			default:
				sayErr("Wrong input");
				DO_WAIT_BUTTON_DOWN;
				DO_CLEAR_SCREEN;
				continue;
		}

		return arr;
	}
}

// menu for create and manipulate array
// print menu with available options
void arrayMenu(const string& _path) {
	string path = _path;
	Array arr = Array();
	string ARRAY_MENU_TEXT = "ARRAY MENU";

	while (true) {
		string in;
		cout << path << " -> " << ARRAY_MENU_TEXT << "\n\n";
		cout << "What to do?\n";
		cout << "Create array - cr\n"
			<< "Sort - srt\n"
			<< "Clear - cl\n"
			<< "Print - p\n"
			<< "Back - b\n";
		cout << endl;

		cout << ">> ";
		in = getWord();
		switch (sci(in.c_str())) {
			case sci("cr"):
				system("cls");
				arr = getArrayMenu(path + " -> " + ARRAY_MENU_TEXT);
				break;

			case sci("srt"):
				DO_CLEAR_SCREEN;
				sortArrayMenu(arr, path + " -> " + ARRAY_MENU_TEXT);
				DO_CLEAR_SCREEN;
				break;

			case sci("cl"):
				DO_CLEAR_SCREEN;
				clearArrayMenu(arr, path + " -> " + ARRAY_MENU_TEXT);
				DO_CLEAR_SCREEN;
				break;

			case sci("p"):
				DO_CLEAR_SCREEN;
				printArrayMenu(arr, path + "->" + ARRAY_MENU_TEXT);
				DO_CLEAR_SCREEN;
				break;

			case sci("b"):
				DO_CLEAR_SCREEN;
				return;

			default:
				sayErr("Wrong input");
				DO_WAIT_BUTTON_DOWN;
				DO_CLEAR_SCREEN;
				continue;
		}
	}
}

void printTableLinesArray(Array& Array) {
	Table t = Table();
	t.prefixes = { "#", "X: ", "Y: ", "R: " };
	for (int i = 0; i < Array.getLength(); i++) {
		t.addRow({ to_string(i + 1),
				 to_string(Array[i].x),
				 to_string(Array[i].y),
				 to_string(Array[i].getR()) }
		);
	}
	t.print();
}

void clearArrayMenu(Array& arr, const string& path) {
	string THIS_MENU_TEXT = "CLEAR";

	cout << path << ARROW_TEXT << THIS_MENU_TEXT << "\n\n";
	arr.clear();
	sayLog("Array cleared");
	DO_WAIT_BUTTON_DOWN;
}

Array selfInputArray(const string& path) {
	string in;
	Array arr;
	string THIS_MENU_TEXT = "SELF INPUT";
	cout << path << ARROW_TEXT << THIS_MENU_TEXT << "\n\n";
	cout << "Enter circles in format < X Y R> (stop word - 'stop')\n\n";
	for (int i = 1; true; i++) {
		cout << "#" << i << " >> ";
		getline(cin, in);
		if (in == "stop") {
			sayLog("stoped");
			break;
		}
		// get line <x y r>
		else {
			try {
				arr.push(parseCircle(in));
			}
			catch (exception & ex) {
				sayErr(ex.what());
				i--;
			}
		}
	}

	return arr;
}

void printArrayMenu(const Array& _arr, const string& _path) {
	Array arr = _arr;
	string path = _path;
	string THIS_MENU_TEXT = "PRINT";
	cout << path << ARROW_TEXT << THIS_MENU_TEXT << "\n\n";
	printArray(arr);
	DO_WAIT_BUTTON_DOWN;
}

// string -> Circle
Circle parseCircle(const string& str) {
	if (countWords(str) != 3) throw exception("not enough arguments");

	string delim = " ";
	string s = str + delim;
	size_t pos = 0;
	string word;
	double x=0, y=0, r=0;

	try {
		for (int i = 0; (pos = s.find(delim)) != std::string::npos; i++) {
			word = s.substr(0, pos);
			if (word == "") i--;
			else {
				switch (i) {
					case 0: x = stod(word);
						break;

					case 1: y = stod(word);
						break;

					case 2:
						r = stod(word);
						break;
				}
			}
			s.erase(0, pos + delim.length());
		}
	}
	catch(const exception&){
		throw exception("can't parse circle form that line");
	}
	return Circle(x, y, r);
}

Array autoArrayMenu(const string& path) {
	Array arr = Array();
	string in;
	string THIS_MENU_TEXT = "AUTO";

	while (true) {
		cout << path << ARROW_TEXT << THIS_MENU_TEXT << "\n\n";
		cout << "Length/back ([integer]/b) ? ";
		in = getWord();
		if (isNumber(in) && stoi(in) > 0) {
			int min = -9, max = 9;
			int len = stoi(in);
			for (int i = 0; i < len; i++) {
				arr.push(Circle(
					random(min, max),
					random(min, max),
					abs(random(min, max))
				));
			}
			break;
		}
		else if (in == "b") {
			throw exception("back");
		}
		else {
			sayErr("Wrong input");
			continue;
		}
	}

	cout << endl;
	printArray(arr);
	DO_WAIT_BUTTON_DOWN;
	return arr;
}

// print array
void printArray(Array& arr) {
	if (!arr.getLength()) {
		sayCaution("Array is empty");
		return;
	}
	printTableLinesArray(arr);
}

void sortArrayMenu(Array& arr, const string& path) {
	string THIS_MENU_TEXT = "SORT";
	cout << path << ARROW_TEXT << THIS_MENU_TEXT << "\n\n";
	if (!arr.getLength()) {
		sayCaution("Array is empty");
		DO_WAIT_BUTTON_DOWN;
		return;
	}

	string in, key;
	bool key_set = false, isAscending, isAscending_set = false;

	while (!key_set) {
		cout << "Property name|back ([string]|-b) ? ";
		in = getWord();
		if (arr[0].has(in)) { key = in; key_set = true; }
		else if (in == "-b") return;
		else { sayErr("No such property"); }
	}

	while (!isAscending_set) {
		cout << "isAscending|back (y/n|b) ? ";
		in = getWord();
		switch (sci(in.c_str())) {
			case sci("y"): isAscending = true; isAscending_set = true;
				break;
			case sci("n"): isAscending = false; isAscending_set = true;
				break;
			case sci("b"): return;
			default: sayErr("Wrong input");
				break;
		}
	}

	for (int i = 1; i < arr.getLength(); i++) {
		for (int j = i;
			 j > 0 && (isAscending ? (arr[j - 1][key] > arr[j][key]) : (arr[j - 1][key] < arr[j][key]));
			 j--)
		{
			arr.swapCircles(arr[j - 1], arr[j]);
		}
	}

	cout << endl;
	printTableLinesArray(arr);
	DO_WAIT_BUTTON_DOWN;
}
