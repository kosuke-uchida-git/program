#include"lassoLinearRegression.h"

LassoLinearRegression::LassoLinearRegression(Matrix data, double arg_missingRate, int seed, double arg_lassoRegularizer):
    LinearRegression(data, arg_missingRate, seed)
{
    lassoRegularizer=arg_lassoRegularizer;
}

double LassoLinearRegression::lassoRegularizer_() const{
    return lassoRegularizer;
}

double& LassoLinearRegression::lassoRegularizer_(){
    return lassoRegularizer;
}

void LassoLinearRegression::revise_coefficient(int dimension_index){
    //same as the base class
    double numerator=0.0, denominator=0.0;
    for(int n=0;n<trainingDataNumber;n++){
        numerator+=explanatory_training[n][dimension_index]*(intermediate[n][0]+coefficient[0][dimension_index]*explanatory_training[n][dimension_index]-bias);
        denominator+=explanatory_training[n][dimension_index]*explanatory_training[n][dimension_index];
    }
    //lasso regularization
    if(std::abs(numerator)>lassoRegularizer)
        numerator-=lassoRegularizer*sign(numerator);
    else
        numerator=0;
    //same as the base class
    coefficient[0][dimension_index]=numerator/denominator;
}