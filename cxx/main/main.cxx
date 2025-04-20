#include"../classes/machineLearning/regression/elasticNetLinearRegression/elasticNetLinearRegression.h"

int main(void){
    Matrix m("file.txt");

    ElasticNetLinearRegression r(m,0.5,2,100,100);
    r.train(1.0E-15);
    //r.print();
    std::cout<<"mae="<<r.mae()<<std::endl;
    return 0;
}