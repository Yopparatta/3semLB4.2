#include <iostream>
using namespace std;

class MyArray
{
	friend ostream& operator<<(ostream& os, MyArray arr);
	friend MyArray operator+(MyArray arr2);
	friend MyArray operator -(MyArray arr2);
	friend MyArray operator *(MyArray arr2);
private:
	int rowSize;
	int colSize;
	int** arr;
public:
	void arrayInput()
	{
		cout << "Заполните ячейки массива числами\n";
		for (int j = 0; j < colSize; j++)
		{
			for (int i = 0; i < rowSize; i++)
			{
				cin >> arr[j][i];
			}
		}
	}

	MyArray(int col, int row)
	{
		arr = new int*[col];
		for (int i = 0; i < col; i++)
		{
			arr[i] = new int [row];
		}
		colSize = col;
		rowSize = row;
	}

	MyArray()
	{
		arr = nullptr;
		colSize = 0;
		rowSize = 0;
	}

	int getAccess(int col, int row)
	{
		if (col > colSize || row > rowSize || col < 0 || row < 0)
		{
			cout << "Неверный индекс массива\n";
			return -1;
		}
		return arr[col][row];
	}

	void getLink(int col, int row)
	{
		int* p = &arr[col][row];
		cout << p << endl;
	}

	void colsRows()
	{
		cout << rowSize << " Строк, " << colSize << " столбцов\n";
	}

	void changeSize(int col, int row)
	{
		arr = new int*[col];
		for (int i = 0; i < col; i++)
		{
			arr[i] = new int [row];
		}
		arrayInput();
	}

	double doDeterminant()
	{
		if (this->colSize == 1)
		{
			return this->arr[0][0];
		}
		if (this->colSize == 2)
		{
			return this->arr[0][0] * this->arr[1][1] - this->arr[0][1] * this->arr[1][0];
		}
	}

	double minor(int col, int row)
	{
		MyArray minorMatrix(colSize - 1, rowSize - 1);
		for (int a = 0, i = 0; a < colSize; a++)
		{
			if (a == col) continue;
			for (int b = 0, j = 0; b < rowSize; b++)
			{
				if (b == row) continue;
					minorMatrix.arr[i++][j++] = this->arr[a][b];
			}
		}
		return minorMatrix.doDeterminant();
	}


	void inverseMatrix()
	{
		double determinant = this->doDeterminant();
		MyArray matrix(colSize, rowSize);

		for (int i = 0; i < colSize; i++)
		{
			for (int j = 0; j < rowSize; j++)
			{
				matrix.arr[i][j] = this->minor(i, j);
			}
		}
		for (int i = 0; i < colSize; i++)
		{
			for (int j = 0; j < rowSize; j++)
			{
				if ((i + j) % 2 != 0)
				{
					matrix.arr[i][j] *= -1;
				}
			}
		}
		for (int i = 0; i < matrix.colSize; i++)
		{
			for (int j = 0; j < matrix.rowSize; j++)
			{
				matrix.arr[i][j] /= determinant;
				cout << matrix.arr[i][j] << " ";
			}
			cout << endl;
		}
	}

	MyArray operator+(MyArray arr2)
	{
		int maxcol;
		int maxrow;
		if (this->colSize >= arr2.colSize) maxcol = this->colSize;
		else maxcol = arr2.colSize;
		if (this->rowSize >= arr2.rowSize) maxrow = this->rowSize;
		else maxrow = arr2.rowSize;
		MyArray arr(maxcol, maxrow);
		MyArray zeroarr(0, 0);
		try
		{
			for (int i = 0; i < maxcol; i++)
			{
				for (int j = 0; j < maxrow; j++)
				{
					arr.arr[i][j] = this->arr[i][j] + arr2.arr[i][j];
				}
			}
			return arr;
		}
		catch (exception e)
		{
			cout << "Невозможно выполнить операцию сложения\n";
			return zeroarr;
		}
	}

	MyArray operator -(MyArray arr2)
	{
		int maxcol;
		int maxrow;
		if (this->colSize >= arr2.colSize) maxcol = this->colSize;
		else maxcol = arr2.colSize;
		if (this->rowSize >= arr2.rowSize) maxrow = this->rowSize;
		else maxrow = arr2.rowSize;
		MyArray arr(maxcol, maxrow);
		MyArray zeroarr(0, 0);
		try
		{
			for (int i = 0; i < maxcol; i++)
			{
				for (int j = 0; j < maxrow; j++)
				{
					arr.arr[i][j] = this->arr[i][j] - arr2.arr[i][j];
				}
			}
			return arr;
		}
		catch (exception e)
		{
			cout << "Невозможно выполнить операцию сложения\n";
			return zeroarr;
		}
	}

	MyArray operator *(MyArray arr2)
	{
		MyArray arr(this->colSize, arr2.rowSize);
		for (int i = 0; i < colSize; i++)
		{
			for (int j = 0; j < rowSize; j++)
			{
				arr.arr[i][j] = 0;
			}
		}
		MyArray zeroarr(0, 0);
		if (this->rowSize == arr2.colSize)
		{
			for (int i = 0; i < arr.colSize; i++)
			{
				for (int j = 0; j < arr.rowSize; j++)
				{
					for (int k = 0; k < this->rowSize; k++)
					{
						arr.arr[i][j] += this->arr[i][k] * arr2.arr[k][j];
					}
				}
			}
			return arr;
		}
		else
		{
			cout << "Невозможно выполнить операцию умножения\n";
			return zeroarr;
		}
	}
};

ostream& operator<<(ostream& os, MyArray arr)
{
	for (int i = 0; i < arr.colSize; i++)
	{
		for (int j = 0; j < arr.rowSize; j++)
		{
			os << arr.arr[i][j] << " ";
		}
		os << endl;
	}
	return os;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Введите размер матрицы\n";
	int r, c;
	cin >> c >> r;
	MyArray matrix1(c, r);
	matrix1.arrayInput();
	cout << "Введите размер второй матрицы\n";
	cin >> c >> r;
	MyArray matrix2(c, r);
	matrix2.arrayInput();
	cout << endl;
	matrix1.getLink(0, 0);
	cout << matrix1 << endl;
	cout << matrix2 << endl;
	cout << matrix1 * matrix2 << endl;
	matrix1.inverseMatrix();
}
