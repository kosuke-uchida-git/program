#include"../classes/machineLearning/regression/elasticNetLinearRegression/elasticNetLinearRegression.h"

int main(void){
    Matrix data("red_wine.txt");
    LinearRegression test(data,0.5,0);
    test.train(1.0E-16);
    test.printMae();
    return 0;
}