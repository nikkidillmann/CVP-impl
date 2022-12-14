#include "cvpp.h"


using namespace std;


MatrixXd CVPP::closest_vector() {
    int p = 1;
    while(!in_cell(target, p)) {
        p++;
    }
    VectorXd initial_target = target;
    for(; p > 0; p--) {
        VectorXd init_target = target;
        target = init_target - walk_phase(target, p);
    }
    return initial_target - target;
}

VectorXd CVPP::walk_phase(VectorXd &curr_target, int iteration) {
    VectorXd initial_target = curr_target;
    while(!in_cell(curr_target, iteration - 1)) {
        curr_target = curr_target - maximize_ratio(curr_target, iteration - 1);
    }
    return initial_target - curr_target;
}

bool CVPP::in_cell(VectorXd &curr_target, int scaling) {
    MatrixXd scaled = scaled_cell(scaling);
    for(int i = 0; i < relevant_vecs.cols(); i++) {
        VectorXd v = scaled.col(i);
        if(v.dot(v) < 2 * curr_target.dot(v)) return false;
    }
    return true;
}

VectorXd CVPP::maximize_ratio(VectorXd &curr_target, int scaling) {
    MatrixXd scaled = scaled_cell(scaling);
    double curr_max = 0;
    VectorXd maximizes;
    for(int i = 0; i < scaled.cols(); i++) {
        VectorXd col = scaled.col(i);
        double ratio = col.dot(curr_target) / col.dot(col);
        if(ratio > curr_max) {
            curr_max = ratio;
            maximizes = col;
        }
    }
    return maximizes;
}

MatrixXd CVPP::scaled_cell(int scaling) {
    MatrixXd scaled = relevant_vecs;
    return scaled * pow(2, scaling);
}
