#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "cvp.h"
#include "lll_algorithm.h"

#include "../include/Eigen/Dense"
#include "../include/Eigen/LU"
 
using Eigen::MatrixXd;

// Takes three arguments:
// 1. Dimension (we assume full rank matrix)
// 2. First file specifies the lattice basis
// with vectors separated by lines and elements separated by spaces
// 3. Second specifies the target, with elements separated by spaces

// Maybe we should also make the user specify the dimension of the lattice,
// so that we don't need to allocate extra space?
int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Error: format is ./cvp dim <basis> <target>\n";
        exit(0);
    }
    int n = atoi(argv[1]);
    MatrixXd basis(n, n);
    VectorXd target(n);
    
    string file_name = argv[2];
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
            row++;
        }
        col++;
    }
    file_name = argv[3];
    fstream target_file;
    target_file.open(file_name);
    double element;
    col = 0;
    while(target_file >> element) {
        target(col) = element;
        col++;
    }
    cout << "Finding closest vector for basis\n" << basis << endl;
    cout << "With target\n" << target << endl;
    CVP c(basis, target, n);
    VectorXd closest = c.closest_vector();
    cout << "Closest Vector found!\n" << closest << endl;
}
