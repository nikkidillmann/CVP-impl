#include "cvp.h"


using namespace std;


MMatrixXd CVP::closest_vector() {
    preprocess();
    int p = 1;
    while(!in_cell(target, p)) {
        p++;
    }
    for(; p >= 0; p--) {
        target = walk_phase(target, p);
    }
    return target;
}

void CVP::preprocess() {
    Voronoi v;
    relevant_vecs = v.voronoi_cell(lattice);
}

VectorXd CVP::walk_phase(VectorXd &curr_target, int iteration) {
    while(!in_cell(curr_target, iteration - 1)) {
        VectorXd next = curr_target - maximize_ratio(curr_target, iteration - 1);
        return walk_phase(next, iteration);
    }
    return curr_target;
}

bool CVP::in_cell(VectorXd &curr_target, int scaling) {
    MatrixXd scaled = scaled_cell(scaling);
    double length_target = sqrt(curr_target.dot(curr_target));
    for(int i = 0; i < dim; i++) {
        VectorXd dist = scaled.col(0) - curr_target;
        if(sqrt(dist.dot(dist)) > length_target) return false;
    }
    return true;
}

VectorXd CVP::maximize_ratio(VectorXd &curr_target, int scaling) {
    MatrixXd scaled = scaled_cell(scaling);
    double curr_max = 0;
    VectorXd maximizes;
    for(int i = 0; i < dim; i++) {
        VectorXd col = scaled.col(0)
        double ratio = col.dot(curr_target) / col.dot(col);
        if(ratio > curr_max) {
            curr_max = ratio;
            maximizes = col;
        }
    }
    return maximizes;
}

MatrixXd CVP::scaled_cell(int scaling) {
    MatrixXd scaled = relevant_vecs;
    return scaling * scaled;
}
