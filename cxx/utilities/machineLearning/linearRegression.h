#include"../math/matrix.h"

class LinearRegression{
    protected:
        double bias;
        Matrix coefficient;
        Matrix intermediate;
        Matrix explanatory;
        Matrix objective;
        int dataNumber;
        int dimension;
    public:
        LinearRegression(Matrix data);
        void print();
        void train(double criterion);
        void revise_intermediate();
        void revise_bias();
        void revise_coefficient();
        void revise_coefficient(int dimension_index);
};