#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "cvp.h"

#include "Eigen/Dense"
 
using Eigen::MatrixXd;

// Takes two files as arguments:
// 1. First file specifies the lattice basis
// with vectors separated by lines and elements separated by spaces
// 2. Second specifies the target, with elements separated by spaces

// Maybe we should also make the user specify the dimension of the lattice,
// so that we don't need to allocate extra space?
int main(int argc, char* argv[]) {
    CVP c;
    std::cout << "IS THIS WORKING????" << std::endl;
    MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    std::cout << m << std::endl;
    
    /**
    string file_name = argv[0];
    fstream basis_file;
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
