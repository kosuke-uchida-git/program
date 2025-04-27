#include"elasticNetLinearRegression.h"

ElasticNetLinearRegression::ElasticNetLinearRegression(Matrix data, double arg_missingRate, int seed, double arg_lassoRegularizer, double arg_ridgeRegularizer):
    Regression(data, arg_missingRate, seed),
    LinearRegression(data, arg_missingRate, seed),
    LassoLinearRegression(data, arg_missingRate, seed, arg_lassoRegularizer),
    RidgeLinearRegression(data, arg_missingRate, seed, arg_ridgeRegularizer){}

void ElasticNetLinearRegression::revise_coefficient(int dimension_index){
    //same as the LinearRegression class
    double numerator=0.0, denominator=0.0;
    for(int n=0;n<trainingDataNumber;n++){
        numerator+=explanatory_training[n][dimension_index]*(intermediate[n][0]+coefficient[0][dimension_index]*explanatory_training[n][dimension_index]-bias);
        denominator+=explanatory_training[n][dimension_index]*explanatory_training[n][dimension_index];
    }
    //lasso regularization
    if(std::abs(numerator)>lassoRegularizer)
        numerator-=lassoRegularizer*sign(numerator);
    else
        numerator=0.0;
    //ridge regularization
    denominator+=ridgeRegularizer;
    //same as the LinearRegression class
    coefficient[0][dimension_index]=numerator/denominator;
}