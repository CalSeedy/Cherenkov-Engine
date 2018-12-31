#include "ckpch.h"
#include "Maths.h"
#include "Log.h"

namespace Cherenkov {
	namespace Maths {

		Matrix::Matrix(int rows, int cols) {
			Rows = rows;
			Cols = cols;

			data.resize(rows, std::vector<float>(cols));

		}

		Matrix::Matrix(int rows, int cols, float* values) {

			Rows = rows;
			Cols = cols;
			data.resize(rows, std::vector<float>(cols));
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					data[i][j] = values[j + i * cols];
				}
			}

		}

		Matrix::Matrix(int rows, int cols, float diagonal) {
			Rows = rows;
			Cols = cols;
			data.resize(rows, std::vector<float>(cols));

			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					if (i == j) {
						data[i][j] = diagonal;
					}
				}
			}
		}

		Matrix::~Matrix() {
			data.clear();

		}


		bool Matrix::Compatible(const Matrix& mat, int operation) {
			switch (operation) {
			case ADD:
				if (Cols == mat.Cols && Rows == mat.Rows) {
					return true;
				}
				else { 
					CK_WARN("Matrix dimensions aren't equal for both matricies! ({0}x{1} =/= {2}x{3})", Rows, Cols, mat.Rows, mat.Cols);
					return false; }
				break;

			case SUBTRACT:
				if (Cols == mat.Cols && Rows == mat.Rows) {
					return true;
				}
				else {
					CK_WARN("Matrix dimensions aren't equal for both matricies! ({0}x{1} =/= {2}x{3})", Rows, Cols, mat.Rows, mat.Cols);
					return false;
				}
				break;

			case MULTIPLY:
				if (Cols == mat.Rows) {
					return true;
				}
				else {
					CK_WARN("Matrix 1 Column and Matrix 2 Row dimension mismatch! ({0} =/= {1})", Cols, mat.Rows);
					return false;
				}
				break;
			}

			return false;
		}

		Matrix Matrix::Identity(int rows, int cols) {
			return Matrix(rows, cols, 1.0f);
		}

		Matrix Matrix::Add(const Matrix& mat){
		
			if (this->Compatible(mat, ADD)) {
				Matrix out = Matrix(this->Rows, this->Cols);

				for (int i = 0; i < this->Rows; i++) {
					for (int j = 0; j < this->Cols; j++) {
						out.data[i][j] = this->data[i][j] + mat.data[i][j];
					}
				}
				return out;
			} else {
				return *this;
			}
		}

		Matrix Matrix::Add(float constant) {
			Matrix out = Matrix(this->Rows, this->Cols);
			for (int i = 0; i < this->Rows; i++) {
				for (int j = 0; j < this->Cols; j++) {
					out.data[i][j] = this->data[i][j] + constant;
				}
			}
			return out;
		}

		Matrix Matrix::Sub(const Matrix& mat){
			if (this->Compatible(mat, SUBTRACT)) {
				Matrix out = Matrix(this->Rows, this->Cols);
				for (int i = 0; i < this->Rows; i++) {
					for (int j = 0; j < this->Cols; j++) {
						out.data[i][j] = this->data[i][j] - mat.data[i][j];
					}
				}
				return out;
			} else {
				return *this;
			}
		}
		
		Matrix Matrix::Sub(float constant) {
			Matrix out = Matrix(this->Rows, this->Cols);
			for (int i = 0; i < this->Rows; i++) {
				for (int j = 0; j < this->Cols; j++) {
					out.data[i][j] = this->data[i][j] - constant;
				}
			}
			return out;
		}

		Matrix Matrix::Divide(float scalar) {
			Matrix out = Matrix(this->Rows, this->Cols);
			for (int i = 0; i < this->Rows; i++) {
				for (int j = 0; j < this->Cols; j++) {
					out.data[i][j] = this->data[i][j] / scalar;
				}
			}
			return out;
		}

		Matrix Matrix::Multiply(float scalar){
			Matrix out = Matrix(this->Rows, this->Cols);
			for (int i = 0; i < this->Rows; i++) {
				for (int j = 0; j < this->Cols; j++) {
					out.data[i][j] = this->data[i][j] * scalar;
				}
			}
			return out;
		}

		Matrix Matrix::Multiply(const Matrix& mat) {
			int inR1 = this->Rows;
			int inR2 = mat.Rows;
			int inC1 = this->Cols;
			int inC2 = mat.Cols;

			int outR = mat.Cols;
			int outC = this->Rows;

			Matrix outMat = Matrix(outR, outC);

			if (inC1 == inR2) {
				for (int i = 0; i < inR1; i++) {
					for (int j = 0; j < inC2; j++) {
						float sum = 0.0f;
						for (int off = 0; off < inC1; off++) {
							sum += this->data[i][off] * mat.data[off][j];
						}
						outMat.data[i][j] = sum;
					}
				}
				return outMat;
			}
			else {
				CK_ERROR("Matrix 1 Column and Matrix 2 Row dimension mismatch! ({0} =/= {1})", this->Cols, mat.Rows);
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
		
		std::ostream& operator<<(std::ostream& os, const Matrix& mat){
			
			os << mat.Rows << " x " << mat.Cols << " - Matrix: " << std::endl;

			for (int i = 0; i < mat.Rows; i++) {
				for (int j = 0; j < mat.Cols; j++) {
					os << mat.data[i][j] << ", ";
				}
				os << std::endl;
			}
			return os;
		}

	}

}