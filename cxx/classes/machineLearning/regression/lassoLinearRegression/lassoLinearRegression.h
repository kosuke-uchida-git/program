#include"../linearRegression/linearRegression.h"

class LassoLinearRegression : public LinearRegression{
    protected:
        double lassoRegularizer;
    public:
        LassoLinearRegression(Matrix data, double arg_missingRate, int seed, double arg_lassoRegularizer);
        double lassoRegularizer_() const;
        double& lassoRegularizer_();
        void revise_coefficient(int dimension_index) override;
};