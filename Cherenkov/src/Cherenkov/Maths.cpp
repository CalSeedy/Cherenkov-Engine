
#include "ckpch.h"
#include "Maths.h"
#include "Log.h"

namespace Cherenkov {
	namespace Maths {

#define ADD 0
#define SUBTRACT 1
#define MULTIPLY 2

		Matrix::Matrix(int rows, int cols) {
			Rows = rows;
			Cols = cols;
			
			this->data = std::vector<std::vector<float> > (rows, std::vector<float>(cols));

			for (int i = 0; i < this->data.size(); ++i)
			{
				for (int j = 0; j < this->data[i].size(); ++j)
				{
					data[i][j] = 0.0f;
				}
			}
		}

		Matrix::Matrix(int rows, int cols, float* values) {
			Rows = rows;
			Cols = cols;
			this->data = std::vector<std::vector<float> >(rows, std::vector<float>(cols));

			for (int i = 0; i < this->data.size(); ++i)
			{
				for (int j = 0; j < this->data[i].size(); ++j)
				{
					data[i][j] = values[j + i*cols];
				}
			}

		}

		Matrix::Matrix(int rows, int cols, float diagonal) {
			Rows = rows;
			Cols = cols;
			
			this->data = std::vector<std::vector<float> >(rows, std::vector<float>(cols));

			for (int i = 0; i < this->data.size(); ++i)
			{
				for (int j = 0; j < this->data[i].size(); ++j)
				{
					if (i == j)
						data[i][j] = diagonal;
					else
						data[i][j] = 0.0f;
				}
			}
		}

		Matrix::Matrix(std::vector<std::vector<float> >& values) {
			Rows = values.size();
			Cols = values[0].size();

			this->data = values;
		}

		Matrix::~Matrix() {
			for (auto row : this->data) {
				row.clear();
			}
			data.clear();
		}


		Matrix& Matrix::Add(const Matrix& mat) {
		
			if (this->Compatible(mat, ADD)) {
				Matrix* out = new Matrix(Rows,Cols);

				for (int i = 0; i < this->data.size(); ++i) {
					for (int j = 0; j < this->data[i].size(); ++j) {
						out->data[i][j] = this->data[i][j] + mat.data[i][j];
					}
				}
				return *out;
			} else {
				CK_WARN("Matrix dimensions aren't equal for both matricies! ({0}x{1} =/= {2}x{3})\nReturned left matrix...", Rows, Cols, mat.Rows, mat.Cols);
				return *this;
			}
		}

		Matrix& Matrix::Add(float constant) {
			Matrix* out = new Matrix(Rows, Cols);

			for (int i = 0; i < this->data.size(); ++i) {
				for (int j = 0; j < this->data[i].size(); ++j) {
					out->data[i][j] = this->data[i][j] + constant;
				}
			}
			return *out;
		}

		Matrix& Matrix::Sub(const Matrix& mat) {
			if (this->Compatible(mat, SUBTRACT)) {
				Matrix* out = new Matrix(Rows, Cols);

				for (int i = 0; i < this->data.size(); ++i) {
					for (int j = 0; j < this->data[i].size(); ++j) {
						out->data[i][j] = this->data[i][j] - mat.data[i][j];
					}
				}
				return *out;
			}
			else {
				CK_WARN("Matrix dimensions aren't equal for both matricies! ({0}x{1} =/= {2}x{3})\nReturned left matrix...", Rows, Cols, mat.Rows, mat.Cols);
				return *this;
			}
		}
		
		Matrix& Matrix::Sub(float constant) {
			Matrix* out = new Matrix(Rows, Cols);
			for (int i = 0; i < this->data.size(); ++i) {
				for (int j = 0; j < this->data[i].size(); ++j) {
					out->data[i][j] = this->data[i][j] - constant;
				}
			}
			return *out;
		}

		Matrix& Matrix::Divide(float scalar) {
			Matrix* out = new Matrix(Rows, Cols);
			for (int i = 0; i < this->data.size(); ++i) {
				for (int j = 0; j < this->data[i].size(); ++j) {
					out->data[i][j] = this->data[i][j] / scalar;
				}
			}
			return *out;
		}

		Matrix& Matrix::Multiply(float scalar) {
			Matrix* out = new Matrix(Rows, Cols);
			for (int i = 0; i < this->data.size(); ++i) {
				for (int j = 0; j < this->data[i].size(); ++j) {
					out->data[i][j] = this->data[i][j] * scalar;
				}
			}
			return *out;
		}

