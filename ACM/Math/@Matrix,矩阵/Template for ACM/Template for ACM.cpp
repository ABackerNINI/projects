#pragma once

#ifndef _MATRIX_MUL_MATRIX_ABACKER_
#define _MATRIX_MUL_MATRIX_ABACKER_

#include <iostream>

using namespace std;

#define DEBUG 0x1
#define DEBUG_THROW_MISMATHING 0x1 //抛出大小不匹配异常

template<typename DataType>class Matrix {
private:
	struct Row {
		DataType *data;
		void Init(int m) {
			data = new DataType[m];
		}
		DataType &operator[](int index) {
			return data[index];
		}
		~Row() {
			if (data)delete[]data;
		}
	};
public:
	int n, m; //char name;

	Matrix() :data(NULL) {}
	Matrix(int n, int m) :n(n), m(m) {
		data = new Row[n];
		for (int i = 0; i < n; ++i)data[i].Init(m);
	}
	Matrix(DataType *arr, int n, int m) :n(n), m(m) {
		data = new Row[n];
		for (int i = 0; i < n; ++i) {
			data[i].Init(m);
			for (int j = 0; j < m; ++j)data[i][j] = *arr++;
		}
	}
	Matrix(const Matrix &matrix):data(NULL){
		assign(matrix);
	}
	Matrix(Matrix &&matrix):data(NULL) {
		assign(std::move(matrix));
	}

	Matrix &operator=(const Matrix &matrix) {//O(n^2)
		assign(matrix);
		return *this;
	}
	Matrix &operator=(Matrix &&matrix) {//O(1)
		assign(std::move(matrix));
		return *this;
	}

	void assign(const Matrix &matrix) {
		if (data)delete[]data;
		n = matrix.n; m = matrix.m;
		data = new Row[n];
		for (int i = 0; i < n; ++i) {
			data[i].Init(m); 
			for (int j = 0; j < m; ++j)
				data[i][j] = matrix.data[i][j];
		}
	}
	void assign(Matrix &&matrix) {
		n = matrix.n; m = matrix.m; swap(data, matrix.data);
	}

	void resize(int n, int m) {
		this->n = n; this->m = m;
		if (data)delete[]data;
		data = new Row[n];
		for (int i = 0; i < n; ++i)data[i].Init(m);
	}

	Matrix &operator+=(const Matrix &matrix) {//O(n^2)
#if(DEBUG&DEBUG_THROW_MISMATHING)
		if (m != matrix.m || n != matrix.n)	throw exception("Error:Matrix size mismatching!");
#endif;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j)
				data[i][j] += matrix.data[i][j];
		}
		return *this;
	}
	Matrix &operator-=(const Matrix &matrix) {//O(n^2)
#if(DEBUG&DEBUG_THROW_MISMATHING)
		if (m != matrix.m || n != matrix.n)	throw exception("Error:Matrix size mismatching!");
#endif;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j)
				data[i][j] -= matrix.data[i][j];
		}
		return *this;
	}
	Matrix &operator*=(const Matrix &matrix) {//O(n^3)
#if(DEBUG&DEBUG_THROW_MISMATHING)
		if (m != matrix.n)	throw exception("Error:Matrix size mismatching!");
#endif;
		Matrix tmp(n, matrix.m); DataType each;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < matrix.m; ++j) {
				each = 0;
				for (int k = 0; k < m; ++k)
					each += data[i][k] * matrix.data[k][j];
				tmp.data[i][j] = each;
			}
		}
		return *this = ::move(tmp);
	}
	Matrix &operator^=(long long val) {//O(n^2+n^3*log(val))
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

	Matrix operator+(const Matrix &matrix) {
		Matrix tmp = *this;
		tmp += matrix;

		return tmp;
	}
	Matrix operator-(const Matrix &matrix) {
		Matrix tmp = *this;
		tmp -= matrix;

		return tmp;
	}
	Matrix operator*(const Matrix &matrix) {
		Matrix tmp = *this;
		tmp *= matrix;

		return tmp;
	}

	template<typename DT>friend Matrix<DT>& operator*=(Matrix<DT>&matrix, long long num);

	//矩阵带模乘法
	Matrix &Mul_Mod(const Matrix &matrix, long long mod) {//O(n^3)
#if(DEBUG&DEBUG_THROW_MISMATHING)
		if (n != matrix.m || m != matrix.n)	throw exception("Error:Matrix size mismatching!");
#endif;
		Matrix tmp(n, matrix.m); LL each;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < matrix.m; ++j) {
				each = 0;
				for (int k = 0; k < m; ++k) {
					each += data[i][k] * matrix.data[k][j];
					if (each >= mod)each %= mod;
				}
				tmp.data[i][j] = each;
			}
		}
		return *this = ::move(tmp);
	}
	//矩阵带模乘方
	Matrix &Pow_Mod(long long val, long long mod) {//O(n^2+n^3*log(val))
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
			if (val & 1)this->Mul_Mod(tmp, mod);
			tmp.Mul_Mod(tmp, mod); val >>= 1;
		}
		return *this;
	}

	Row &operator[](unsigned int index) {
		return data[index];
	}

	~Matrix() {
		if (data)delete[]data;
	}

	//debug 输出矩阵各项值
	void print(bool isNewLine = false) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				data[i][j].print();
				printf(" ");
			}
			printf("\n");
		}
		if (isNewLine)printf("\n");
	}

private:
	Row *data;
};

template<typename DataType>Matrix<DataType>& operator*=(Matrix<DataType>&matrix, long long num) {
	for (int i = 0; i < matrix.n; ++i) {
		for (int j = 0; j < matrix.m; ++j) {
			matrix.data[i][j] *= num;
		}
	}
	return matrix;
}

#endif;

/*
//矩阵乘法
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

//矩阵快速幂
void test2() {
	int n, m; cin >> n >> m;
	Matrix<LL>A(n, n);

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			scanf("%I64d", &A[i][j]);

	A.Pow_Mod(m, 1000000000 + 7);
	A.Print();
}

//斐波拉契数列第n项
void test3() {
	LL n; cin >> n;
	Matrix<LL>m(2, 2);
	m[0][0] = 1; m[0][1] = 1;
	m[1][0] = 1; m[1][1] = 0;

	m.Pow_Mod(n - 1, 1000000000 + 9);

	printf("%I64d\n", m[0][0]);
}

void test4() {
	int arr[] = { 1,2,3,4,5,6 };
	Matrix<int>m(arr, 3, 2);
	m.Print();
}

int main() {
	test4();

	return 0;
}*/