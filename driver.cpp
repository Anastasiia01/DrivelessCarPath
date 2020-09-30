#include <iostream>
#include <fstream>
#include "matrix.h"
#include <string>
#include <tuple>

using namespace std;

void main(int argc, char** argv) 
{
	ifstream input("instructions.txt");
	string line;
	matrix m;
	tuple<int, int> start;
	tuple<int, int> end;
	//string line;
	while (input.good()) {
		getline(input, line);
		cout << line << endl;
		int rows = stoi(string(1, line[1]));
		int cols = stoi(string(1, line[4]));
		cout << rows << " " << cols << endl;
		m.resetP();
		m.SetCsize(cols);
		m.SetRsize(rows);
		m.initP();
		getline(input, line);
		cout << line << endl;
		start = make_tuple(stoi(string(1, line[1]))-1, stoi(string(1, line[4]))-1);
		m.SetCur(stoi(string(1, line[1])) - 1, stoi(string(1, line[4])) - 1);
		//cout << get<0>(start)<< get<1>(start) <<endl;
		//m(stoi(string(1, line[1]))-1, stoi(string(1, line[4]))-1) = 'C';
		getline(input, line);
		cout << line << endl;
		end = make_tuple(stoi(string(1, line[1]))-1, stoi(string(1, line[4]))-1);
		m.SetEnd(stoi(string(1, line[1])) - 1, stoi(string(1, line[4])) - 1);
		//cout << "end "<<get<0>(end) << get<1>(end) << endl;
		m(stoi(string(1, line[1]))-1, stoi(string(1, line[4]))-1) = 'E';
		while (input.good()) {
			getline(input, line);
			cout << line << endl;
			if (line == "-1") {
				break;
			}
			m(stoi(string(1, line[1]))-1, stoi(string(1, line[4]))-1) = 'O';
		}
		m.printPath();
		//cout << m;
	}
}