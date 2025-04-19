#include"../classes/machineLearning/regression/lassoLinearRegression/lassoLinearRegression.h"

int main(void){
    Matrix m("file.txt");

    LassoLinearRegression r(m,0.5,2,0.01);
    r.train(1.0E-15);
    //r.print();
    std::cout<<"mae="<<r.mae()<<std::endl;
    return 0;
}