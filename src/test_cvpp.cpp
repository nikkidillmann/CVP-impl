#include "cvpp.h"
#include "../include/Eigen/Dense"

using Eigen::MatrixXd;
using Eigen::VectorXd;

void one_dim();
void two_dim();

int main(int argc, char** argv) {
    one_dim();
    two_dim();
}

void one_dim() {
    MatrixXd m(1,1);
    MatrixXd rel(1,2);
    VectorXd tar(1);
    tar(0) = 329;
    m(0,0) = 16;
    rel(0,0) = 16;
    rel(0,1) = -16;
    CVPP c(m, tar, rel, 1);
    cout << c.closest_vector() << endl;
    cout << "PASSED!\n";
}

void two_dim() {
    MatrixXd m(2,2);
    MatrixXd rel(2,8);
    VectorXd tar(2);
    tar(0) = 17.5;
    tar(1) = 5;
    m(0,0) = 2;
    m(1,0) = 0;
    m(0,1) = 0;
    m(1,1) = 2;
    rel(0,0) = 2;
    rel(1,0) = 0;
    rel(0,1) = -2;
    rel(1,1) = 0;
    rel(0,2) = 0;
    rel(1,2) = 2;
    rel(0,3) = 0;
    rel(1,3) = -2;
    rel(0,4) = 2;
    rel(1,4) = 2;
    rel(0,5) = -2;
    rel(1,5) = -2;
    rel(0,6) = -2;
    rel(1,6) = 2;
    rel(0,7) = 2;
    rel(1,7) = -2;
    CVPP c(m, tar, rel, 2);
    cout << c.closest_vector();
    cout << "PASSED!\n";
}