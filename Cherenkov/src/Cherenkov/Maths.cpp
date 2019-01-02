
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


		float Matrix::Det(){
			
			float result;
			int row, col;
			if (Cols == Rows) {
				switch (Rows) {
				case 1:
				{
					result = this->data[0][0];
					break;
				}
				case 2:
				{
					result = (this->data[0][0] * this->data[1][1]) - (this->data[0][1] * this->data[1][0]);
					break;
				}
				case 3:
				{
					float temp1 = this->data[0][0] * ((this->data[1][1] * this->data[2][2]) - (this->data[1][2] * this->data[2][1]));
					float temp2 = this->data[0][1] * ((this->data[1][0] * this->data[2][2]) - (this->data[1][2] * this->data[2][0]));
					float temp3 = this->data[0][2] * ((this->data[1][0] * this->data[2][1]) - (this->data[1][1] * this->data[2][0]));

					result = temp1 - temp2 + temp3;
					break;
				}
				case 4:
				{
					/*
					
						00 01 02 03
						10 11 12 13
						20 21 22 23
						30 31 32 33

					*/
					//cols 123
					float temp11 = this->data[1][1] * ((this->data[2][2] * this->data[3][3]) - (this->data[2][3] * this->data[3][2]));
					float temp12 = this->data[1][2] * ((this->data[2][1] * this->data[3][3]) - (this->data[2][3] * this->data[3][1]));
					float temp13 = this->data[1][3] * ((this->data[2][1] * this->data[3][2]) - (this->data[2][2] * this->data[3][1]));
					float temp1 = this->data[0][0] * (temp11 - temp12 + temp13);

					
					//cols 023
					float temp21 = this->data[1][0] * ((this->data[2][2] * this->data[3][3]) - (this->data[2][3] * this->data[3][2]));
					float temp22 = this->data[1][2] * ((this->data[2][0] * this->data[3][3]) - (this->data[2][3] * this->data[3][0]));
					float temp23 = this->data[1][3] * ((this->data[2][0] * this->data[3][2]) - (this->data[2][2] * this->data[3][0]));
					float temp2 = this->data[0][1] * (temp21 - temp22 + temp23);
					


					//cols 013
					float temp31 = this->data[1][0] * ((this->data[2][1] * this->data[3][3]) - (this->data[2][3] * this->data[3][1]));
					float temp32 = this->data[1][1] * ((this->data[2][0] * this->data[3][3]) - (this->data[2][3] * this->data[3][0]));
					float temp33 = this->data[1][3] * ((this->data[2][0] * this->data[3][1]) - (this->data[2][1] * this->data[3][0]));
					float temp3 = this->data[0][2] * (temp31 - temp32 + temp33);
					
					//cols 012
					float temp41 = this->data[1][0] * ((this->data[2][1] * this->data[3][2]) - (this->data[2][2] * this->data[3][1]));
					float temp42 = this->data[1][1] * ((this->data[2][0] * this->data[3][2]) - (this->data[2][2] * this->data[3][0]));
					float temp43 = this->data[1][2] * ((this->data[2][0] * this->data[3][1]) - (this->data[2][1] * this->data[3][0]));
					float temp4 = this->data[0][3] * (temp41 - temp42 + temp43);

					result = temp1 - temp2 + temp3 - temp4;
					break;
				}
				}
			}
			else {
				CK_WARN("Not a square matrix, det of a {0} by {1} matrix is undefined!", Rows, Cols);
				result = std::nanf("1");
			}
			return result;
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


		Vector::Vector(int dim){
			Dim = dim;
			this->data = std::vector<float> (dim);

			for (int i = 0; i < this->data.size(); ++i)
			{
					data[i] = 0.0f;
			}
		}

		Vector::Vector(int dim, float *values){
			Dim = dim;
			data = std::vector<float>(dim);

			for (int i = 0; i < data.size(); ++i)
			{
				data[i] = values[i];
			}
		}

		Vector::Vector(std::vector<float> values) {
			Dim = values.size();
			this->data = values;
		}

		Vector::~Vector(){
			data.clear();
		}

		Vector& Vector::Add(float constant){
			Vector* out = new Vector(Dim);

			for (int i = 0; i < this->data.size(); ++i) {
				out->data[i] = this->data[i] + constant;
				
			}
			return *out;
		}

		Vector& Vector::Add(const Vector& vec){
			if (this->Compatible(vec, ADD)) {
				Vector* out = new Vector(Dim);

				for (int i = 0; i < this->data.size(); ++i) {
					out->data[i] = this->data[i] + vec.data[i];
				}

				return *out;
			}
			else {
				CK_WARN("Vector dimensions aren't equal! (1x{0} =/= 1x{1})\nReturned left vector...", Dim, vec.Dim);
				return *this;
			}
		}

		Vector operator+(Vector& left, const Vector& right) { return left.Add(right); }
		Vector operator+(Vector& vec, float constant) { return vec.Add(constant); }
		Vector operator+(float constant, Vector& vec){ return vec.Add(constant); }
		Vector& Vector::operator+=(const Vector& vec) { return this->Add(vec); }
		Vector& Vector::operator+=(float constant) { return this->Add(constant); }


		Vector& Vector::Sub(float constant) {
			Vector* out = new Vector(Dim);

			for (int i = 0; i < this->data.size(); ++i) {
				out->data[i] = this->data[i] - constant;

			}
			return *out;
		}

		Vector& Vector::Sub(const Vector& vec) {
			if (this->Compatible(vec, SUBTRACT)) {

				Vector* out = new Vector(Dim);

				for (int i = 0; i < this->data.size(); ++i) {
					out->data[i] = this->data[i] - vec.data[i];
				}
				return *out;
			}
			else {
				CK_WARN("Vector dimensions aren't equal! (1x{0} =/= 1x{1})\nReturned left vector...", Dim, vec.Dim);
				return *this;
			}
		}

		Vector operator-(Vector& left, const Vector& right) { return left.Sub(right); }
		Vector operator-(Vector& vec, float constant) { return vec.Sub(constant); }
		Vector operator-(float constant, Vector& vec) { return vec.Sub(constant); }
		Vector& Vector::operator-=(const Vector& vec) { return this->Sub(vec); }
		Vector& Vector::operator-=(float constant) {return this->Sub(constant); }


		Vector& Vector::Multiply(float scalar) {
			Vector* out = new Vector(Dim);

			for (int i = 0; i < this->data.size(); ++i) {
				out->data[i] = this->data[i] * scalar;

			}
			return *out;
		}

		Vector& Vector::Multiply(const Vector& vec) { 
			if (this->Compatible(vec, MULTIPLY)) {

				Vector* out = new Vector(Dim);
				for (int i = 0; i < this->data.size(); ++i) {
						float sum = 0.0f;
							sum += this->data[i] * vec.data[i];
						out->data[i] = sum;
				}
				return *out;
			}
			else {
				CK_WARN("Vector dimensions aren't equal! (1x{0} =/= 1x{1})\nReturned left vector...", Dim, vec.Dim);
				return *this;
			}
		}
		Vector operator*(Vector& left, const Vector& right) { return left.Multiply(right); }
		Vector operator*(Vector& vec, float scalar) { return vec.Multiply(scalar); }
		Vector operator*(float scalar, Vector& vec) { return vec.Multiply(scalar); }
		Vector& Vector::operator*=(const Vector& vec) { return this->Multiply(vec); }
		Vector& Vector::operator*=(float scalar) { return this->Multiply(scalar); }

		Vector& Vector::Divide(float scalar) {
			Vector* out = new Vector(Dim);

			for (int i = 0; i < this->data.size(); ++i) {
				out->data[i] = this->data[i] / scalar;

			}
			return *out;
		}

		Vector operator/(Vector& vec, float scalar) { return vec.Divide(scalar); }
		Vector& Vector::operator/=(float scalar) { return this->Divide(scalar); }

		std::ostream& operator<<(std::ostream& os, Vector& vec) {
			os << "1 x " << vec.Dim << " - Vector: " << std::endl;

			for (int i = 0; i < vec.data.size(); ++i) {
					if (i == vec.Dim - 1) {
						os << vec.data[i] << " ";
					}
					else {
						os << vec.data[i] << ", ";
					}
			}
			os << std::endl;

			return os;
		}





		float Vector::Dot(Vector& vec) {

			float result = 0.0f;

			if (this->Compatible(vec, MULTIPLY)) {
				
					result = vec.Magnitude();
			}
			else {
				CK_WARN("Vectors cannot be multiplied (aren't compatible)!");
				result = std::nanf("1");
			}

			return result;
		}

		float Vector::Magnitude() {
			
			float result = 0.0f;
			for (int i = 0; i < this->Dim; ++i) {
				result += this->data[i] * this->data[i];
				
			}
			return sqrt(result);
			
		}

		bool Vector::Compatible(const Vector& vec, int operation) {
			switch (operation) {
			case ADD:
				if (Dim == vec.Dim) {
					return true;
				}
				else {
					return false;
				}
			case SUBTRACT:
				if (Dim == vec.Dim) {
					return true;
				}
				else {
					return false;
				}
			case MULTIPLY:
				if (Dim == vec.Dim) {
					return true;
				}
				else {
					return false;
				}
			}
		}


	}

}