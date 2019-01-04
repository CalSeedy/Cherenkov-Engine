
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

			this->data = std::vector<std::vector<double> >(rows, std::vector<double>(cols));

			for (int i = 0; i < this->data.size(); ++i)
			{
				for (int j = 0; j < this->data[i].size(); ++j)
				{
					data[i][j] = 0.0f;
				}
			}
		}

		Matrix::Matrix(int rows, int cols, double* values) {
			Rows = rows;
			Cols = cols;
			this->data = std::vector<std::vector<double> >(rows, std::vector<double>(cols));

			for (int i = 0; i < this->data.size(); ++i)
			{
				for (int j = 0; j < this->data[i].size(); ++j)
				{
					data[i][j] = values[i + j * rows];
				}
			}

		}

		Matrix::Matrix(int rows, int cols, double diagonal) {
			Rows = rows;
			Cols = cols;

			this->data = std::vector<std::vector<double> >(rows, std::vector<double>(cols));

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

		Matrix::Matrix(std::vector<std::vector<double> >& values) {
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
				Matrix* out = new Matrix(Rows, Cols);

				for (int i = 0; i < this->data.size(); ++i) {
					for (int j = 0; j < this->data[i].size(); ++j) {
						out->data[i][j] = this->data[i][j] + mat.data[i][j];
					}
				}
				return *out;
			}
			else {
				CK_WARN("Matrix dimensions aren't equal for both matricies! ({0}x{1} =/= {2}x{3})\nReturned left matrix...", Rows, Cols, mat.Rows, mat.Cols);
				return *this;
			}
		}

		Matrix& Matrix::Add(double constant) {
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

		Matrix& Matrix::Sub(double constant) {
			Matrix* out = new Matrix(Rows, Cols);
			for (int i = 0; i < this->data.size(); ++i) {
				for (int j = 0; j < this->data[i].size(); ++j) {
					out->data[i][j] = this->data[i][j] - constant;
				}
			}
			return *out;
		}

		Matrix& Matrix::Divide(double scalar) {
			Matrix* out = new Matrix(Rows, Cols);
			for (int i = 0; i < this->data.size(); ++i) {
				for (int j = 0; j < this->data[i].size(); ++j) {
					out->data[i][j] = this->data[i][j] / scalar;
				}
			}
			return *out;
		}

		Matrix& Matrix::Multiply(double scalar) {
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
						double sum = 0.0f;
						for (int offset = 0; offset < Cols; ++offset) {
							sum += this->data[i][offset] * mat.data[offset][j];
						}
						out->data[i][j] = sum;
					}
				}
				return *out;
			}
			else {
				CK_WARN("Matrix 1 Column and Matrix 2 Row dimension mismatch! ({0} =/= {1})\n\tReturned left matrix...", Cols, mat.Rows);
				return *this;
			}
		}

		Matrix operator+(Matrix& left, const Matrix& right) { return left.Add(right); }
		Matrix operator+(Matrix& mat, double constant) { return mat.Add(constant); }
		Matrix operator+(double constant, Matrix& mat) { return mat.Add(constant); }
		Matrix& Matrix::operator+=(const Matrix& mat) { return this->Add(mat); }
		Matrix& Matrix::operator+=(double constant) { return this->Add(constant); }

		Matrix operator-(Matrix& left, const Matrix& right) { return left.Sub(right); }
		Matrix operator-(Matrix& mat, double constant) { return mat.Sub(constant); }
		Matrix operator-(double constant, Matrix& mat) { return mat.Sub(constant); }
		Matrix& Matrix::operator-=(const Matrix& mat) { return this->Sub(mat); }
		Matrix& Matrix::operator-=(double constant) { return this->Sub(constant); }

		Matrix operator*(Matrix& left, const Matrix& right) { return left.Multiply(right); }
		Matrix operator*(Matrix& mat, double scalar) { return mat.Multiply(scalar); }
		Matrix operator*(double scalar, Matrix& mat) { return mat.Multiply(scalar); }
		Matrix& Matrix::operator*=(const Matrix& mat) { return this->Multiply(mat); }
		Matrix& Matrix::operator*=(double scalar) { return this->Multiply(scalar); }

		Matrix operator/(Matrix& mat, double scalar) { return mat.Multiply((1 / scalar)); }
		Matrix& Matrix::operator/=(double scalar) { return this->Multiply((1 / scalar)); }


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


		//Created by Martin Thoma: https://martin-thoma.com/inverting-matrices/
		//Adapted to handle an n by n Matrix
		Matrix& Matrix::Inverse() {
			Matrix* temp = new Matrix(this->data);
			for (int i = 0; i < this->data.size(); ++i) {
				for (int j = 0; j < this->data.size(); ++j) {
					if (i == j) {
						temp->data[i].push_back(1);
					}
					else {
						temp->data[i].push_back(0);
					}
				}
			}

			int n = temp->data.size();

			for (int i = 0; i < n; i++) {
				// Search for maximum in temp column
				double maxEl = abs(temp->data[i][i]);
				int maxRow = i;
				for (int k = i + 1; k < n; k++) {
					if (abs(temp->data[k][i]) > maxEl) {
						maxEl = temp->data[k][i];
						maxRow = k;
					}
				}

				// Swap maximum row with current row (column by column)
				for (int k = i; k < 2 * n; k++) {
					double tmp = temp->data[maxRow][k];
					temp->data[maxRow][k] = temp->data[i][k];
					temp->data[i][k] = tmp;
				}

				// Make all rows below temp one 0 in current column
				for (int k = i + 1; k < n; k++) {
					double c = -temp->data[k][i] / temp->data[i][i];
					for (int j = i; j < 2 * n; j++) {
						if (i == j) {
							temp->data[k][j] = 0;
						}
						else {
							temp->data[k][j] += c * temp->data[i][j];
						}
					}
				}
			}

			// Solve equation Ax=b for an upper triangular matrix temp->data
			for (int i = n - 1; i >= 0; i--) {
				for (int k = n; k < 2 * n; k++) {
					temp->data[i][k] /= temp->data[i][i];
				}
				// temp is not necessary, but the output looks nicer:
				temp->data[i][i] = 1;

				for (int rowModify = i - 1; rowModify >= 0; rowModify--) {
					for (int columModify = n; columModify < 2 * n; columModify++) {
						temp->data[rowModify][columModify] -= temp->data[i][columModify]
							* temp->data[rowModify][i];
					}
					// temp is not necessary, but the output looks nicer:
					temp->data[rowModify][i] = 0;
				}
			}


			Matrix* out = new Matrix(this->data.size(), this->data.size());


			for (int i = 0; i < this->data.size(); ++i) {
				for (int j = 0; j < this->data[i].size(); ++j) {

					out->data[i][j] = temp->data[i][j + (this->data.size())];

				}
			}

			temp->~Matrix();

			return *out;
		}


		double Matrix::Det() {

			double result;
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
					double temp1 = this->data[0][0] * ((this->data[1][1] * this->data[2][2]) - (this->data[1][2] * this->data[2][1]));
					double temp2 = this->data[0][1] * ((this->data[1][0] * this->data[2][2]) - (this->data[1][2] * this->data[2][0]));
					double temp3 = this->data[0][2] * ((this->data[1][0] * this->data[2][1]) - (this->data[1][1] * this->data[2][0]));

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
					double temp11 = this->data[1][1] * ((this->data[2][2] * this->data[3][3]) - (this->data[2][3] * this->data[3][2]));
					double temp12 = this->data[1][2] * ((this->data[2][1] * this->data[3][3]) - (this->data[2][3] * this->data[3][1]));
					double temp13 = this->data[1][3] * ((this->data[2][1] * this->data[3][2]) - (this->data[2][2] * this->data[3][1]));
					double temp1 = this->data[0][0] * (temp11 - temp12 + temp13);


					//cols 023
					double temp21 = this->data[1][0] * ((this->data[2][2] * this->data[3][3]) - (this->data[2][3] * this->data[3][2]));
					double temp22 = this->data[1][2] * ((this->data[2][0] * this->data[3][3]) - (this->data[2][3] * this->data[3][0]));
					double temp23 = this->data[1][3] * ((this->data[2][0] * this->data[3][2]) - (this->data[2][2] * this->data[3][0]));
					double temp2 = this->data[0][1] * (temp21 - temp22 + temp23);



					//cols 013
					double temp31 = this->data[1][0] * ((this->data[2][1] * this->data[3][3]) - (this->data[2][3] * this->data[3][1]));
					double temp32 = this->data[1][1] * ((this->data[2][0] * this->data[3][3]) - (this->data[2][3] * this->data[3][0]));
					double temp33 = this->data[1][3] * ((this->data[2][0] * this->data[3][1]) - (this->data[2][1] * this->data[3][0]));
					double temp3 = this->data[0][2] * (temp31 - temp32 + temp33);

					//cols 012
					double temp41 = this->data[1][0] * ((this->data[2][1] * this->data[3][2]) - (this->data[2][2] * this->data[3][1]));
					double temp42 = this->data[1][1] * ((this->data[2][0] * this->data[3][2]) - (this->data[2][2] * this->data[3][0]));
					double temp43 = this->data[1][2] * ((this->data[2][0] * this->data[3][1]) - (this->data[2][1] * this->data[3][0]));
					double temp4 = this->data[0][3] * (temp41 - temp42 + temp43);

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
				}
				else {
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

#undef near
#undef far

		Matrix Matrix::Orthographic(float left, float right, float bottom, float top, float near, float far) {

			Matrix out = Identity(4, 4);

			out.data[0][0] = 2.0 / (right - left);
			out.data[1][1] = 2.0 / (top - bottom);
			out.data[2][2] = -2.0 / (far - near);
			out.data[0][3] = -(right + left) / (right - left);
			out.data[1][3] = -(top + bottom) / (top - bottom);
			out.data[2][3] = -(far + near) / (far - near);

			return out;

		}


		Matrix Matrix::Perspective(float fov, float aspectRatio, float near, float far) {

			Matrix out = Matrix(4, 4);

			out.data[0][0] = 1.0 / (atan(fov / 2));
			out.data[1][1] = 1.0 / (atan(fov / 2));
			out.data[2][2] = -(near + far) / (near - far);
			out.data[2][3] = (2 * near * far) / (near - far);
			out.data[3][2] = 1.0;

			return out;
		}

		Vector Matrix::getRow(int row) {
			Vector out = Vector(this->data[0].size());

			for (int i = 0; i < this->data.size(); ++i) {
				out.data[i] = this->data[row][i];
			}

			return out;
		}


		void Matrix::setRow(int row, Vector rowVec) {
			this->data[row] = rowVec.data;
		}

		Vector Matrix::getColumn(int column) {
			Vector out = Vector(this->data.size());

			for (int i = 0; i < this->data.size(); ++i) {
				out.data[i] = this->data[i][column];
			}

			return out;
		}

		void Matrix::setColumn(int column, Vector columnVec) {

			for (int i = 0; i < this->data.size(); ++i) {
				this->data[i][column] = columnVec.data[i];
			}
		}


		std::ostream& operator<<(std::ostream& os, Matrix& mat) {

			os << mat.Rows << " x " << mat.Cols << " - Matrix: " << std::endl;

			for (int i = 0; i < mat.data.size(); ++i) {
				for (int j = 0; j < mat.data[i].size(); ++j) {
					if (i == mat.Rows - 1 && j == mat.Cols - 1) {
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


		Vector::Vector(int dim) {
			Dim = dim;
			this->data = std::vector<double>(dim);

			for (int i = 0; i < this->data.size(); ++i)
			{
				data[i] = 0.0f;
			}
		}

		Vector::Vector(int dim, double *values) {
			Dim = dim;
			data = std::vector<double>(dim);

			for (int i = 0; i < data.size(); ++i)
			{
				data[i] = values[i];
			}
		}

		Vector::Vector(std::vector<double> values) {
			Dim = values.size();
			this->data = values;
		}

		Vector::~Vector() {
			data.clear();
		}

		Vector& Vector::Add(double constant) {
			Vector* out = new Vector(Dim);

			for (int i = 0; i < this->data.size(); ++i) {
				out->data[i] = this->data[i] + constant;

			}
			return *out;
		}

		Vector& Vector::Add(const Vector& vec) {
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
		Vector operator+(Vector& vec, double constant) { return vec.Add(constant); }
		Vector operator+(double constant, Vector& vec) { return vec.Add(constant); }
		Vector& Vector::operator+=(const Vector& vec) { return this->Add(vec); }
		Vector& Vector::operator+=(double constant) { return this->Add(constant); }


		Vector& Vector::Sub(double constant) {
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
		Vector operator-(Vector& vec, double constant) { return vec.Sub(constant); }
		Vector operator-(double constant, Vector& vec) { return vec.Sub(constant); }
		Vector& Vector::operator-=(const Vector& vec) { return this->Sub(vec); }
		Vector& Vector::operator-=(double constant) { return this->Sub(constant); }


		Vector& Vector::Multiply(double scalar) {
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
					double sum = 0.0f;
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
		Vector operator*(Vector& vec, double scalar) { return vec.Multiply(scalar); }
		Vector operator*(double scalar, Vector& vec) { return vec.Multiply(scalar); }
		Vector& Vector::operator*=(const Vector& vec) { return this->Multiply(vec); }
		Vector& Vector::operator*=(double scalar) { return this->Multiply(scalar); }

		Vector& Vector::Divide(double scalar) {
			Vector* out = new Vector(Dim);

			for (int i = 0; i < this->data.size(); ++i) {
				out->data[i] = this->data[i] / scalar;

			}
			return *out;
		}

		Vector operator/(Vector& vec, double scalar) { return vec.Divide(scalar); }
		Vector& Vector::operator/=(double scalar) { return this->Divide(scalar); }

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


		Vector& Vector::Cross(Vector& vec) {
			if (this->Compatible(vec, MULTIPLY)) {
				if (this->Dim == 3) {
					double outX = (this->data[1] * vec.data[2]) - (this->data[2] * vec.data[1]);
					double outY = (this->data[2] * vec.data[0]) - (this->data[0] * vec.data[2]);
					double outZ = (this->data[0] * vec.data[1]) - (this->data[1] * vec.data[0]);
					double values[3] = { outX, outY, outZ };

					Vector* out = new Vector(3, values);
					return *out;
				}
				else {
					CK_WARN("Cross product operation only valid for 3 dimensions (7 actually, but cba to code that)!\nReturned left vector...");
					return *this;
				}
			}
		}


		double Vector::Dot(Vector& vec) {

			double result = 0.0f;

			if (this->Compatible(vec, MULTIPLY)) {

				result = vec.Magnitude();
			}
			else {
				CK_WARN("Vectors cannot be multiplied (aren't compatible)!");
				result = std::nanf("1");
			}

			return result;
		}

		double Vector::Magnitude() {

			double result = 0.0f;
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