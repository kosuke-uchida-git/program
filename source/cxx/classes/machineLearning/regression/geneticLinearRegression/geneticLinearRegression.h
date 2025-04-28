#include"../regression/regression.h"

#ifndef GENETIC_LINEAR_REGRESSION
#define GENETIC_LINEAR_REGRESSION

class GeneticLinearRegression : virtual public Regression{
    protected:
        double bias;
        Matrix coefficient;
        Matrix intermediate;
    public:
        GeneticLinearRegression(Matrix data, double arg_missingRate, int seed);
        void print() override;
        void train(double criterion) override;
        void predict() override;
        double objectiveFunction(Matrix arg_coefficient,double arg_bias);
        void revise_intermediate();
        void revise_bias();
        void revise_coefficient();
        virtual void revise_coefficient(int dimension_index);
};

#endif