/*
* File: matrix.h
* Author : Anastasiia Babenko
* Date : 9/30/2020
* Compiler Used : Visual Studio 2019
*
* This is the header file with definition of matrix class that
* allows to store and reuse multiple times 2d array(matrix) of characters.
* It also let you print steps of the car moving from the given start to the given end.
*/

#ifndef MATRIX_H
#define MATRIX_H
#include<iostream>
#include<tuple>
using namespace std;

class matrix {
private:
	int c_size, r_size;
	char** p;
public:
	matrix();
	matrix(int c, int r);
	matrix(const matrix&);
	~matrix();
	void resetP(); //deallocates memory of the previous p
	void initP(); //initializes empty p
	void SetCsize(int c) { c_size = c; } // mutator 
	void SetRsize(int r) { r_size = r; } // mutator
	// prints steps of the car moving from start to end
	void printPath(tuple<int, int>& start, tuple<int, int> end);
	char& operator()(int i, int j) { return p[i][j]; }
	matrix operator=(const matrix& m);
	matrix operator+=(matrix& m);
	friend ostream& operator<<(ostream& out, const matrix& m);//output
};

#endif // !MATRIX_H
