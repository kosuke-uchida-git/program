#include"../lassoLinearRegression/lassoLinearRegression.h"
#include"../ridgeLinearRegression/ridgeLinearRegression.h"

#ifndef ELASTIC_NET_LINEAR_REGRESSION
#define ELASTIC_NET_LINEAR_REGRESSION

class ElasticNetLinearRegression : virtual public LassoLinearRegression, virtual public RidgeLinearRegression{
    public:
        ElasticNetLinearRegression(Matrix data, double arg_missingRate, int seed, double arg_lassoRegularizer, double arg_ridgeRegularizer);
        virtual void revise_coefficient(int dimension_index) override;
};

#endif