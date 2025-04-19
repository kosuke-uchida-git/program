#include"linearRegression.h"

LinearRegression::LinearRegression(Matrix data){
    bias=0.0;
    dataNumber=data.row_();
    dimension=data.column_()-1;
    coefficient.row_(1);
    coefficient.column_(dimension);
    intermediate.row_(dataNumber);
    intermediate.column_(1);
    explanatory.row_(dimension);
    explanatory.column_(dataNumber);
    objective.row_(dataNumber);
    objective.column_(1);
    for(int i=0;i<dataNumber;i++){
        for(int j=0;j<dimension;j++){
            explanatory[j][i]=data[i][j];
        }
        objective[i][0]=data[i][data.column_()-1];
    }
}

void LinearRegression::print(){
    std::cout<<"number of data:"<<dataNumber<<std::endl;
    std::cout<<"dimension     :"<<dimension<<std::endl;
    std::cout<<"explanatory variable:"<<std::endl;
    explanatory.print();
    std::cout<<"objective variable:"<<std::endl;
    objective.print();
    std::cout<<"coefficient:"<<std::endl;
    coefficient.print();
    std::cout<<"bias:"<<bias<<std::endl;
    std::cout<<"intermediate:"<<std::endl;
    intermediate.print();
}

void LinearRegression::train(double criterion){
    while(1){
        double tmp_bias=bias;
        Matrix tmp_coefficient(coefficient);
        revise_intermediate();
        revise_bias();
        revise_coefficient();
        double difference=std::abs(bias-tmp_bias)+(coefficient-tmp_coefficient).maxNorm();
        //std::cout<<"difference="<<difference<<std::endl;
        if(difference<criterion)
            break;
    }
}

void LinearRegression::revise_intermediate(){
    intermediate=objective-(coefficient*explanatory).transpose();
}

void LinearRegression::revise_bias(){
    double result=0.0;
    for(int n=0;n<dataNumber;n++)
        result+=intermediate[n][0];
    result/=dataNumber;
    bias=result;
}

void LinearRegression::revise_coefficient(){
    for(int m=0;m<dimension;m++)
        revise_coefficient(m);
}

void LinearRegression::revise_coefficient(int dimension_index){
    double numerator=0.0, denominator=0.0;
    for(int n=0;n<dataNumber;n++){
        numerator+=explanatory[dimension_index][n]*(intermediate[n][0]+coefficient[0][dimension_index]*explanatory[dimension_index][n]-bias);
        denominator+=explanatory[dimension_index][n]*explanatory[dimension_index][n];
    }
    coefficient[0][dimension_index]=numerator/denominator;
}