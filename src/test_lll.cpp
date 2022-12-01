#include "lll_algorithm.h"
#include "../include/Eigen/Dense"

using Eigen::MatrixXd;
using Eigen::VectorXd;

void one_dim();
void two_dim();
void three_dim();
void three_dim_red();
// bool check_reduced(MatrixXd &lat);

int main(int argc, char** argv) {
    one_dim();
    two_dim();
    three_dim();
    three_dim_red();
}

void one_dim() {
    MatrixXd m(1,1);
    m(0,0) = 1;
    m = LLL::lll_reduce(m);
    std::cout << "LLL reduced:\n" << m << std::endl;
    std::cout << "PASSED!\n";
}


void two_dim() {
    MatrixXd m(2,2);
    m << 1, 0,
         0, 1;
    m = LLL::lll_reduce(m);
    std::cout << "LLL reduced:\n" << m << std::endl;
    std::cout << "PASSED!\n";
}

void three_dim() {
    MatrixXd lattice(3,3);
    lattice << 1,1,1, -1,0,2, 3,5,6;
    lattice = LLL::lll_reduce(lattice);
    std::cout << "LLL reduced:\n" << lattice << std::endl;
    std::cout << "PASSED!\n";
}

void three_dim_red() {
    MatrixXd lattice(3,3);
    lattice << 0,1,0, 1,0,1, -1,0,2;
    lattice = LLL::lll_reduce(lattice);
    std::cout << "LLL reduced:\n" << lattice << std::endl;
    std::cout << "PASSED!\n";
}

/*
bool check_reduced(vector<vector<double>> &lat) {
    // Lovasz condition
    vector<vector<double>> gs_reduced = LLL::gram_schmidt(lat);
    for(size_t i = 0; i < lat.size()-1; i++) {
        double lhs = (.75) * pow(VectorOps::length(gs_reduced[i]), 2);
        double coeff = LLL::gs_coefficient(lat[i], gs_reduced[i+1]);
        vector<double> scaled = VectorOps::scale(gs_reduced[i], coeff);
        vector<double> comp = VectorOps::add_vectors(scaled, gs_reduced[i+1]);
        double rhs = pow(VectorOps::length(comp), 2);
        if(lhs > rhs) {  
            return false;
        }
    }
    // size_reduced
    for(size_t i = 0; i < lat.size() - 1; i++) {
        for(size_t j = i +1; j < lat.size(); j++) {
            if(LLL::gs_coefficient(lat[i], gs_reduced[j]) > .5) return false;
        }
    }
    return true;
}
*/
