#include"regression.h"

Regression::Regression(Matrix data, double arg_missingRate, int seed){
    dataNumber=data.row_();
    dimension=data.column_()-1;
    missingRate=arg_missingRate;
    missingNumber=(int)(missingRate*dataNumber);
    trainingDataNumber=dataNumber-missingNumber;
    explanatory_missing.row_(missingNumber);
    explanatory_missing.column_(dimension);
    objective_missing.row_(missingNumber);
    objective_missing.column_(1);
    explanatory_training.row_(trainingDataNumber);
    explanatory_training.column_(dimension);
    objective_training.row_(trainingDataNumber);
    objective_training.column_(1);
    prediction.row_(missingNumber);
    prediction.column_(1);
    int* dataIndex=new int[dataNumber];
    for(int i=0;i<dataNumber;i++)
        dataIndex[i]=i;
    shuffle(dataIndex,dataNumber,seed);
    for(int i=0;i<missingNumber;i++){
        for(int j=0;j<dimension;j++)
            explanatory_missing[i][j]=data[dataIndex[i]][j];
        objective_missing[i][0]=data[dataIndex[i]][dimension];
    }
    for(int i=missingNumber;i<dataNumber;i++){
        for(int j=0;j<dimension;j++)
            explanatory_training[i-missingNumber][j]=data[dataIndex[i]][j];
        objective_training[i-missingNumber][0]=data[dataIndex[i]][dimension];
    }
    delete[] dataIndex;
}

void Regression::print(){
    std::cout<<"dataNumber="<<dataNumber<<std::endl;
    std::cout<<"missingRate="<<missingRate<<std::endl;
    std::cout<<"missingNumber="<<missingNumber<<std::endl;
    std::cout<<"trainingDataNumber="<<trainingDataNumber<<std::endl;
    std::cout<<"dimension="<<dimension<<std::endl;
    std::cout<<"explanatory_training=\n";
    explanatory_training.print();
    std::cout<<"objective_training=\n";
    objective_training.print();
    std::cout<<"explanatory_missing=\n";
    explanatory_missing.print();
    std::cout<<"objective_missing=\n";
    objective_missing.print();
}

void Regression::train(double criterion){}

void Regression::predict(){}

double Regression::mae(){
    predict();
    Matrix tmp_matrix(prediction-objective_missing);
    double result=tmp_matrix.l1norm()/missingNumber;
    return result;
}