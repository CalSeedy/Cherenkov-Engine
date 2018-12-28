#include "ckpch.h"
#include "Cherenkov/Maths.h"


namespace Cherenkov {
	namespace Maths {

		Matrix::Matrix(int rows, int cols) {
			Rows = rows;
			Cols = cols;

			data = new float*[Rows];

			for (int i = 0; i < rows; i++)
			{
				data[i] = new float[cols];
				for (int j = 0; j < cols; j++)
				{
					data[i][j] = 0;
				}
			}

		}

		Matrix::Matrix(int rows, int cols, float* values) {

			Rows = rows;
			Cols = cols;
			data = new float*[Rows];

			for (int i = 0; i < rows; i++)
			{
				data[i] = new float[cols];
				for (int j = 0; j < cols; j++)
				{
					data[i][j] = values[i + j * Cols];
				}
			}

		}

		Matrix::Matrix(int rows, int cols, float diagonal) {
			Rows = rows;
			Cols = cols;
			data[(Rows*Cols)] = { 0 };

			memset(data, 0, rows*cols * sizeof(float));
			for (int i = 0; i < Rows; i++) {
				for (int j = 0; j < Cols; j++) {
					if (i == j) {
						*data[i + (j*Cols)] = diagonal;
					}
				}
			}
		}

		Matrix::~Matrix() {
			for (int i = 0; i < Rows; i++)
				delete[] data[i];
		}


		bool Matrix::Compatible(const Matrix& mat, int operation) {
			switch (operation) {
			case ADD:
				if (Cols == mat.Cols && Rows == mat.Rows) {
					return true;
				}
				else { 
					CK_ERROR("Matrix dimensions aren't equal for both matricies! ({0}x{1} =/= {2}x{3})", Rows, Cols, mat.Rows, mat.Cols);
					return false; }
				break;

			case SUBTRACT:
				if (Cols == mat.Cols && Rows == mat.Rows) {
					return true;
				}
				else {
					CK_ERROR("Matrix dimensions aren't equal for both matricies! ({0}x{1} =/= {2}x{3})", Rows, Cols, mat.Rows, mat.Cols);
					return false;
				}
				break;

			case MULTIPLY:
				if (Cols == mat.Rows) {
					return true;
				}
				else {
					CK_ERROR("Matrix 1 Column and Matrix 2 Row dimension mismatch! ({0} =/= {1})", Cols, mat.Rows);
					return false;
				}
				break;
			}

			return false;
		}

		Matrix Matrix::Identity(int rows, int cols) {
			return Matrix(rows, cols, 1.0f);
		}

		Matrix& Matrix::Add(const Matrix& mat){
		
			if (this->Compatible(mat, ADD)) {
				for (int i = 0; i < Rows; i++) {
					for (int j = 0; j < Cols; j++) {
						data[i][j] += mat.data[i][j];
					}
				}
				return *this;
			}
		}

		Matrix& Matrix::Add(float constant) {

			for (int i = 0; i < Rows; i++) {
				for (int j = 0; j < Cols; j++) {
					data[i][j] += constant;
				}
			}
			return *this;
		}

		Matrix& Matrix::Sub(const Matrix& mat){
			if (this->Compatible(mat, SUBTRACT)) {

				for (int i = 0; i < Rows; i++) {
					for (int j = 0; j < Cols; j++) {
						data[i][j] -= mat.data[i][j];
					}
				}
				return *this;
			}
		}
		
		Matrix& Matrix::Sub(float constant) {
			for (int i = 0; i < Rows; i++) {
				for (int j = 0; j < Cols; j++) {
					data[i][j] -= constant;
				}
			}
			return *this;
		}

		Matrix& Matrix::Divide(float scalar) {
			for (int i = 0; i < Rows; i++) {
				for (int j = 0; j < Cols; j++) {
					data[i][j] /= scalar;
				}
			}
			return *this;
		}

		Matrix& Matrix::Multiply(float scalar){
			for (int i = 0; i < Rows; i++) {
				for (int j = 0; j < Cols; j++) {
					data[i][j] *= scalar;
				}
			}
			return *this;
		}

		Matrix& Matrix::Multiply(const Matrix& mat) {
			if (this->Compatible(mat, MULTIPLY)) {

				int outRows = this->Rows;
				int outCols = mat.Cols;

				float** temp = new float*[outRows];

				for (int i = 0; i < outRows; i++)
				{
					temp[i] = new float[outCols];
					for (int j = 0; j < outCols; j++)
					{
						temp[i][j] = 0;
					}
				}
				for (int i = 0; i < this->Rows; i++) {
					for (int j = 0; j < this->Cols; j++) {
						float sum = 0.0f;
						for (int offset = 0; offset < outCols; offset++) {
							sum += data[i][j + offset] * mat.data[i + offset][j];

						}
						temp[i][j] = sum;
					}
				}
				data = temp;

				for (int i = 0; i < outRows; i++) {
					delete[] temp[i];
				}

				return *this;
			}
		}

		Matrix operator+(Matrix& left, const Matrix& right) { return left.Add(right); }
		Matrix operator+(Matrix mat, float constant){ return mat.Add(constant); }
		Matrix operator+(float constant, Matrix mat){ return mat.Add(constant); }
		Matrix& Matrix::operator+=(const Matrix& mat) { return this->Add(mat); }
		Matrix& Matrix::operator+=(float constant) { return this->Add(constant); }

		Matrix operator-(Matrix& left, const Matrix& right) { return left.Sub(right); }
		Matrix operator-(Matrix mat, float constant) { return mat.Sub(constant); }
		Matrix operator-(float constant, Matrix mat) { return mat.Sub(constant); }
		Matrix& Matrix::operator-=(const Matrix& mat) { return this->Sub(mat); }
		Matrix& Matrix::operator-=(float constant) { return this->Sub(constant); }

		Matrix operator*(Matrix& left, const Matrix& right) { return left.Multiply(right); }
		Matrix operator*(Matrix mat, float scalar) { return mat.Multiply(scalar); }
		Matrix operator*(float scalar, Matrix mat) { return mat.Multiply(scalar); }
		Matrix& Matrix::operator*=(const Matrix& mat) { return this->Multiply(mat); }
		Matrix& Matrix::operator*=(float scalar) { return this->Multiply(scalar); }

		Matrix operator/(Matrix mat, float scalar){ return mat.Multiply((1/scalar)); }
		Matrix operator/(float scalar, Matrix mat){ return mat.Multiply((1/scalar)); }
		Matrix& Matrix::operator/=(float scalar) { return this->Multiply((1/scalar)); }
		

	}

}