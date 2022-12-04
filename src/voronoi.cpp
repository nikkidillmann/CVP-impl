#include "voronoi.h"


MatrixXd Voronoi::voronoi_cell(MatrixXd &in) {
    in = LLL::lll_reduce(in);
    cout << "LLL reduced basis:\n" << in << endl;
    MatrixXd gs = LLL::gso(in);
    cout << "After Modified Gram-Schmidt:\n" << gs << endl;
    MatrixXd voronoi;
    voronoi.resize(gs.rows(), 2);
    voronoi.col(0) = gs.col(0);
    voronoi.col(1) = -1 * gs.col(0);
    MatrixXd curr_basis(in.rows(), 1);
    curr_basis.col(0) = in.col(0);
    for(int k = 1; k < in.rows(); k++) {
        curr_basis.conservativeResize(in.rows(), k+1);
        curr_basis.col(k) = in.col(k);
        voronoi = compute_cell(curr_basis, voronoi, pow(2, .5*(k+1)));
    }
    cout << "Computed Voronoi Cell:\n" << voronoi << endl;
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
    assert(abs(start - i) < h);            // otherwise we will have problems
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
    for (int i = vor.cols() - 1; i >= 0; i--) {
        for (int j = vor.cols() - 1; j >= 0; j--) {
            if (i == j) continue;
            VectorXd v_i = vor.col(i) / 2;
            VectorXd dist = vor.col(j) - v_i;
            if(dist.dot(dist) <= v_i.dot(v_i)) {
                remove_col(vor, i);
                break;
            }
        }
    }
    return vor;
}

MatrixXd Voronoi::compute_cell(MatrixXd &curr_basis,
                           MatrixXd &v, double scale) {
    cout << "computing cell\n";
    MatrixXd vor = find_relevant(curr_basis.cols(), curr_basis, v, scale);
    cout << "found relevant:\n" << vor << endl;
    vor = remove_non_relevant(vor);
    cout << "removing non relevant:\n" << vor << endl;
    return vor;
}

VectorXd Voronoi::binary_vec(int i, int dim) {
    VectorXd p(dim);
    // you can use boost to dynamically set the size
    // but if we try to process a 129 dim lattice we will have plenty of other problems
    string binary = bitset<128>(i).to_string();
    int j = 0;
    for(int i = 0; i < dim; i++) {
        p(j) = (binary[binary.length() - 1- i] - '0') / 2.0;
        j++;
    }
    return p;
}

void Voronoi::remove_col(MatrixXd &to_remove, int col) {
    for(int i = col; i < to_remove.cols() - 1; i++) {
        to_remove.col(i) = to_remove.col(i+1);
    }
    to_remove.conservativeResize(to_remove.rows(), to_remove.cols() - 1);
}