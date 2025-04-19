#include"utilities/machineLearning/linearRegression.h"

int main(void){
    Matrix data("file.txt");
    LinearRegression test(data);
    test.train(1.0E-14);
    test.print();
    return 0;
}