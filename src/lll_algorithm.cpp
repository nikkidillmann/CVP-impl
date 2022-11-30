#include <cassert>
#include <vector>
#include <iostream>
#include <string>
#include <math.h>

#include "vector_ops.h"
#include "lll_algorithm.h"

#include "Eigen/Dense"

using std::vector;
using Eigen::Dense;

void print_lattice(vector<vector<double>> &lat);

vector<vector<double>> LLL::lll_reduce(vector<vector<double>> &to_reduce) {
    bool reduced = false;
    vector<vector<double>> gs_reduced;
    int i = 5;
    while(!reduced && --i > 0) {
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

vector<vector<double>> LLL::gram_schmidt(vector<vector<double>> &in) {
    assert(in.size() > 0);
    vector<vector<double>> gs;
    gs.push_back(in[0]);
    for(size_t i = 1; i < in.size(); i++) {
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

MatrixXd &&LLL::gso(MatrixXd &basis) {
    Eigen::FullPivHouseholderQR<MatrixXd> qr(basis);

    // This is B = QR where B is our basis
    const MatrixXd &basis_qr = qr.matrixQR();
    
    // Q^-1
    const MatrixXd &basis_q_inverse = qr.matrixQ().inverse();

    // Q^-1(QR) = R
    const MatrixXd &basis_r = basis_q_inverse * basis_qr;

    // Factor out R into DU where D is diagonal
    size_t DIM = basis.rows();
    MatrixXd diag_matrix = MatrixXd::Zero(DIM, DIM);
    for (size_t i = 0; i < DIM; ++i) {
        diag_matrix(i,i) = basis_r.diagonal()(i);
    }

    // GS Basis = QD
    MatrixXd gso_basis = qr.matrixQ() * diag_matrix;

    std::cout << qr.matrixQ() << std::endl;
    std::cout << diag_matrix << std::endl;
    std::cout << gso_basis << std::endl;

    // This is a bit suspect
    return std::move(gso_basis);
}

vector<vector<double>> LLL::size_reduce(vector<vector<double>> &in) {
    vector<vector<double>> gs = gram_schmidt(in);
    for(size_t j = 2; j < gs.size(); j++) {
        for(int i = j-1; i >= 0; i--) {
            double scaling = gs_coefficient(in[j], gs[i]);
            if(abs(scaling) > .5) {
                vector<double> scaled = VectorOps::scale(in[i], round(scaling));
                in[j] = VectorOps::subtract_vectors(in[j], scaled);
                gs = gram_schmidt(in);
            }
        }
    }
    return in;
}

double LLL::gs_coefficient(vector<double> &v1, vector<double> &v2) {
    return VectorOps::inner_product(v1, v2) / VectorOps::inner_product(v2, v2);
}

void print_lattice(vector<vector<double>> &lat) {
    for(size_t i = 0; i < lat.size(); i++) {
        for(size_t j = 0; j < lat[0].size(); j++) {
            cout << lat[i][j] << " ";
        }
        cout << "\n";
    }
}

