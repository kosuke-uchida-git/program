#include"matrix.h"

Matrix::Matrix():
    row(0),
    column(0),
    element(nullptr){}

Matrix::Matrix(int arg_row, int arg_column, int initial):
    row(arg_row),
    column(arg_column)
{
    if(row<=0 || column<=0){
        std::cout<<"Error! Matrix::Matrix(int arg_row, int arg_column, int initial)"<<std::endl;
        exit(0);
    }
    element=new Vector[row];
    for(int i=0;i<row;i++){
        element[i].size_(column);
    }
    for(int i=0;i<row;i++)
        for(int j=0;j<column;j++)
            element[i][j]=initial;
}

Matrix::Matrix(const Matrix &arg_matrix){
    row=arg_matrix.row_();
    column=arg_matrix.column_();
    if(row>0){
        element = new Vector[row];
        for(int i=0;i<row;i++)
            element[i]=arg_matrix[i];
    }
    else
        element=nullptr;
}

Matrix::Matrix(std::string filename){
    //read file
    filename="file/"+filename;
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        std::cout<<"Error1! Matrix:: Matrix(std::string filename)"<<std::endl;
        exit(0);
    }
    std::string line;
    int rowCount = 0;
    int columnCount = 0;
    List valueList(0);

    while (std::getline(ifs, line)) {
        std::istringstream iss(line);
        double value;
        int tmpColumnCount = 0;

        while (iss >> value) {
            tmpColumnCount++;
            valueList.addTail(value);
        }

        if (tmpColumnCount > 0) {
            rowCount++;
            if (tmpColumnCount > columnCount) {
                columnCount = tmpColumnCount;
            }
        }
    }
    
    ifs.close();

    //edit Matrix
    row=rowCount;
    column=columnCount;
    if(row<=0 || column<=0){
        std::cout<<"Error2! Matrix::Matrix(std::string filename)"<<std::endl;
        exit(0);
    }
    element=new Vector[row];
    for(int i=0;i<row;i++)
        element[i].size_(column);

    SearchList searchList(valueList);
    double nextElement;
    searchList.next();
    for(int i=0;i<row;i++)
        for(int j=0;j<column;j++){
            searchList.next(nextElement);
            element[i][j]=nextElement;
    }
}

Matrix::~Matrix(){
    if(element != nullptr){
        delete[] element;
        element = nullptr;
    }
}

int Matrix::row_() const{
    return row;
}

void Matrix::row_(int arg_row){
    if(arg_row<=0){
        std::cout<<"Error! void Matrix::row_(int arg_row)"<<std::endl;
        exit(0);
    }
    if(row==arg_row)
        return;
    
    row=arg_row;
    if(element != nullptr){
        delete[] element;
        element = nullptr;
    }
    element=new Vector[row];
    Vector dummy(1,column,0.0);
    for(int i=0;i<row;i++)
        element[i]=dummy;
}

int Matrix::column_() const{
    return column;
}

void Matrix::column_(int arg_column){
    if(arg_column<=0){
        std::cout<<"Error! void Matrix::column_(int arg_column)"<<std::endl;
        exit(0);
    }
    if(column==arg_column)
        return;
    
    column=arg_column;
    if(element != nullptr){
        delete[] element;
        element = nullptr;
    }
    element=new Vector[row];
    Vector dummy(1,column,0.0);
    for(int i=0;i<row;i++)
        element[i]=dummy;
}

Vector& Matrix::operator[](int arg_row) const{
    if(arg_row<0 || arg_row>=row){
        std::cout<<"Error! Vector& Matrix::operator[](int arg_row) const"<<std::endl;
        exit(0);
    }
    return element[arg_row];
}

Vector Matrix::columnVector_(int arg_column) const{
    if(arg_column<0 || arg_column>=column){
        std::cout<<"Error! Vector Matrix::columnVector_(int arg_column) const"<<std::endl;
        exit(0);
    }
    Vector result(0,row,0);
    for(int i=0;i<result.size_();i++)
        result[i]=element[i][arg_column];
    return result;
}

