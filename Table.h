#pragma once
/*
	How it should work:

	auto t = Table([colCount]);
	t.addRow({cell1, cell2, ...});
	t.addRow({...});
	t.colSeparator = " ";
	t.prefixes = { "#", "X: ", "Y: ", "R: " };
	t.print();
*/
#include <vector>
#include <string>
#include <iostream>
#include "utils.h"
using namespace std;

class Table;

class Column {
private:
	int _maxWidth;
public:
	int _index_1;
	friend Table;
	vector<string> cells;
	Column() {
		this->cells = vector<string>();
		this->_maxWidth = 0;
		if (this->_index_1 != 0) this->_index_1 = 0;
	}

	int getMaxWidth() {
		return this->_maxWidth;
	}

	bool hasOnlyNumbers(int columnOrder = 1) {
		int _cellsSize = this->cells.size();
		for (int i = 0; i < this->cells.size(); i++) {
			if (!isNumber(this->cells[i])) return false;
		}
		return true;
	}

	bool hasNegative() {
		for (int i = 0; i < this->cells.size(); i++) {
			try {
				if (stod(this->cells[i]) < 0)
					return true;
			}
			catch (const std::exception&) {
				return false;
			}

		}
		return false;
	}
};

class Table {
private:
public:
	vector<Column> cols; // columns
	string colSeparator;
	vector<string> prefixes;

	Table(int inputHeight = 0) {
		this->cols = vector<Column>();
		this->colSeparator = " | ";
		this->prefixes = vector<string>();
	}

	// add row
	void addRow(vector<string> row) {
		for (int i = 0; i < row.size(); i++) {
			if (this->cols.size() < (UINT)i + 1) this->cols.push_back(Column());
			this->cols[i].cells.push_back(row[i]);
			if (row[i].length() > this->cols[i]._maxWidth)
				this->cols[i]._maxWidth = row[i].length();
		}
	}
	// print table
	void print() {
		string filler; // for padding
		string cell; // value of current cell
		int rowsCount = this->cols[0].cells.size();
		vector<bool> hasNegative;

		for (int i = 0; i < this->cols.size(); i++)
			hasNegative.push_back(this->cols[i].hasOnlyNumbers(i + 1) && this->cols[i].hasNegative());
		for (int r = 0; r < rowsCount; r++) { // enumeration of rows
			// print row
			cout << this->colSeparator;

			for (int c = 0; c < this->cols.size(); c++) { // enumeration of columns
				cout << this->prefixes[c];
				cell = this->cols[c].cells[r];
				// form filler...
				for (int flen = cell.size(); flen < this->cols[c]._maxWidth; flen++) {
					filler += " ";
				}

				if (cell.empty()) {
					cout << "*";
					filler.erase(filler.size() - 1, filler.size() - 1);
				}

				else if (isNumber(cell)) {
					if (hasNegative[c] && stod(cell) >= 0) {
						cout << " ";
						if (!filler.empty()) filler.erase(filler.size() - 1, 1);
					}
					if (floor(stod(cell)) != ceil(stod(cell)))
						printf("%.2f", stod(cell));
					else cout << cell;
				}
				else cout << cell;
				cout << filler << this->colSeparator;
				filler = "";
			}
			cout << endl;
		}
	}
};

