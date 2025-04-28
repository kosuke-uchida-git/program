#include"geneticLinearRegression.h"

GeneticLinearRegression::GeneticLinearRegression(Matrix data, double arg_missingRate, int seed):
    Regression(data, arg_missingRate, seed)
{
    bias=0.0;
    coefficient.row_(1);
    coefficient.column_(dimension);
    intermediate.row_(trainingDataNumber);
    intermediate.column_(1);
}

void GeneticLinearRegression::print(){
    Regression::print();
    std::cout<<"bias="<<bias<<std::endl;
    std::cout<<"coefficient="<<std::endl;
    coefficient.print();
    std::cout<<"intermediate="<<std::endl;
    intermediate.print();
}

void GeneticLinearRegression::train(double criterion){
    #ifdef VERBOSE
    int step=0;
    #endif

    while(1){
        double tmp_bias=bias;
        Matrix tmp_coefficient(coefficient);
        
        revise_intermediate();
        revise_bias();
        revise_coefficient();

        double difference=std::abs(bias-tmp_bias);
        double coefficient_difference=(coefficient-tmp_coefficient).maxNorm();
        if(coefficient_difference>difference)
            difference=coefficient_difference;
        if(difference<criterion)
            break;

        #ifdef VERBOSE
        step++;
        if(step%10000==0)
            //std::cout<<step<<":difference="<<difference<<std::endl;
            std::cout<<objectiveFunction(coefficient,bias)<<std::endl;
        #endif
    }
}

void GeneticLinearRegression::predict(){
    prediction=explanatory_missing*coefficient.transpose();
    for(int i=0;i<missingNumber;i++)
        prediction[i][0]+=bias;
}

double GeneticLinearRegression::objectiveFunction(Matrix arg_coefficient,double arg_bias){
    Matrix tmp(intermediate);
    tmp=objective_training-(arg_coefficient*explanatory_training.transpose()).transpose();
    for(int i=0;i<trainingDataNumber;i++){
        tmp[i][0]-=arg_bias;
    }
    return tmp.l2normSquare();
}

void GeneticLinearRegression::revise_intermediate(){
    intermediate=objective_training-(coefficient*explanatory_training.transpose()).transpose();
}

void GeneticLinearRegression::revise_bias(){
    double result=0.0;
    for(int n=0;n<trainingDataNumber;n++){
        result+=intermediate[n][0];
    }
    result/=trainingDataNumber;
    bias=result;
}

void GeneticLinearRegression::revise_coefficient(){
    for(int m=0;m<dimension;m++)
        revise_coefficient(m);
}

void GeneticLinearRegression::revise_coefficient(int dimension_index){
    double numerator=0.0, denominator=0.0;
    for(int n=0;n<trainingDataNumber;n++){
        numerator+=explanatory_training[n][dimension_index]*(intermediate[n][0]+coefficient[0][dimension_index]*explanatory_training[n][dimension_index]-bias);
        denominator+=explanatory_training[n][dimension_index]*explanatory_training[n][dimension_index];
    }
    coefficient[0][dimension_index]=numerator/denominator;
}