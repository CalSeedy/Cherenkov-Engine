#pragma once
#include "ckpch.h"
#include "Core.h"
#include <type_traits>

namespace Cherenkov {
	namespace Maths {

#define ADD 0
#define SUBTRACT 1
#define MULTIPLY 2


		struct CK_API Vector {

			int Dim;

			std::vector<double> data;

			Vector(int dim);

			Vector(int dim, double *values);

			Vector(std::vector<double> values);

			~Vector();

			Vector& Add(double constant);
			Vector& Add(const Vector& vec);
			friend CK_API Vector operator+(Vector& left, const Vector& right);
			friend CK_API Vector operator+(Vector& vec, double constant);
			friend CK_API Vector operator+(double constant, Vector& vec);
			Vector& operator+=(const Vector& vec);
			Vector& operator+=(double constant);


			Vector& Sub(double constant);
			Vector& Sub(const Vector& vec);
			friend CK_API Vector operator-(Vector& left, const Vector& right);
			friend CK_API Vector operator-(Vector& vec, double constant);
			friend CK_API Vector operator-(double constant, Vector& vec);
			Vector& operator-=(const Vector& vec);
			Vector& operator-=(double constant);


			Vector& Multiply(double scalar);
			Vector& Multiply(const Vector& vec);
			friend CK_API Vector operator*(Vector& left, const Vector& right);
			friend CK_API Vector operator*(Vector& vec, double scalar);
			friend CK_API Vector operator*(double scalar, Vector& vec);
			Vector& operator*=(const Vector& vec);
			Vector& operator*=(double scalar);

			Vector& Divide(double scalar);
			friend CK_API Vector operator/(Vector& vec, double scalar);
			Vector& operator/=(double scalar);

			Vector& Cross(Vector& vec);
			bool Compatible(const Vector& vec, int operation);
			double Magnitude();
			double Dot(Vector& vec);
			friend CK_API std::ostream& operator<<(std::ostream& os, Vector& vec);

		};


		struct CK_API Matrix {

			int Rows, Cols;

			std::vector<std::vector<double>> data;


			//Data given in column major order
			Matrix(int rows, int cols);
			Matrix(int rows, int cols, double *values);
			Matrix(int rows, int cols, double diagonal);
			Matrix(std::vector<std::vector<double> >& values);

			~Matrix();

			Matrix& Add(double constant);
			Matrix& Add(const Matrix& mat);
			friend CK_API Matrix operator+(Matrix& left, const Matrix& right);
			friend CK_API Matrix operator+(Matrix& mat, double constant);
			friend CK_API Matrix operator+(double constant, Matrix& mat);
			Matrix& operator+=(const Matrix& mat);
			Matrix& operator+=(double constant);

			Matrix& Sub(double constant);
			Matrix& Sub(const Matrix& mat);
			friend CK_API Matrix operator-(Matrix& left, const Matrix& right);
			friend CK_API Matrix operator-(Matrix& mat, double constant);
			friend CK_API Matrix operator-(double constant, Matrix& mat);
			Matrix& operator-=(const Matrix& mat);
			Matrix& operator-=(double constant);

			Matrix& Multiply(double scalar);
			Matrix& Multiply(const Matrix& mat);
			friend CK_API Matrix operator*(Matrix& left, const Matrix& right);
			friend CK_API Matrix operator*(Matrix& mat, double scalar);
			friend CK_API Matrix operator*(double scalar, Matrix& mat);
			Matrix& operator*=(const Matrix& mat);
			Matrix& operator*=(double scalar);

			Matrix& Divide(double scalar);
			friend CK_API Matrix operator/(Matrix& mat, double scalar);
			Matrix& operator/=(double scalar);

			Matrix& Inverse();
			Matrix& Transpose();

			Vector getRow(int row);

			void setRow(int row, Vector rowVec);
			Vector getColumn(int column);
			void setColumn(int column, Vector columnVec);

			double Det();

#undef near
#undef far
			static Matrix Perspective(float fov, float aspectRatio, float near, float far);
			static Matrix Orthographic(float left, float right, float bottom, float top, float near, float far);
			static Matrix Identity(int rows, int cols);
			bool Compatible(const Matrix& mat, int operation);


			friend CK_API std::ostream& operator<<(std::ostream& os, Matrix& mat);

		};

	}
}