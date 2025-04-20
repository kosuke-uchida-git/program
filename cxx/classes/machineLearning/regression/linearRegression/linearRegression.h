#include"../regression/regression.h"

#ifndef LINEAR_REGRESSION
#define LINEAR_REGRESSION

class LinearRegression : virtual public Regression{
    protected:
        double bias;
        Matrix coefficient;
        Matrix intermediate;
    public:
        LinearRegression(Matrix data, double arg_missingRate, int seed);
        void print() override;
        void train(double criterion) override;
        void predict() override;
        void revise_intermediate();
        void revise_bias();
        void revise_coefficient();
        virtual void revise_coefficient(int dimension_index);
};

#endif