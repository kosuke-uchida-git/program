#include"../linearRegression/linearRegression.h"

#ifndef LASSO_LINEAR_REGRESSION
#define LASSO_LINEAR_REGRESSION

class LassoLinearRegression : virtual public LinearRegression{
    protected:
        double lassoRegularizer;
    public:
        LassoLinearRegression(Matrix data, double arg_missingRate, int seed, double arg_lassoRegularizer);
        double lassoRegularizer_() const;
        double& lassoRegularizer_();
        virtual void revise_coefficient(int dimension_index) override;
};

#endif