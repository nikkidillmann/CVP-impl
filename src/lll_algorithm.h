#ifndef LLL_ALGORITHM_H
#define LLL_ALGORITHM_H

#include <vector>

#include "Eigen/Dense"

using std::vector;
using Eigen::MatrixXd;

class LLL {
public:

    // Does static make the code faster? - Daniel
    
    // returns the Euclidean distance between v1 and v2
    static MatrixXd lll_reduce(MatrixXd& to_reduce);

    static MatrixXd gram_schmidt(MatrixXd& in);

    static MatrixXd size_reduce(MatrixXd& in);

    static MatrixXd gso(MatrixXd &basis);

    // computes <v1, v2> / <v2, v2>
    static double gs_coefficient(VectorXd &v1, VectorXd &v2);

};

#endif // LLL_ALGORITHM_H
