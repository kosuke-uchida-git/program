#include"../../functions/functions.h"

#ifndef VECTOR
#define VECTOR

class Vector{
    protected:
        bool rowColumn;//row vector : rowColumn=1, column vector : rowColumn=0
        int size;
        double *element;
    
    public:
        //constructors
        Vector();
        Vector(bool arg_rowColumn, int arg_size, double initial);
        Vector(const Vector &arg_vector);

        //destructor
        ~Vector();

        //getters and setters
        bool rowColumn_() const;
        bool& rowColumn_();
        int size_() const;
        void size_(int arg_size);
        double& operator[](int index) const;

        //substitute
        void operator=(const Vector& rhs);

        //print
        void print() const;

        //calculate
        void operator+=(const Vector& rhs);
        Vector operator+(const Vector& rhs) const;
        void operator-=(const Vector& rhs);
        Vector operator-(const Vector& rhs) const;
        Vector operator*(const Vector& rhs) const;
};

#endif