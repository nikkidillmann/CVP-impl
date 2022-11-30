#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "cvp.h"
#include "lll_algorithm.h"

#include "Eigen/Dense"
#include "Eigen/LU"
 
using Eigen::MatrixXd;

// Takes two files as arguments:
// 1. First file specifies the lattice basis
// with vectors separated by lines and elements separated by spaces
// 2. Second specifies the target, with elements separated by spaces

// Maybe we should also make the user specify the dimension of the lattice,
// so that we don't need to allocate extra space?
int main(int argc, char* argv[]) {
    MatrixXd m(2,2);
    
    m(0,0) = 3;
    m(1,0) = 13;
    m(0,1) = -1;
    m(1,1) = 100;

    LLL::gso(m);

    // std::cout << m << std::endl;

    // Eigen::FullPivHouseholderQR<MatrixXd> qr(m.rows(), m.cols());

    // auto q = qr.compute(m).matrixQ();

    // std::cout << q << std::endl;

    // std::cout << q(0, 0) << std::endl;

    // auto res = qr.compute(m).matrixQ() * (qr.compute(m).matrixQ().inverse() * qr.compute(m).matrixQR());

    // std::cout << res << std::endl;
    // std::cout << qr.compute(m).matrixQR() << std::endl;

    // std::cout << res.diagonal() << std::endl;

    // MatrixXd m2(2,2);
    // m2(0,0) = 1;
    // m2(1,0) = 0;
    // m2(0,1) = 0;
    // m2(1,1) = 1;

    // std::cout << m2 << std::endl;

    // MatrixXd m3 = MatrixXd::Zero(2, 2);

    // std::cout << m3 << std::endl;

    // for (size_t t = 0; t < 2; ++t) {
    //     m3(t, t) = res.diagonal()(t);
    // }
    // std::cout << m3 << std::endl;

    // std::cout << m2 * m3 << std::endl;
    
    /**
    string file_name = argv[0];
    fstream basis_nfile;
    basis_file.open(file_name);
    string line;
    while(getline(basis_file, line)) {
        istringstream vec(line);
        double element;
        vector<double> basis_vec;
        while(vec >> element) {
            basis_vec.push_back(element);
        }
        //c.lattice.push_back(basis_vec);
    }
    file_name = argv[1];
    fstream target_file;
    target_file.open(file_name);
    double element;
    while(target_file >> element) {
        //c.target.push_back(element);
    }
    **/
}
