#include "lll_algorithm.h"
#include "../include/Eigen/Dense"
#include "../include/Eigen/LU"

using Eigen::MatrixXd;
using Eigen::VectorXd;

void one_dim();
void two_dim();
void three_dim();
void three_dim_red();
void hard_test();
bool check_reduced(MatrixXd &lat);
bool equivalent(MatrixXd &lat, MatrixXd &red);

int main(int argc, char** argv) {
    one_dim();
    two_dim();
    three_dim();
    three_dim_red();
    hard_test();
}

void one_dim() {
    MatrixXd m(1,1);
    m(0,0) = 1;
    MatrixXd m_r = LLL::lll_reduce(m);
    assert(check_reduced(m_r));
    assert(equivalent(m, m_r));
    std::cout << "PASSED!\n";
}


void two_dim() {
    MatrixXd m(2,2);
    m << 1, 0,
         0, 1;
    MatrixXd m_r = LLL::lll_reduce(m);
    assert(check_reduced(m_r));
    assert(equivalent(m, m_r));
    std::cout << "PASSED!\n";
}

void three_dim() {
    MatrixXd lattice(3,3);
    lattice << 1,1,1, -1,0,2, 3,5,6;
    MatrixXd lattice_red = LLL::lll_reduce(lattice);
    assert(check_reduced(lattice_red));
    assert(equivalent(lattice, lattice_red));
    std::cout << "PASSED!\n";
}

void three_dim_red() {
    MatrixXd lattice(3,3);
    lattice << 0,1,0, 1,0,1, -1,0,2;
    MatrixXd lattice_red = LLL::lll_reduce(lattice);
    assert(check_reduced(lattice_red));
    assert(equivalent(lattice, lattice_red));
    std::cout << "PASSED!\n";
}

void hard_test() {
    MatrixXd lattice(6,6);
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            lattice(i, j) = rand();
        }
    }
    MatrixXd lattice_red = LLL::lll_reduce(lattice);
    assert(check_reduced(lattice_red));
    // this check does not pass, but appears to be due to precision errors
    assert(equivalent(lattice, lattice_red));
    std::cout << "PASSED!\n";
}

bool check_reduced(MatrixXd &lat) {
    MatrixXd gs_reduced = LLL::gso(lat);
    MatrixXd to_reduce = lat;
    // Lovasz condition
    for (int i = 0; i < to_reduce.rows()-1; i++) {
        double lhs = (.75) * (gs_reduced.col(i)).dot(gs_reduced.col(i));
        VectorXd b = to_reduce.col(i+1);
        VectorXd gs_b = gs_reduced.col(i);
        double coeff = LLL::gs_coefficient(b, gs_b);
        VectorXd scaled = coeff * gs_reduced.col(i);
        VectorXd comp = scaled + gs_reduced.col(i+1);
        double rhs = comp.dot(comp);
        if(lhs > rhs) {     
            return false;
        }
    }

    // size reduced
    for(int i = 0; i < to_reduce.rows(); i++) {
        for(int j = i + 1; j < to_reduce.rows(); j++) {
            VectorXd gs_bi = gs_reduced.col(i);
            VectorXd b_j = to_reduce.col(j);
            if(LLL::gs_coefficient(b_j, gs_bi) > .5) return false;
        }
    }

    return true;
}

// checks that red^-1 * lat has det 1 
// TODO: check integral
bool equivalent(MatrixXd &lat, MatrixXd &red) {
    MatrixXd u = lat.inverse() * red;
    std::cout << "U matrix: \n" << u << std::endl;
    return u.determinant() == 1 || u.determinant() == -1;
}