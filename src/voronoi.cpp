#include "voronoi.h"
#include "cvpp.h"
#include "lll_algorithm.h"

using namespace std;


MatrixXd Voronoi::voronoi_cell(MatrixXd &in) {
    in = LLL::lll_reduce(in);
    MatrixXd gs = LLL::gram_schmidt(in);
    MatrixXd voronoi;
    voronoi.resize(gs.rows(), 2);
    voronoi.col(0) = gs.col(0);
    voronoi.col(1) = -1 * gs.col(0);
    MatrixXd curr_basis(in.rows(), 1);
    curr_basis.col(0) = in.col(0);
    for(size_t k = 2; k < in.rows(); k++) {
        curr_basis.resize(in.rows(), k);
        curr_basis.col(k) = in.col(k);
        voronoi = compute_cell(curr_basis, voronoi, pow(2, .5*k));
    }
    return voronoi;
}


VectorXd Voronoi::rank_reduce(VectorXd &target,
                                    MatrixXd &basis,
                                    MatrixXd &vor, double h) {
    MatrixXd gs = LLL::gram_schmidt(basis);
    double i = LLL::gs_coefficient(target, gs.col(gs.cols()-1));
    VectorXd closest;
    double min_dist = INT_MAX;
    int start = round(i - h);
    while (abs(start - i) < h) {
        VectorXd scaled_basis = start * basis.col(basis.cols()-1);
        VectorXd subtracted = target - scaled_basis;
        CVPP c(basis, subtracted, vor, basis.rows());
        VectorXd curr = c.closest_vector() + scaled_basis;
        VectorXd diff = curr - target;
        if (sqrt(diff.dot(diff)) < min_dist) {
            closest = curr;
            min_dist = sqrt(diff.dot(diff));
        }
        start++;
    }
    return closest;
}

// Daniel
MatrixXd Voronoi::find_relevant(MatrixXd &in,
                            MatrixXd &v_partial, double h) {
    assert(false);
}

MatrixXd Voronoi::remove_non_relevant(MatrixXd &vor) {
    assert(false);
}

MatrixXd Voronoi::compute_cell(MatrixXd &curr_basis,
                           MatrixXd &v, double scale) {
    // Prevent compiler errors
    MatrixXd vor = find_relevant(curr_basis, v, scale);
    vor = remove_non_relevant(vor);
    return vor;
}
