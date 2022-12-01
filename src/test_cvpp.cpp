#include "cvpp.h"
#include "../include/Eigen/Dense"

using Eigen::MatrixXd;
using Eigen::VectorXd;

void one_dim();

int main(int argc, char** argv) {
    one_dim();
}

void one_dim() {
    MatrixXd m(1,1);
    MatrixXd rel(1,2);
    VectorXd tar(1);
    tar(0) = 17;
    m(0,0) = 3;
    rel(0,0) = 3;
    rel(0,1) = -3;
    CVPP c(m, tar, rel, 1);
    assert(c.closest_vector() == 18);
    cout << "PASSED!\n";
}