#pragma once
#include <string>
#include <iostream>
#include <Windows.h>

/* string convert int */
constexpr unsigned int sci(const char* s, int h = 0) {
	return !s[h] ? 5381 : (sci(s, h + 1) * 33) ^ s[h];
}

/* get word from cin */
std::string getWord() {
	std::string s;
	std::cin >> s;
	std::cin.ignore(INT_MAX, '\n');
	return s;
}

/* trim */
std::string trimRight(const std::string& str, const std::string delim = " ") {
	std::string s = str;
	std::string::size_type pos = s.find_last_not_of(delim);
	return s.erase(pos + 1);
}

std::string trimLeft(const std::string& str, const std::string delim = " ") {
	std::string s = str;
	std::string::size_type pos = s.find_first_not_of(delim);
	return s.erase(0, pos);
}

std::string trim(const std::string& str, const std::string delim = " ") {
	return trimRight(trimLeft(str, delim), delim);
}

/* isNumber */
bool isNumber(const std::string& str) {
	using namespace std;
	string s = trim(str);
	try {
		string stod_s = to_string(stod(s));
		stod_s = stod_s.substr(0, s.size());
		return stod_s == s;
	}
	catch (const exception&) {
		return false;
	}
}

/* counts words in string */
int countWords(const std::string& str, const std::string& delim = " ") {
	std::string s = str + delim;
	int i = 0;
	size_t pos = 0;
	std::string word;

	for (; (pos = s.find(delim)) != std::string::npos; i++) {
		word = s.substr(0, pos);
		if (word == "") i--;
		s.erase(0, pos + delim.length());
	}
	return i;
}

/* [double] random */
double random(double min, double max) {
	double f = (double)rand() / RAND_MAX;
	return min + f * (max - min);
}

/* round number to precision */
double round(const double num, size_t prc) {
	double dec = pow(10, prc);
	return (int)(num * dec + 0.5) / dec;
}

/* colorized output */
const int COLOR_STD = 7; // 7/15
const int COLOR_ERR = 12; // 4/12
const int COLOR_LOG = 11; // 11/30/31
const int COLOR_INPUT = 10; // 2/10
const int COLOR_YELLOW = 14;

// Set Text Color
void stc(const std::string& s) {
	auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int mode;
	switch (sci(s.c_str())) {
		case sci("std"): mode = COLOR_STD; break;
		case sci("err"): mode = COLOR_ERR; break;
		case sci("log"): mode = COLOR_LOG; break;
		case sci("input"): mode = COLOR_INPUT; break;
		/* colors */
		case sci("yellow"): mode = COLOR_YELLOW; break;
		default: mode = COLOR_STD;
	}
	SetConsoleTextAttribute(handle, mode);
}

void sayErr(const char* s) {
	stc("err");
	std::cout << "Error! " << s << std::endl;
	stc("std");
}

void sayLog(const char* s) {
	stc("log");
	std::cout << "[" << s << "]" << std::endl;
	stc("std");
}

void sayCaution(const char* s) {
	stc("yellow");
	std::cout << "Caution! " << s << std::endl;
	stc("std");
}

/* repeat char n counts */ // BAD
void logRepeat(const char ch, int n) {
	for (int i = 0; i < n; i++) std::cout << ch;
}
/* filling console line spaces */ // BAD
void clearLine(int n = 80) {
	logRepeat(' ', n);
	//std::cout << "\r";
}