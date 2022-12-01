#include <cassert>
#include <vector>
#include <iostream>
#include <string>
#include <math.h>

#include "lll_algorithm.h"

using namespace std;

MatrixXd LLL::lll_reduce(MatrixXd &to_reduce) {
    bool reduced = false;
    MatrixXd gs_reduced;
    int i = 5;
    while(!reduced && --i > 0) {
        reduced = true;
        to_reduce = size_reduce(to_reduce);
        gs_reduced = gso(to_reduce);
        for (int i = 0; i < to_reduce.rows()-1; i++) {
            double lhs = (.75) * pow(sqrt((gs_reduced.col(i)).dot(gs_reduced.col(i))), 2);
            VectorXd b_i = to_reduce.col(i);
            VectorXd gs_b = gs_reduced.col(i+1);
            double coeff = gs_coefficient(b_i, gs_b);
            VectorXd scaled = coeff * gs_reduced.col(i);
            VectorXd comp = scaled + gs_reduced.col(i+1);
            double rhs = pow(sqrt(comp.dot(comp)), 2);
            if(lhs > rhs) {     // Lovasz condition is violated
                reduced = false;
                VectorXd temp = to_reduce.col(i);
                to_reduce.col(i) = to_reduce.col(i+1);
                to_reduce.col(i+1) = temp;
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
    MatrixXd gs = gso(in);
    for(int j = 2; j < in.rows(); j++) {
        for(int i = j-1; i >= 0; i--) {
            VectorXd b_j = in.col(j);
            VectorXd gs_bi = gs.col(i);
            double scaling = gs_coefficient(b_j, gs_bi);
            if(abs(scaling) > .5) {
                VectorXd scaled = round(scaling) * in.col(i);
                in.col(j) = in.col(j) - scaled;
                gs = gso(in);
            }
        }
    }
    std::cout << "size reduced:\n" << in;
    return in;
}

MatrixXd LLL::gso(MatrixXd &basis) {
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

    //std::cout << qr.matrixQ() << std::endl;
    //std::cout << diag_matrix << std::endl;
    std::cout << "gs:\n" << gso_basis << std::endl;

    // This is a bit suspect
    return gso_basis;
}

double LLL::gs_coefficient(VectorXd &v1, VectorXd &v2) {
    return v1.dot(v2) / v2.dot(v2);
}


