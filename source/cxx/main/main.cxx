#include"../classes/machineLearning/regression/elasticNetLinearRegression/elasticNetLinearRegression.h"

int main(void){
    Matrix data("red_wine.txt");
    ElasticNetLinearRegression test(data,0.5,0,0.0,0.01);
    test.train(1.0E-16);
    test.printMae();
    return 0;
}