#pragma once
#include "ckpch.h"
#include "Cherenkov.h"
#include "Cherenkov/Core.h"

namespace Cherenkov {

	namespace Maths {
	
		constexpr int ADD = 0;
		constexpr int SUBTRACT = 1;
		constexpr int MULTIPLY = 2;

		struct CK_API Matrix {

			int Rows, Cols;

			float** data;

			Matrix(int rows, int cols);

			Matrix(int rows, int cols, float *values);

			Matrix(int rows, int cols, float diagonal);

			~Matrix();


			bool Compatible(const Matrix &mat, int operation);
			Matrix Identity(int rows, int cols);

			Matrix& Add(float constant);
			Matrix& Add(const Matrix& mat);
			friend CK_API Matrix operator+(Matrix& left, const Matrix& right);
			friend CK_API Matrix operator+(Matrix mat, float constant);
			friend CK_API Matrix operator+(float constant, Matrix mat);
			Matrix& operator+=(const Matrix& mat);
			Matrix& operator+=(float constant);


			Matrix& Sub(float constant);
			Matrix& Sub(const Matrix& mat);
			friend CK_API Matrix operator-(Matrix& left, const Matrix& right);
			friend CK_API Matrix operator-(Matrix mat, float constant);
			friend CK_API Matrix operator-(float constant, Matrix mat);
			Matrix& operator-=(const Matrix& mat);
			Matrix& operator-=(float constant);


			Matrix& Multiply(float scalar);
			Matrix& Multiply(const Matrix& mat);
			friend CK_API Matrix operator*(Matrix& left, const Matrix& right);
			friend CK_API Matrix operator*(Matrix mat, float scalar);
			friend CK_API Matrix operator*(float scalar, Matrix mat);
			Matrix& operator*=(const Matrix& mat);
			Matrix& operator*=(float scalar);


			Matrix& Divide(float scalar);
			friend CK_API Matrix operator/(Matrix mat, float scalar);
			friend CK_API Matrix operator/(float scalar, Matrix mat);
			Matrix& operator/=(float scalar);

		};

	}
}