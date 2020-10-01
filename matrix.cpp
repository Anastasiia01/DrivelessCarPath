/*
* File: matrix.cpp
* Author : Anastasiia Babenko
* Date : 9/30/2020
* Compiler Used : Visual Studio 2019
*
* This is the source file with implementation of matrix methods
* as well as top level overloading of << operators
*/

#include <cassert>
#include <iostream>
using namespace std;
#include "matrix.h"

matrix::matrix() { //default constructor
	r_size = c_size = 1;
	p = new char* [r_size];
	p[0] = new char[c_size];
}
matrix::matrix(int r, int c) :r_size(r), c_size(c)
{
	p = new char* [r_size];
	for (int i = 0; i < r_size; i++)
	{
		p[i] = new char[c_size];
		//initialize all entries of matrix to be '='
		for (int j = 0; j < c_size; j++)
			p[i][j] = '=';
	}
}

matrix::matrix(const matrix& m) :r_size(m.r_size), c_size(m.c_size)
{
	p = new char* [r_size];
	for (int i = 0; i < r_size; i++)
		p[i] = new char[c_size];

	for (int i = 0; i < r_size; i++)
		for (int j = 0; j < c_size; j++)
		{
			p[i][j] = m.p[i][j];
		}
}

void matrix::resetP() {
	//deallocates memory of the previous p
	for (int i = 0; i < r_size; i++)
	{
		delete[] p[i];
	}
	delete[] p;
}

void matrix::initP() {
	//initialize new p with current host's r_size and c_size 
	p = new char* [r_size];
	for (int i = 0; i < r_size; i++)
	{
		p[i] = new char[c_size];
		//initialize all entries of matrix to be '='
		for (int j = 0; j < c_size; j++)
			p[i][j] = '=';
	}
}

matrix::~matrix() //destructor
{
	for (int i = 0; i < r_size; i++)
	{
		delete[] p[i];
	}
	delete[] p;
}

void matrix::printPath(tuple<int, int>& cur, tuple<int, int> end)
{
	/* prints matrix content during every step of the path 
	   from given 'cur' to 'end' coordinates. Allows to go around multiple obstacles in row
	   as long as there is no dead end (this method doesn't do backtracking).
	*/
	int stepNum = 1;
	int yStep = get<0>(end) - get<0>(cur); //row diff - num of steps needed to get to the 'end' vertically
	int xStep = get<1>(end) - get<1>(cur); //col diff - num of steps needed to get to the 'end' horizontally
	//booleans prevent from coming back and forth if many obstacles are in row - makes go the same way
	bool skipY = false, skipX = false; 
	int x, y ;
	while (true) {
		cout << "   ========== Step " << stepNum << " ==========" << endl;
		(*this)(get<0>(cur), get<1>(cur)) = 'C'; //updates 'C'
		cout << (*this);// prints with content with new position of 'C'
		(*this)(get<0>(cur), get<1>(cur)) = '='; //zeros out old 'C', then will calculate new below.
		if (yStep == 0 && xStep == 0) { //no more steps needed
			break;
		}
		stepNum++;
		if (!skipY && yStep != 0) {// steps needed vertically
			y = (yStep > 0) ? 1 : -1; //check whether step needed up or down
			if ((*this)(get<0>(cur) + y, get<1>(cur)) != 'O') { //if potential step is not obstacle
				get<0>(cur) += y;//update cur
				yStep -= y;
				skipX = false;
				continue;
			}
			//if obstacle, then go around it even if steps are NOT needed horizontally
			if (xStep != 0 && !skipX){
				x = (xStep > 0) ? 1 : -1;
			}
			if ((*this)(get<0>(cur), get<1>(cur) + x) != 'O') {
				get<1>(cur) += x;
				skipX = true;
				xStep -= x;
				continue;
			}
		}
		else{ //if (!skipX && xStep != 0) - steps needed horizontally
			x = (xStep > 0) ? 1 : -1; //check whether step needed right or left
			if ((*this)(get<0>(cur), get<1>(cur) + x) != 'O'){//if potential step is not obstacle
				skipY = false;
				get<1>(cur) += x;
				xStep -= x;
				continue;
			}
			//if obstacle, then go around it even if steps are NOT needed vertically
			if (yStep != 0 && !skipY) { 
				y = (yStep > 0) ? 1 : -1; //update step
			}
			if ((*this)(get<0>(cur) + y, get<1>(cur)) != 'O') { 
				get<0>(cur) += y;
				yStep -= y;
				skipY = true;
			}			
		}
	}
	cout << endl << "Total Steps to goal: "<< stepNum << endl;
	cout << endl << "************************************************" << "\n\n";
}


matrix matrix::operator=(const matrix& m)
{
	//check if 2d arrayStep has the same dim, else resize(destroyStep & create new) first, then applyStep '='
	if (!(m.c_size == c_size && m.r_size == r_size)){
		for (int i = 0; i < r_size; i++)
		{
			delete[] p[i];
		}
		delete[] p;
		c_size = m.c_size;
		r_size = m.r_size;

	}
	
	int i, j;
	for (i = 0; i < r_size; i++)
		for (j = 0; j < c_size; j++)
			p[i][j] = m.p[i][j];
	return (*this);
}

matrix matrix::operator+=(matrix& m)
{
	assert(m.c_size == c_size && m.r_size == r_size);
	int i, j;
	for (i = 0; i < r_size; i++)
		for (j = 0; j < c_size; j++)
			p[i][j] += m.p[i][j];
	return (*this);
}


ostream& operator<<(ostream& out, const matrix& m)
{
	//prints content of m.p - 2d array
	for (int i = 0; i < m.r_size; i++)
	{
		out << "    ";
		for (int j = 0; j < m.c_size; j++)
			out << m.p[i][j] << "     ";
		out << endl;
	}
	return out;
}