void Matrix::operator=(const Matrix& rhs) {
    if (this == &rhs) return;

    if (element != nullptr) {
        delete[] element;
        element = nullptr;
    }

    row = rhs.row_();
    column = rhs.column_();

    if (row*column > 0) {
        element=new Vector[row];
        for (int i = 0; i < row; i++) {
            element[i] = rhs.element[i];
        }
    } else {
        element = nullptr;
    }
}

Matrix Matrix::number(double arg_double){
    Matrix result(1,1,arg_double);
    return result;
}

void Matrix::print() const{
    std::cout<<"<"<<row<<"*"<<column<<">"<<std::endl;
    std::cout<<"(";
    for(int i=0;i<row-1;i++){
        element[i].print();
        std::cout<<std::endl;
    }
    element[row-1].print();
    std::cout<<")"<<std::endl;
}

void Matrix::output(std::string filename){
    std::ofstream ofs(filename);
    if (!ofs) {
        std::cout<<"void Matrix::output(std::string filename)"<<std::endl;
        exit(0);
    }
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            ofs<<element[i][j];
            if(j<column-1){
                ofs<<" ";
            }
        }
        if(i<row-1){
            ofs<<"\n";
        }
    }
    ofs.close();
}

Matrix Matrix::transpose(){
    Matrix result(column,row,0.0);
    for(int i=0;i<row;i++)
        for(int j=0;j<column;j++)
            result[j][i]=element[i][j];
    return result;
}

void Matrix::operator+=(const Matrix& rhs)  {
    if(row!=rhs.row_() || column!=rhs.column_()){
        std::cout<<"Error! void Matrix::operator+=(const Matrix& rhs)"<<std::endl;
        exit(0);
    }
    for(int i=0;i<row;i++){
        element[i]+=rhs[i];
    }
}

Matrix Matrix::operator+(const Matrix& rhs)  {
    if(row!=rhs.row_() || column!=rhs.column_()){
        std::cout<<"Error! void Matrix::operator+(const Matrix& rhs)"<<std::endl;
        exit(0);
    }
    Matrix result(*this);
    result+=rhs;
    return result;
}

void Matrix::operator-=(const Matrix& rhs)  {
    if(row!=rhs.row_() || column!=rhs.column_()){
        std::cout<<"Error! void Matrix::operator-=(const Matrix& rhs)"<<std::endl;
        exit(0);
    }
    for(int i=0;i<row;i++){
        element[i]-=rhs[i];
    }
}

Matrix Matrix::operator-(const Matrix& rhs)  {
    if(row!=rhs.row_() || column!=rhs.column_()){
        std::cout<<"Error! void Matrix::operator-(const Matrix& rhs)"<<std::endl;
        exit(0);
    }
    Matrix result(*this);
    result-=rhs;
    return result;
}

void Matrix::operator*=(const Matrix& rhs){
    (*this)=(*this)*rhs;
}

Matrix Matrix::operator*(const Matrix& rhs)  {
    if(row==1 && column==1){
        Vector tmp_vector(1,1,element[0][0]);
        Matrix result(rhs);
        for(int i=0;i<result.row_();i++)
            result[i]=tmp_vector*result[i];
        return result;
    }
    else if(column==rhs.row_()){
        Matrix result(row,rhs.column_(),0);
        for(int i=0;i<result.row_();i++)
            for(int j=0;j<result.column_();j++){
                result[i][j]=(element[i]*rhs.columnVector_(j))[0];
        }
        return result;
    }
    else{
        std::cout<<"Error! Matrix Matrix::operator*(const Matrix& rhs)"<<std::endl;
        exit(0);
    }
}

double Matrix::maxNorm(){
    if(row<1 || column<1){
        std::cout<<"Error! double Matrix::maxNorm()"<<std::endl;
        exit(0);
    }
    double max=0.0;
    for(int i=0;i<row;i++)
        for(int j=0;j<column;j++)
            if(std::abs(element[i][j])>max)
                max=std::abs(element[i][j]);
    return max;
}

double Matrix::l1norm(){
    double result=0.0;
    for(int i=0;i<row;i++)
        for(int j=0;j<column;j++)
            result+=std::abs(element[i][j]);
    return result;
}