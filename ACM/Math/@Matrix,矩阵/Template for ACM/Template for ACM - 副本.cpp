//Template for ACM

#define LL long long
#define INF 0x7FFFFFFF
#define LINF 0x7FFFFFFF7FFFFFFF

#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cmath>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define DEBUG 0x0
#define DEBUG_THROW_MISMATHING 0x1

#define MAXN ()

template<typename DataType>class Matrix {
public:
	Matrix(int n, int m) :n(n), m(m) {
		data = new vector<DataType>[n];
		for (int i = 0; i < n; ++i)data[i].resize(m);
	}
	Matrix(const Matrix &matrix) {
		data = new vector<DataType>[matrix.n];
		*this = matrix;
	}
	Matrix(Matrix &&matrix) {
		data = new vector<DataType>[matrix.n];
		*this = ::move(matrix);
	}

	Matrix &operator=(const Matrix &matrix) {
		n = matrix.n; m = matrix.m;
		for (int i = 0; i < n; ++i) {
			if (data[i].capacity() < m)data[i].resize(m);
			for (int j = 0; j < m; ++j)
				data[i][j] = matrix.data[i][j];
		}
		return *this;
	}
	Matrix &operator=(Matrix &&matrix) {
		n = matrix.n; m = matrix.m; swap(data, matrix.data);

		return *this;
	}

	Matrix &operator+=(const Matrix &matrix) {
#if(DEBUG&DEBUG_THROW_MISMATHING)
		if (m != matrix.m || n != matrix.n)	throw exception("Error:Matrix size mismatching!");
#endif;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j)
				data[i][j] += matrix.data[i][j];
		}
		return *this;
	}
	Matrix &operator*=(const Matrix &matrix) {
#if(DEBUG&DEBUG_THROW_MISMATHING)
		if (n != matrix.m || m != matrix.n)	throw exception("Error:Matrix size mismatching!");
#endif;
		Matrix tmp(n, matrix.m); DataType each;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < matrix.m; ++j) {
				each = 0;
				for (int k = 0; k < n; ++k)
					each += data[i][k] * matrix.data[k][j];
				tmp.data[i][j] = each;
			}
		}
		return *this = ::move(tmp);
	}
	Matrix &operator^=(LL val) {
#if(DEBUG&DEBUG_THROW_MISMATHING)
		if (n != m)throw exception("Error:Matrix size mismatching!");
#endif;
		Matrix tmp = *this;

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j)
				data[i][j] = 0;
			data[i][i] = 1;
		}

		while (val > 0) {
			if (val & 1)*this *= tmp;
			tmp *= tmp; val >>= 1;
		}
		return *this;
	}

	Matrix &Mul(const Matrix &matrix, LL mod) {
#if(DEBUG&DEBUG_THROW_MISMATHING)
		if (n != matrix.m || m != matrix.n)	throw exception("Error:Matrix size mismatching!");
#endif;
		Matrix tmp(n, matrix.m); DataType each;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < matrix.m; ++j) {
				each = 0;
				for (int k = 0; k < n; ++k) {
					each += data[i][k] * matrix.data[k][j];
					each %= mod;
				}
				tmp.data[i][j] = each;
			}
		}
		return *this = ::move(tmp);
	}
	Matrix &Pow(LL val, LL mod) {
#if(DEBUG&DEBUG_THROW_MISMATHING)
		if (n != m)throw exception("Error:Matrix size mismatching!");
#endif;
		Matrix tmp = *this;

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j)
				data[i][j] = 0;
			data[i][i] = 1;
		}

		while (val > 0) {
			if (val & 1)this->Mul(tmp, mod);
			tmp.Mul(tmp, mod); val >>= 1;
		}
		return *this;
	}

	vector<DataType> &operator[](unsigned int index) {
		return data[index];
	}

	~Matrix() {
		if (data)delete[]data;
	}

	//debug
	void Print() {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j)
				printf("%d ", data[i][j]);
			printf("\n");
		}
	}

private:
	int n, m; vector<DataType>*data;
};

void test1() {
	int n; cin >> n;
	Matrix<LL>A(n, n), B(n, n);

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			scanf("%I64d", &A[i][j]);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			scanf("%I64d", &B[i][j]);

	A *= B;
	A.Print();
}

void test2() {
	int n, m; cin >> n >> m;
	Matrix<LL>A(n, n);

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			scanf("%I64d", &A[i][j]);

	A.Pow(m, 1000000000 + 7);
	A.Print();
}

int main() {
	test2();

	return 0;
}