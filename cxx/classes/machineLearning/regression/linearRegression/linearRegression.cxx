#include"linearRegression.h"

LinearRegression::LinearRegression(Matrix data, double arg_missingRate, int seed):
    Regression(data, arg_missingRate, seed)
{
    bias=0.0;
    coefficient.row_(1);
    coefficient.column_(dimension);
    intermediate.row_(trainingDataNumber);
    intermediate.column_(1);
}

void LinearRegression::print(){
    Regression::print();
    std::cout<<"bias="<<bias<<std::endl;
    std::cout<<"coefficient="<<std::endl;
    coefficient.print();
    std::cout<<"intermediate="<<std::endl;
    intermediate.print();
}

void LinearRegression::train(double criterion){
    #ifdef VERBOSE
    int step=0;
    #endif

    while(1){
        double tmp_bias=bias;
        Matrix tmp_coefficient(coefficient);
        revise_intermediate();
        revise_bias();
        revise_coefficient();
        double difference=std::abs(bias-tmp_bias)+(coefficient-tmp_coefficient).maxNorm();
        if(difference<criterion)
            break;

        #ifdef VERBOSE
        step++;
        if(step%10000==0)
            std::cout<<step<<":difference="<<difference<<std::endl;
        #endif
    }
}

void LinearRegression::predict(){
    prediction=explanatory_missing*coefficient.transpose();
    for(int i=0;i<missingNumber;i++)
        prediction[i][0]+=bias;
}

void LinearRegression::revise_intermediate(){
    intermediate=objective_training-(coefficient*explanatory_training.transpose()).transpose();
}

void LinearRegression::revise_bias(){
    double result=0.0;
    for(int n=0;n<trainingDataNumber;n++){
        result+=intermediate[n][0];
    }
    result/=trainingDataNumber;
    bias=result;
}

void LinearRegression::revise_coefficient(){
    for(int m=0;m<dimension;m++)
        revise_coefficient(m);
}

void LinearRegression::revise_coefficient(int dimension_index){
    double numerator=0.0, denominator=0.0;
    for(int n=0;n<trainingDataNumber;n++){
        numerator+=explanatory_training[n][dimension_index]*(intermediate[n][0]+coefficient[0][dimension_index]*explanatory_training[n][dimension_index]-bias);
        denominator+=explanatory_training[n][dimension_index]*explanatory_training[n][dimension_index];
    }
    coefficient[0][dimension_index]=numerator/denominator;
}