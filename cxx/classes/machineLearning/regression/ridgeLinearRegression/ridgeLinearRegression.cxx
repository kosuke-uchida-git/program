#include"ridgeLinearRegression.h"

RidgeLinearRegression::RidgeLinearRegression(Matrix data, double arg_missingRate, int seed, double arg_ridgeRegularizer):
    LinearRegression(data, arg_missingRate, seed)
{
    ridgeRegularizer=arg_ridgeRegularizer;
}

double RidgeLinearRegression::ridgeRegularizer_() const{
    return ridgeRegularizer;
}

double& RidgeLinearRegression::ridgeRegularizer_(){
    return ridgeRegularizer;
}

void RidgeLinearRegression::revise_coefficient(int dimension_index){
    //same as the base class
    double numerator=0.0, denominator=0.0;
    for(int n=0;n<trainingDataNumber;n++){
        numerator+=explanatory_training[n][dimension_index]*(intermediate[n][0]+coefficient[0][dimension_index]*explanatory_training[n][dimension_index]-bias);
        denominator+=explanatory_training[n][dimension_index]*explanatory_training[n][dimension_index];
    }
    //ridge regularization
    denominator+=ridgeRegularizer;
    //same as the base class
    coefficient[0][dimension_index]=numerator/denominator;
}