#ifndef VORONOI_H
#define VORONOI_H

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <math.h>
#include <climits>
#include <bitset>
#include "../include/Eigen/Dense"
#include "cvpp.h"
#include "lll_algorithm.h"

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;

class Voronoi {
public:
    // return the Voronoi relevant vectors for the lattice defined by basis in
    MatrixXd voronoi_cell(MatrixXd &in);

private:
    // assumes basis is an LLL reduced basis
    VectorXd rank_reduce(VectorXd &target,
                               MatrixXd &basis,
                               MatrixXd &vor, double h);

    MatrixXd find_relevant(size_t dim, MatrixXd &in,
                       MatrixXd &v_partial, double h);

    MatrixXd remove_non_relevant(MatrixXd &vor);

    MatrixXd compute_cell(MatrixXd &curr_basis,
                      MatrixXd &v, double scale);

    VectorXd binary_vec(int i, int dim);

    void remove_col(MatrixXd &to_remove, int col);
};

#endif // VORONOI_H
