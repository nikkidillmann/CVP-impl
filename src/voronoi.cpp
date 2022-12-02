#include "voronoi.h"


MatrixXd Voronoi::voronoi_cell(MatrixXd &in) {
    in = LLL::lll_reduce(in);
    MatrixXd gs = LLL::gso(in);
    MatrixXd voronoi;
    voronoi.resize(gs.rows(), 2);
    voronoi.col(0) = gs.col(0);
    voronoi.col(1) = -1 * gs.col(0);
    MatrixXd curr_basis(in.rows(), 1);
    curr_basis.col(0) = in.col(0);
    for(int k = 1; k < in.rows(); k++) {
        curr_basis.conservativeResize(in.rows(), k+1);
        curr_basis.col(k) = in.col(k);
        cout << pow(2, .5*(k+1)) << endl;
        voronoi = compute_cell(curr_basis, voronoi, pow(2, .5*(k+1)));
    }
    return voronoi;
}


VectorXd Voronoi::rank_reduce(VectorXd &target,
                                    MatrixXd &basis,
                                    MatrixXd &vor, double h) {
    MatrixXd gs = LLL::gso(basis);
    VectorXd gs_bk = gs.col(gs.cols() - 1);
    double i = LLL::gs_coefficient(target, gs_bk);
    VectorXd closest; 
    double min_dist = INT_MAX;
    int start = round(i - h);
    if (!(abs(start - i) < h)) start++;
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
MatrixXd Voronoi::find_relevant(size_t dim, MatrixXd &in,
                            MatrixXd &v_partial, double h) {
    MatrixXd v_next = v_partial;
    int i = 1;
    while(i < pow(2,dim)) {
        VectorXd p = binary_vec(i++, dim);
        VectorXd t = -1 * in * p;
        VectorXd c = rank_reduce(t, in, v_partial, h);
        v_next.conservativeResize(v_next.rows(), v_next.cols() + 2);
        v_next.col(v_next.cols() - 2) = 2 * (c-t);
        v_next.col(v_next.cols() - 1) = -2 * (c-t);
    }
    return v_next;
}

MatrixXd Voronoi::remove_non_relevant(MatrixXd &vor) {
    assert(false);
}

MatrixXd Voronoi::compute_cell(MatrixXd &curr_basis,
                           MatrixXd &v, double scale) {
    // Prevent compiler errors
    MatrixXd vor = find_relevant(curr_basis.rows(), curr_basis, v, scale);
    // vor = remove_non_relevant(vor);
    return vor;
}

VectorXd Voronoi::binary_vec(int i, int dim) {
    VectorXd p(dim);
    string binary = bitset<32>(i).to_string();
    int j = 0;
    for(int i = 0; i < dim; i++) {
        p(j) = (binary[binary.length() - 1- i] - '0') / 2.0;
        j++;
    }
    return p;
}