		Matrix& Matrix::Multiply(const Matrix& mat) {

			if (this->Compatible(mat, MULTIPLY)) {
				Matrix* out = new Matrix(Rows, mat.Cols);
				for (int i = 0; i < this->data.size(); ++i) {
					for (int j = 0; j < this->data[i].size(); ++j) {
						float sum = 0.0f;
						for (int offset = 0; offset < Cols; ++offset) {
							sum += this->data[i][offset] * mat.data[offset][j];
						}
						out->data[i][j] = sum;
					}
				}
				return *out;
			} else {
				CK_WARN("Matrix 1 Column and Matrix 2 Row dimension mismatch! ({0} =/= {1})\n\tReturned left matrix...", Cols, mat.Rows);
				return *this;
			}
		}

		Matrix operator+(Matrix& left, const Matrix& right) { return left.Add(right); }
		Matrix operator+(Matrix& mat, float constant){ return mat.Add(constant); }
		Matrix operator+(float constant, Matrix& mat){ return mat.Add(constant); }
		Matrix& Matrix::operator+=(const Matrix& mat) { return this->Add(mat); }
		Matrix& Matrix::operator+=(float constant) { return this->Add(constant); }

		Matrix operator-(Matrix& left, const Matrix& right) { return left.Sub(right); }
		Matrix operator-(Matrix& mat, float constant) { return mat.Sub(constant); }
		Matrix operator-(float constant, Matrix& mat) { return mat.Sub(constant); }
		Matrix& Matrix::operator-=(const Matrix& mat) { return this->Sub(mat); }
		Matrix& Matrix::operator-=(float constant) { return this->Sub(constant); }

		Matrix operator*(Matrix& left, const Matrix& right) { return left.Multiply(right); }
		Matrix operator*(Matrix& mat, float scalar) { return mat.Multiply(scalar); }
		Matrix operator*(float scalar, Matrix& mat) { return mat.Multiply(scalar); }
		Matrix& Matrix::operator*=(const Matrix& mat) { return this->Multiply(mat); }
		Matrix& Matrix::operator*=(float scalar) { return this->Multiply(scalar); }

		Matrix operator/(Matrix& mat, float scalar){ return mat.Multiply((1/scalar)); }
		Matrix operator/(float scalar, Matrix& mat){ return mat.Multiply((1/scalar)); }
		Matrix& Matrix::operator/=(float scalar) { return this->Multiply((1/scalar)); }
		

		Matrix Matrix::Identity(int rows, int cols) {
			return Matrix(rows, cols, 1.0f);
		}

		Matrix& Matrix::Transpose() {
			Matrix* out = new Matrix(this->Cols, this->Rows);
			for (int i = 0; i < out->Rows; ++i) {
				for (int j = 0; j < out->Cols; ++j) {
					out->data[i][j] = this->data[j][i];
				}
			}
			return *out;
		}


		Matrix& Matrix::Cross(const Matrix& mat) {
			return *this;
		}

		float Matrix::Dot(Matrix& mat){
			int a, b;
			
			float result = 0.0f;

			if (this->Compatible(mat, MULTIPLY)) {
				Matrix& matrix = this->Multiply(mat);
				a = matrix.Rows;
				b = matrix.Cols;

				if (a == 1 || b == 1) {
					result = matrix.Magnitude();
				}
				else {
					CK_WARN("Dot product results in Matrix, not a scalar, consider using Multiply()!");
					result = std::nanf("1");
				}
			}
			else {
				CK_WARN("Matricies cannot be multiplied (aren't compatible)!");
				result = std::nanf("1");
			}

			return result;
		}

		float Matrix::Magnitude() {
			if (this->Cols == 1 || this->Rows == 1) {
				float result = 0.0f;
				for (int i = 0; i < this->Rows; ++i) {
					for (int j = 0; j < this->Cols; ++j) {
						result += this->data[i][j] * this->data[i][j];
					}
				}
				return sqrt(result);
			}
		}

		float Matrix::Det(){
			return 0.0f;
		}


		bool Matrix::Compatible(const Matrix& mat, int operation) {
			switch (operation) {
			case ADD:
				if (Cols == mat.Cols && Rows == mat.Rows) {
					return true;
				} else {
					return false;
				}
			case SUBTRACT:
				if (Cols == mat.Cols && Rows == mat.Rows) {
					return true;
				}
				else {
					return false;
				}
			case MULTIPLY:
				if (Cols == mat.Rows) {
					return true;
				}
				else {
					return false;
				}
			}
		}

		std::ostream& operator<<(std::ostream& os, Matrix& mat){
			
			os << mat.Rows << " x " << mat.Cols << " - Matrix: " << std::endl;

			for (int i = 0; i < mat.data.size(); ++i) {
				for (int j = 0; j < mat.data[i].size(); ++j) {
					if (i == mat.Rows - 1 && j == mat.Cols -1) {
						os << mat.data[i][j] << " ";
					}
					else {
						os << mat.data[i][j] << ", ";
					}
				}
				os << std::endl;
			}
			return os;
		}

	}

}