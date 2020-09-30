#ifndef MATRIX_H
#define MATRIX_H
#include<iostream>
#include<tuple>
using namespace std;

class matrix {
private:
	int c_size, r_size;
	tuple <int, int> cur;
	tuple <int, int> end;
	char** p;
public:
	matrix();
	matrix(int c, int r);
	matrix(const matrix&);
	~matrix();
	void resetP();
	void initP();
	void SetCsize(int c) { c_size = c; } // mutator
	void SetRsize(int r) { r_size = r; } // mutator
	void SetCur(int r, int c) { cur = make_tuple(r, c); } // mutator
	void SetEnd(int r, int c) { end = make_tuple(r, c); } // mutator
	//void printPath(tuple<int, int>& start, tuple<int, int> end);
	void printPath();
	char& operator()(int i, int j) { return p[i][j]; }
	//matrix operator=(const matrix& m);
	//friend istream& operator>>(istream& in, matrix& m);
	friend ostream& operator<<(ostream& out, const matrix& m);//output
	//matrix operator+=(matrix& m);
};

#endif // !MATRIX_H
