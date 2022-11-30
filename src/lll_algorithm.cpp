#include "lll_algorithm.h"

using namespace std;

MatrixXd LLL::lll_reduce(MatrixXd &to_reduce) {
    bool reduced = false;
    MatrixXd gs_reduced;
    while(!reduced) {
        reduced = true;
        to_reduce = size_reduce(to_reduce);
        gs_reduced = gram_schmidt(to_reduce);
        for (size_t i = 0; i < to_reduce.size()-1; i++) {
            double lhs = (.75) * pow(VectorOps::length(gs_reduced[i]), 2);
            double coeff = gs_coefficient(to_reduce[i], gs_reduced[i+1]);
            vector<double> scaled = VectorOps::scale(gs_reduced[i], coeff);
            vector<double> comp = VectorOps::add_vectors(scaled, gs_reduced[i+1]);
            double rhs = pow(VectorOps::length(comp), 2);
            if(lhs > rhs) {     // Lovasz condition is violated
                reduced = false;
                vector<double> temp = to_reduce[i];
                to_reduce[i] = to_reduce[i+1];
                to_reduce[i+1] = temp;
                break;
            }
        }
        if(reduced) {
            return to_reduce;
        }
    }
    return to_reduce;
}

MatrixXd LLL::size_reduce(MatrixXd &in) {
    MatrixXd gs = gram_schmidt(in);
    for(size_t j = 2; j < dim; j++) {
        for(int i = j-1; i >= 0; i--) {
            double scaling = gs_coefficient(in.col(j), gs.col(i));
            if(abs(scaling) > .5) {
                VectorXd scaled = round(scaling) * in.col(i);
                in.col(j) = in.col(j) - scaled;
                gs = gram_schmidt(in);
            }
        }
    }
    return in;
}

MatrixXd LLL::gram_schmidt(MatrixXd &in) {
    vector<vector<double>> gs;
    gs.push_back(in[0]);
    for(size_t i = 1; i < dim; i++) {
        vector<double> to_orthog = in[i];
        for(size_t j = 0; j < i; j++) {
            double scaling = gs_coefficient(to_orthog, gs[j]);
            vector<double> scaled = VectorOps::scale(gs[j], scaling);
            to_orthog = VectorOps::subtract_vectors(to_orthog, scaled);
        }
        gs.push_back(to_orthog);
    }
    return gs;
}

double LLL::gs_coefficient(VectorXd &v1, VectorXd &v2) {
    return v1.dot(v2) / v2.dot(v2);
}

