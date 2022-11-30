#ifndef VORONOI_H
#define VORONOI_H

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <math.h>
#include <climits>

using namespace std;


class Voronoi {
public:
    // return the Voronoi relevant vectors for the lattice defined by basis in
    MatrixXd voronoi_cell(MatrixXd &in);

private:
    // assumes basis is an LLL reduced basis
    VectorXd rank_reduce(VectorXd &target,
                               MatrixXd &basis,
                               MatrixXd &vor, double h);

    MatrixXd find_relevant(MatrixXd &in,
                       MatrixXd &v_partial, double h);

    MatrixXd remove_non_relevant(MatrixXd &vor);

    MatrixXd compute_cell(MatrixXd &curr_basis,
                      MatrixXd &v, double scale);
};

#endif // VORONOI_H
