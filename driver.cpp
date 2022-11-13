#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <fstream>
#include "cvp.h"

using namespace std;

// takes two files as arguments
// the first specifies the lattice basis, with vectors separated by lines and elements separated by spaces
// the second specifies the target, with elements separated by spaces
int main(int argc, char* argv[]) {
    CVP c;
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
        c.lattice.insert(basis_vec);
    }
    file_name = argv[1];
    fstream target_file;
    target_file.open(file_name);
    double element;
    while(target_file >> element) {
        c.target.push_back(element);
    }
}