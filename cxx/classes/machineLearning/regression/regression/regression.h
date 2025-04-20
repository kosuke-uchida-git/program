#include"../../../math/matrix/matrix.h"

#ifndef REGRESSION
#define REGRESSION

class Regression{
    protected:
        Matrix explanatory_training;
        Matrix objective_training;
        Matrix explanatory_missing;
        Matrix objective_missing;
        Matrix prediction;
        int dataNumber;
        double missingRate;
        int missingNumber;
        int trainingDataNumber;
        int dimension;
        
    public:
        Regression(Matrix data, double arg_missingRate, int seed);
        virtual void print();
        virtual void train(double criterion);
        virtual void predict();
        double mae();
};

#endif