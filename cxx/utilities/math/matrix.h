#include<fstream>
#include <sstream>
#include"vector.h"
#include"../list/searchList.h"

class Matrix{
    protected:
        int row;
        int column;
        Vector *element;
    public:
        //constructors
        Matrix();
        Matrix(int arg_row, int arg_column, int initial);
        Matrix(const Matrix &arg_matrix);
        Matrix(std::string filename);//read file

        //destructor
        ~Matrix();

        //getters and setters
        int row_() const;
        void row_(int arg_row);
        int column_() const;
        void column_(int arg_column);
        Vector& operator[](int arg_row) const;//get a row vector
        Vector columnVector_(int arg_column) const;//get a column vector

        //substitute
        void operator=(const Matrix& rhs);

        //convert double to Matrix
        static Matrix number(double arg_double);

        //print
        void print() const;

        //output file
        void output(std::string filename);

        //calculate
        Matrix transpose();
        void operator+=(const Matrix& rhs);
        Matrix operator+(const Matrix& rhs);
        void operator-=(const Matrix& rhs);
        Matrix operator-(const Matrix& rhs);
        void operator*=(const Matrix& rhs);
        Matrix operator*(const Matrix& rhs);
};