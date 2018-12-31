#pragma once
#include "ckpch.h"
#include "Core.h"

namespace Cherenkov {

	namespace Maths {
	
		#define ADD 0
		#define SUBTRACT 1
		#define MULTIPLY 2

		struct CK_API Matrix {

			int Rows, Cols;

			std::vector<std::vector<float>> data;

			Matrix(int rows, int cols);

			Matrix(int rows, int cols, float *values);

			Matrix(int rows, int cols, float diagonal);

			~Matrix();


			bool Compatible(const Matrix &mat, int operation);
			static Matrix Identity(int rows, int cols);

			Matrix Add(float constant);
			Matrix Add(const Matrix& mat);
			friend CK_API Matrix operator+(Matrix& left, const Matrix& right);
			friend CK_API Matrix operator+(Matrix& mat, float constant);
			friend CK_API Matrix operator+(float constant, Matrix& mat);
			Matrix& operator+=(const Matrix& mat);
			Matrix& operator+=(float constant);


			Matrix Sub(float constant);
			Matrix Sub(const Matrix& mat);
			friend CK_API Matrix operator-(Matrix& left, const Matrix& right);
			friend CK_API Matrix operator-(Matrix& mat, float constant);
			friend CK_API Matrix operator-(float constant, Matrix& mat);
			Matrix& operator-=(const Matrix& mat);
			Matrix& operator-=(float constant);


			Matrix Multiply(float scalar);
			Matrix Multiply(const Matrix& mat);
			friend CK_API Matrix operator*(Matrix& left, const Matrix& right);
			friend CK_API Matrix operator*(Matrix& mat, float scalar);
			friend CK_API Matrix operator*(float scalar, Matrix& mat);
			Matrix& operator*=(const Matrix& mat);
			Matrix& operator*=(float scalar);

			Matrix Divide(float scalar);
			friend CK_API Matrix operator/(Matrix& mat, float scalar);
			friend CK_API Matrix operator/(float scalar, Matrix& mat);
			Matrix& operator/=(float scalar);

			friend CK_API std::ostream& operator<<(std::ostream& os, const Matrix& mat);
		};

	}
}