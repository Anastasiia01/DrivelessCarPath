#include <cassert>
using namespace std;
#include "matrix.h"

matrix::matrix() {
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

void matrix::resetP() {
	//delete old p
	for (int i = 0; i < r_size; i++)
	{
		delete[] p[i];
	}
	delete[] p;
}

void matrix::initP() {
	//initialize new p
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

matrix::~matrix()
{
	for (int i = 0; i < r_size; i++)
	{
		delete[] p[i];
	}
	delete[] p;
}

//void matrix::printPath(tuple<int, int>& cur, tuple<int, int> end)
void matrix::printPath()
{
	int stepNum = 1;
	int xStep = get<0>(cur) - get<0>(end);
	int yStep = get<1>(cur) - get<1>(end);
	cout << "( " << xStep << ',' << yStep << " )";
	while (xStep!=0 or yStep!=0) {
		cout << "========== Step " << stepNum << " ==========" <<endl;
		(*this)(get<0>(cur), get<1>(cur)) = 'C';
		cout << (*this);
		(*this)(get<0>(cur), get<1>(cur)) = '=';
		stepNum++;
		if (xStep != 0) {
			int step = (xStep > 0) ? 1 : -1;
			if ((get<0>(cur) + step, get<1>(cur)) != 'O') {
				get<0>(cur) += step;
				xStep -= step;
				continue;
			}
		}
		else if(yStep != 0) {
			int step = (yStep > 0) ? 1 : -1;
			if ((get<0>(cur), get<1>(cur) + step) != 'O') {
				get<1>(cur) += step;
				yStep -= step;
			}
		}
	}
	


}


/*matrix matrix::operator=(const matrix& m)
{
	//check if 2d array has the same dim, else resize(destroy & create new) first, then apply '='
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
}*/

/*matrix matrix::operator+=(matrix& m)
{
	assert(m.c_size == c_size && m.r_size == r_size);
	int i, j;
	for (i = 0; i < r_size; i++)
		for (j = 0; j < c_size; j++)
			p[i][j] += m.p[i][j];
	return (*this);
}*/


ostream& operator<<(ostream& out, const matrix& m)
{
	for (int i = 0; i < m.r_size; i++)
	{
		for (int j = 0; j < m.c_size; j++)
			out << m.p[i][j] << "     ";
		out << endl;
	}
	return out;
}
