#include "voronoi.h"
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
    m(0,0) = 16;
    Voronoi v;
    MatrixXd vor = v.voronoi_cell(m);
    cout << vor << endl;;
}

void two_dim() {
    MatrixXd m(2,2);
    m(0,0) = 1;
    m(0,1) = 0;
    m(1,0) = 0;
    m(1,1) = 1;
    Voronoi v;
    MatrixXd vor = v.voronoi_cell(m);
    cout << vor << endl;
}