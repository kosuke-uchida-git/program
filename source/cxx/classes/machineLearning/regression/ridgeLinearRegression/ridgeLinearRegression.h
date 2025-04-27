#include"../linearRegression/linearRegression.h"

#ifndef RIDGE_LINEAR_REGRESSION
#define RIDGE_LINEAR_REGRESSION

class RidgeLinearRegression : virtual public LinearRegression{
    protected:
        double ridgeRegularizer;
    public:
        RidgeLinearRegression(Matrix data, double arg_missingRate, int seed, double arg_ridgeRegularizer);
        double ridgeRegularizer_() const;
        double& ridgeRegularizer_();
        virtual void revise_coefficient(int dimension_index) override;
};

#endif