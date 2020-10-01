/*
* File: matrix.cpp
* Author : Anastasiia Babenko
* Date : 9/30/2020
* Compiler Used : Visual Studio 2019
*
* This is the client file where from the input file we read 
* matrix size, the car start and end positions. Then matrices are assigned and we get content
* of matrix during every step of path from start to end using matrix class methods. 
* The result outputs to console.
*/

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
	while (input.good()) {
		getline(input, line);
		int rows = stoi(string(1, line[1]));
		int cols = stoi(string(1, line[4]));
		m.resetP();
		m.SetCsize(cols);
		m.SetRsize(rows);
		m.initP();
		getline(input, line);
		start = make_tuple(stoi(string(1, line[1]))-1, stoi(string(1, line[4]))-1);
		getline(input, line);
		end = make_tuple(stoi(string(1, line[1]))-1, stoi(string(1, line[4]))-1);
		m(stoi(string(1, line[1]))-1, stoi(string(1, line[4]))-1) = 'E';
		while (input.good()) { // mark all obstacles for the current matrix
			getline(input, line);
			if (line == "-1") {
				break;
			}
			m(stoi(string(1, line[1]))-1, stoi(string(1, line[4]))-1) = 'O';
		}
		m.printPath(start, end);
	}
}