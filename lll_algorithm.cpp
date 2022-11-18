#include "lll_algorithm.h"

using namespace std;

vector<vector<double>> LLL::lll_reduce(vector<vector<double> &to_reduce) {
    bool reduced = false;
    while(!reduced) {
        reduced = true;
        to_reduce = size_reduce(to_reduce);
        gs_reduced = gram_schmidt(to_reduce);
        for(size_t i = 0; i < to_reduce.size()-1; i++) {
            double lhs = (.75) * pow(VectorOps::length(gs_reduced[i]), 2);
            double coeff = gs_coefficient(to_reduce[i], gs_reduced[i+1]);
            vector<double> comp = VectorOps::add_vectors(VectorOps::scale(gs_reduced[i], coeff), gs_reduced[i+1]);
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

vector<vector<double>> LLL:size_reduce(vector<vector<double>> &in) {
    vector<vector<double> to_reduce = gram_schmidt(in);
    for(size_t i = 2; i < to_reduce.size(); i++) {
        for(int j = i-1; j > 0; j--) {
            double scaling = gs_coefficient(to_reduce[i], in[j]);
            in[j] = VectorOps::subtract_vectors(in[j], VectorOps::scale(in[i], round(scaling)));
            to_reduce = gram_schmidt(in);
        }
    }
<<<<<<< HEAD
    return to_reduce;
=======

>>>>>>> 512038337dfb6c644cbde617749422b6904dead3
}

vector<vector<double>> LLL::gram_schmidt(vector<vector<double>> &in) {
    assert(in.size() > 0);
    vector<vector<double>> gs;
    gs.push_back(in[0]);
    for(size_t i = 0; i < in.size(); i++) {
        vector<double> to_orthog = in[i];
        for(size_t j = 0; j < gs.size(); j++) {
            double scaling = gs_coefficient(to_orthog, gs[j]);
            to_orthog = VectorOps::subtract_vectors(to_orthog, VectorOps::scale(gs[j], scaling));
        }
        gs.push_back(to_orthog);
    }
    return gs;
}

 double gs_coefficient(vector<double> &v1, vector<double> &v2) {
    VectorOps::inner_product(v1, v2) / VectorOps::inner_product(v2, v2);
 }

