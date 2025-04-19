#include"../linearRegression/linearRegression.h"

class RidgeLinearRegression : public LinearRegression{
    protected:
        double ridgeRegularizer;
    public:
        RidgeLinearRegression(Matrix data, double arg_missingRate, int seed, double arg_ridgeRegularizer);
        double ridgeRegularizer_() const;
        double& ridgeRegularizer_();
        void revise_coefficient(int dimension_index) override;
};