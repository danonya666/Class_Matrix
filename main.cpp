#include <iostream>
#include <fstream>
using namespace std;

class Matrix
{

private:
    int n_rows;
    int n_cols;
    int **ptr;

public:
    //Normal constructor of the Matrix
    Matrix(int n_rows, int n_cols):
        n_rows(n_rows),
        n_cols(n_cols)
        {
            //Error for negative n_rows / n_cols
            if(this->n_cols < 0 || this->n_rows < 0)
                throw "Error";

            //Memory allocation
            ptr = new int* [n_rows];
            for(int counter = 0; counter < n_rows; counter++)
                ptr[counter] = new int [n_cols];

            //Zeroing the data
            for(int i = 0; i < n_rows; i++)
            {
                for(int j = 0; j < n_cols; j++)
                {
                    this->ptr[i][j] = 0;
                }
            }
        }


        //Copying Constructor
        Matrix(Matrix const &other):
            n_rows(other.n_rows),
            n_cols(other.n_cols)
            {
                if(this != &other)
                {
                    //cout << "Matrix copy" << endl;
                    ptr = new int* [n_rows];
                    for(int counter = 0; counter < n_rows; counter++)
                        ptr[counter] = new int [n_cols];

                    for(int i = 0; i < n_rows; i++)
                    {
                        for(int j = 0; j < n_cols; j++)
                        {
                            ptr[i][j] = other.ptr[i][j];
                        }
                    }
                }
            }

            //Destructor
        ~Matrix()
        {
            //cout << "~Matrix";
            for(int counter = 0; counter < n_rows; counter++)
                delete [] ptr[counter];
            delete [] ptr;
        }

        //Function for filling the exact field of the Matrix
        //Could be done also with () operation, same result
        void FillMatrix(const int &row, const int &col, int value)
        {
            if(row > n_rows - 1 || row < 0 || col > n_cols - 1 || col < 0)
                throw "Error";
            this->ptr[row][col] = value;
        }

        //For getting the exact field
        //Could be done with (), same result
        int getPtr(int row, int col)
        {
            return this->ptr[row][col];
        }

        int getRows(){
            return this->n_rows;
        }

        int getCols() const {
            return this->n_cols;
        }

        //Below are the operators for arithmetics for Matrix type
        Matrix operator + (Matrix &m1)
        {
            if (this->getRows() != m1.getRows() || this->getCols() != m1.getCols())
                    throw 1;


            Matrix m3(this->getRows(), this->getCols());
            for(int i = 0; i < m3.getRows(); i++)
            {
                for(int j = 0; j < m3.getCols(); j++)
                {
                    m3.FillMatrix(i, j, m1.ptr[i][j] + this->ptr[i][j]);
                }
            }
            return m3;
        }


        Matrix operator - (Matrix &m1)
        {
            if (this->getRows() != m1.getRows() || this->getCols() != m1.getCols())
                    throw 1;

            Matrix m3(this->getRows(), this->getCols());
            for(int i = 0; i < m3.getRows(); i++)
            {
                for(int j = 0; j < m3.getCols(); j++)
                {
                    m3.FillMatrix(i, j, this->ptr[i][j] - m1.ptr[i][j]);
                }
            }
            return m3;
        }


        Matrix operator + (const int &m1)
        {
            Matrix m3(this->getRows(), this->getCols());
            for(int i = 0; i < m3.getRows(); i++)
            {
                for(int j = 0; j < m3.getCols(); j++)
                {
                    m3.FillMatrix(i, j, m1 + this->ptr[i][j]);
                }
            }
            return m3;
        }


        Matrix operator - (const int m1)
        {
            Matrix m3(this->getRows(), this->getCols());
            for(int i = 0; i < m3.getRows(); i++)
            {
                for(int j = 0; j < m3.getCols(); j++)
                {
                    m3.FillMatrix(i, j, -m1 + this->ptr[i][j]);
                }
            }
            return m3;
        }


        Matrix operator * (const int &m1)
        {
            Matrix m3(this->getRows(), this->getCols());
            for(int i = 0; i < m3.getRows(); i++)
            {
                for(int j = 0; j < m3.getCols(); j++)
                {
                    m3.FillMatrix(i, j, m1 * this->ptr[i][j]);
                }
            }
            return m3;
        }


        Matrix operator * (Matrix &m1)
        {
            if (this->getRows() != m1.getRows() || this->getCols() != m1.getCols())
                    throw 1;

            Matrix m3(this->getRows(), this->getCols());
            for(int i = 0; i < m3.getRows(); i++)
            {
                for(int j = 0; j < m3.getCols(); j++)
                {
                    m3.ptr[i][j] = m1.ptr[i][j] * this->ptr[i][j];
                }
            }
            return m3;
        }

        int& operator()(const int row, const int col)
        {
            return ptr[row][col];
        }

        Matrix& operator += (Matrix &m1)
        {
            if (this->getRows() != m1.getRows() || this->getCols() != m1.getCols())
                    throw 1;

            for(int i = 0; i < this->getRows(); i++)
            {
                for(int j = 0; j < this->getCols(); j++)
                {
                    this->ptr[i][j] += m1.ptr[i][j];
                }
            }
            return *this;
        }


        Matrix& operator -= (Matrix &m1)
        {
            if (this->getRows() != m1.getRows() || this->getCols() != m1.getCols())
                    throw 1;

            for(int i = 0; i < this->getRows(); i++)
            {
                for(int j = 0; j < this->getCols(); j++)
                {
                    this->ptr[i][j] -= m1.ptr[i][j];
                }
            }
            return *this;
        }


