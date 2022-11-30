#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "cvp.h"

#include "Eigen/Dense"
 
using Eigen::MatrixXd;

// Takes three arguments:
// 1. Dimension (we assume full rank matrix)
// 2. First file specifies the lattice basis
// with vectors separated by lines and elements separated by spaces
// 3. Second specifies the target, with elements separated by spaces

// Maybe we should also make the user specify the dimension of the lattice,
// so that we don't need to allocate extra space?
int main(int argc, char* argv[]) {
    int n = atoi(arg[0]);
    MatrixXd basis(n, n);
    MatrixXd target(n, 1);
    
    string file_name = argv[1];
    fstream basis_file;
    basis_file.open(file_name);
    string line;
    int col = 0;
    while(getline(basis_file, line)) {
        istringstream vec(line);
        double element;
        int row = 0;
        while(vec >> element) {
            basis(row, col) = element;
        }
    }
    file_name = argv[2];
    fstream target_file;
    target_file.open(file_name);
    double element;
    int col = 0
    while(target_file >> element) {
        target(0, col) = element;
    }
    
    CVP c(lattice, target, n);
    cout << c.closest_vector() << endl;
}
