#pragma once
#include "ckpch.h"
#include "Core.h"
#include <type_traits>


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

			Matrix(std::vector<std::vector<float> >& values);


			~Matrix();

			Matrix& Add(float constant);
			Matrix& Add(const Matrix& mat);
			friend CK_API Matrix operator+(Matrix& left, const Matrix& right);
			friend CK_API Matrix operator+(Matrix& mat, float constant);
			friend CK_API Matrix operator+(float constant, Matrix& mat);
			Matrix& operator+=(const Matrix& mat);
			Matrix& operator+=(float constant);


			Matrix& Sub(float constant);
			Matrix& Sub(const Matrix& mat);
			friend CK_API Matrix operator-(Matrix& left, const Matrix& right);
			friend CK_API Matrix operator-(Matrix& mat, float constant);
			friend CK_API Matrix operator-(float constant, Matrix& mat);
			Matrix& operator-=(const Matrix& mat);
			Matrix& operator-=(float constant);


			Matrix& Multiply(float scalar);
			Matrix& Multiply(const Matrix& mat);
			friend CK_API Matrix operator*(Matrix& left, const Matrix& right);
			friend CK_API Matrix operator*(Matrix& mat, float scalar);
			friend CK_API Matrix operator*(float scalar, Matrix& mat);
			Matrix& operator*=(const Matrix& mat);
			Matrix& operator*=(float scalar);

			Matrix& Divide(float scalar);
			friend CK_API Matrix operator/(Matrix& mat, float scalar);
			Matrix& operator/=(float scalar);

			Matrix& Transpose();
			float Det();
			static Matrix Identity(int rows, int cols);
			bool Compatible(const Matrix& mat, int operation);


			friend CK_API std::ostream& operator<<(std::ostream& os, Matrix& mat);

		};

		struct CK_API Vector {

			int Dim;

			std::vector<float> data;

			Vector(int dim);

			Vector(int dim, float *values);
			
			Vector(std::vector<float> values);

			~Vector();

			Vector& Add(float constant);
			Vector& Add(const Vector& vec);
			friend CK_API Vector operator+(Vector& left, const Vector& right);
			friend CK_API Vector operator+(Vector& vec, float constant);
			friend CK_API Vector operator+(float constant, Vector& vec);
			Vector& operator+=(const Vector& vec);
			Vector& operator+=(float constant);


			Vector& Sub(float constant);
			Vector& Sub(const Vector& vec);
			friend CK_API Vector operator-(Vector& left, const Vector& right);
			friend CK_API Vector operator-(Vector& vec, float constant);
			friend CK_API Vector operator-(float constant, Vector& vec);
			Vector& operator-=(const Vector& vec);
			Vector& operator-=(float constant);


			Vector& Multiply(float scalar);
			Vector& Multiply(const Vector& vec);
			friend CK_API Vector operator*(Vector& left, const Vector& right);
			friend CK_API Vector operator*(Vector& vec, float scalar);
			friend CK_API Vector operator*(float scalar, Vector& vec);
			Vector& operator*=(const Vector& vec);
			Vector& operator*=(float scalar);

			Vector& Divide(float scalar);
			friend CK_API Vector operator/(Vector& vec, float scalar);
			Vector& operator/=(float scalar);

			bool Compatible(const Vector& vec, int operation);
			float Magnitude();
			float Dot(Vector& vec);
			friend CK_API std::ostream& operator<<(std::ostream& os, Vector& vec);

		};

	}
}