        Matrix& operator *= (int m1)
        {
            for(int i = 0; i < this->getRows(); i++)
            {
                for(int j = 0; j < this->getCols(); j++)
                {
                    this->ptr[i][j] *= m1;
                }
            }
            return *this;
        }


        Matrix& operator *= (Matrix &m1)
        {
            if (this->getRows() != m1.getRows() || this->getCols() != m1.getCols())
                    throw 1;

            for(int i = 0; i < this->getRows(); i++)
            {
                for(int j = 0; j < this->getCols(); j++)
                {
                    this->ptr[i][j] *= m1.ptr[i][j];
                }
            }
            return *this;
        }


        Matrix& operator += (int m1)
        {
            for(int i = 0; i < this->getRows(); i++)
            {
                for(int j = 0; j < this->getCols(); j++)
                {
                    this->ptr[i][j] += m1;
                }
            }
            return *this;
        }


        Matrix& operator -= (int m1)
        {
            for(int i = 0; i < this->getRows(); i++)
            {
                for(int j = 0; j < this->getCols(); j++)
                {
                    this->ptr[i][j] -= m1;
                }
            }
            return *this;
        }

        //transpose of the matrix

        Matrix T()
        {
            Matrix m2(this->getCols(), this->getRows());
            for(int i = 0; i < this->getRows(); i++)
            {
                for(int j = 0; j < this->getCols(); j++)
                {
                    m2.ptr[j][i] = this->ptr[i][j];
                }
            }

            for (int i = 0; i < this->n_rows; i++)
            delete (this->ptr[i]);
        delete (this->ptr);
        this->n_rows = m2.getRows();
        this->n_cols = m2.getCols();

        ptr = new int* [this->n_rows];
            for(int counter = 0; counter < n_rows; counter++)
                ptr[counter] = new int [this->n_cols];

            for(int i = 0; i < this->getRows(); i++)
            {
                for(int j = 0; j < this->getCols(); j++)
                {
                    this->ptr[i][j] = m2.ptr[i][j];
                }
            }
            return *this;
        }

        Matrix operator = (Matrix m1)
        {
            int c, l;
            c = m1.getCols();
            l = m1.getRows();
            Matrix result(l, c);

    if (this->ptr != m1.ptr)
    {
        for (int i = 0; i < l; i++)
            for (int j = 0; j < c; j++)
                {
                    result.ptr[i][j] = m1.ptr[i][j];
                }

        for (int i = 0; i < this->n_rows; i++)
            delete (this->ptr[i]);
        delete (this->ptr);
        this->n_rows = l;
        this->n_cols = c;
        ptr = new int* [this->n_rows];
            for(int counter = 0; counter < n_rows; counter++)
                ptr[counter] = new int [this->n_cols];
        for(int i = 0; i < this->getRows(); i++)
            for(int j = 0; j < this->getCols(); j++)
                this->ptr[i][j] = result.ptr[i][j];
         for (int i = 0; i < l; i++)
        return *this;
    }
    else
        return m1;
        }

        // Multiplying rows to columns
        Matrix dot(Matrix &m1)
        {
            if (this->n_cols != m1.n_rows)
                    throw "Error";

            Matrix m3(this->getRows(), m1.getCols());
            for(int q = 0; q < m3.getRows(); q++)
            {
                for(int k = 0; k < m3.getCols(); k++)
                {
                    m3.ptr[q][k] = 0;
                    {
                        for(int i = 0; i < this->getCols(); i++)
                        {
                            m3.ptr[q][k] += this->ptr[q][i] * m1.ptr[i][k];
                        }
                    }
                }
            }
            return m3;
        }

        friend ostream& operator << (ostream &fout, Matrix& m1)
        {
            fout << endl;
            fout << "PRINTING MATRIX " << m1.getRows() << "x" << m1.getCols() << endl;
            for(int i = 0; i < 3 * m1.getCols(); i++)
            {
                fout << "_";
            }
            fout << endl << endl;
            for(int i = 0; i < m1.getRows(); i++)
            {
                for(int j = 0; j < m1.getCols(); j++)
                    fout << m1.getPtr(i, j) << " ";
                fout << endl;
            }

            for(int i = 0; i < 3 * m1.getCols(); i++)
            {
                fout << "_";
            }

            fout << "\nMATRIX PRINTED\n\n";

            return fout;
        }

        friend ifstream& operator >> (ifstream& fin, Matrix& m1)
        {
            for(int i = 0; i < m1.getRows(); i++)
                {
                for(int j = 0; j < m1.getCols(); j++)
                    {
                        fin >> m1.ptr[i][j];
                    }
                }
            return fin;
        }


};

int main()
{
    //Some tests
    Matrix matrix1(2, 3);
    Matrix matrix2(3, 2);
    Matrix matrix3(2, 2);
    //Matrix matrix4(-1, -3);
    //Negative n_rows n_cols test up there

    Matrix result(1, 1);
    ifstream fin;
    fin.open("input.txt");
    fin >> matrix1 >> matrix2 >> matrix3;

    cout << "\n\nM1" << matrix1 << endl;

    result = matrix1.dot(matrix2);
    cout << "M1 dot M2" << result;

    result = matrix1.T();
    cout << "\n\nTRANSPONDED MATRIX " << result;

    result = matrix1 + matrix1;
    cout << "M1 + M1" << result;

    result = matrix1 - matrix1;
    cout << "M1 - M1" << result;

    result = matrix1 * 5;
    cout << "M1 * 5" <<result;

    result = matrix1 + 5;
    cout << "M1 + 5" << result;


    return 0;
}
