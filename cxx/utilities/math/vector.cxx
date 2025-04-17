#include"vector.h"

Vector::Vector():
    rowColumn(1),
    size(0),
    element(nullptr){}

Vector::Vector(bool arg_rowColumn, int arg_size, double initial):
    rowColumn(arg_rowColumn),
    size(arg_size)
{
    if(size<0){
        std::cout<<"Error! Vector::Vector(bool arg_rowColumn, int arg_size)"<<std::endl;
        exit(0);
    }
    if(size > 0){
        element=new double[size];
        for(int i=0;i<size;i++)
            element[i]=initial;
    } else {
        element = nullptr;
    }
}

Vector::Vector(const Vector &arg_vector){
    rowColumn=arg_vector.rowColumn_();
    size=arg_vector.size_();
    if(size > 0){
        element = new double[size];
        for(int i = 0; i < size; i++)
            element[i] = arg_vector[i];
    } else {
        element = nullptr;
    }
}

Vector::~Vector(){
    if(element != nullptr){
        delete[] element;
        element = nullptr;
    }
}

bool Vector::rowColumn_() const{
    return rowColumn;
}
void Vector::rowColumn_(bool arg_rowColumn){
    rowColumn=arg_rowColumn;
}

int Vector::size_() const{
    return size;
}

void Vector::size_(int arg_size){
    if(arg_size<0){
        std::cout<<"Error! void Vector::size_(int arg_size)"<<std::endl;
        exit(0);
    }

    if(size==arg_size)
        return;
    
    double *tmp_element=new double[size];
    for(int i=0;i<size;i++)
        tmp_element[i]=element[i];
    delete[] element;
    element=new double[arg_size];
    for(int i=0;i<arg_size;i++){
        if(i<size)
            element[i]=tmp_element[i];
        else
            element[i]=0.0;
    }
    delete[] tmp_element;
    size=arg_size;
}

double& Vector::operator[](int index) const{
    return element[index];
}

void Vector::operator=(const Vector& rhs) {
    if (this == &rhs) return;

    if (element != nullptr) {
        delete[] element;
        element = nullptr;
    }

    rowColumn = rhs.rowColumn_();
    size = rhs.size_();

    if (size > 0) {
        element = new double[size];
        for (int i = 0; i < size; i++) {
            element[i] = rhs.element[i];
        }
    } else {
        element = nullptr;
    }
}

void Vector::print() const{
    for(int i=0;i<size-1;i++)
        std::cout<<element[i]<<",";
    std::cout<<element[size-1];
}

void Vector::operator+=(const Vector& rhs)  {
    if(rowColumn!=rhs.rowColumn_() || size!=rhs.size_()){
        std::cout<<"Error! void Vector::operator+=(const Vector& rhs)"<<std::endl;
        exit(0);
    }
    for(int i=0;i<size;i++){
        element[i]+=rhs[i];
    }
}

Vector Vector::operator+(const Vector& rhs) const{
    if(rowColumn!=rhs.rowColumn_() || size!=rhs.size_()){
        std::cout<<"Error! Vector operator+(const Vector& rhs) const"<<std::endl;
        exit(0);
    }

    Vector result(*this);
    result+=rhs;
    return result;
}

void Vector::operator-=(const Vector& rhs) {
    if(rowColumn!=rhs.rowColumn_() || size!=rhs.size_()){
        std::cout<<"Error! void Vector::operator-=(const Vector& rhs)"<<std::endl;
        exit(0);
    }
    for(int i=0;i<size;i++){
        element[i]-=rhs[i];
    }
}

Vector Vector::operator-(const Vector& rhs) const{
    if(rowColumn!=rhs.rowColumn_() || size!=rhs.size_()){
        std::cout<<"Error! Vector operator-(const Vector& rhs) const"<<std::endl;
        exit(0);
    }

    Vector result(*this);
    result-=rhs;
    return result;
}

Vector Vector::operator*(const Vector& rhs) const{
    if(rowColumn==1 && rhs.rowColumn_()==0 && size==rhs.size_()){
        Vector result(1,1,0.0);
        for(int i=0;i<size;i++)
            result[0]+=element[i]*rhs[i];
        return result;
    }
    else if(size==1){
        Vector result(rhs);
        for(int i=0;i<rhs.size_();i++){
            result[i]*=element[0];
        }
        return result;
    }
    else{
        std::cout<<"Error! Vector operator*(const Vector& rhs) const"<<std::endl;
        exit(0);
    }
}