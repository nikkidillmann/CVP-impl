#ifndef CVP_H
#define CVP_H

#include <iostream>
#include <vector>
#include <vector>
#include <string>
#include <cassert>
#include <math.h>
#include "voronoi.h"
#include "cvpp.h"

#include "../include/Eigen/Dense"

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd; 

// CVP without preprocessed Voronoi cell. Computes Voronoi cell and consults
// CVPP (CVP with preprocessed Voronoi cell)
class CVP {
public:
    // Basis vectors
    MatrixXd lattice;
    
    // Relevant vectors of voronoi cell
    MatrixXd relevant_vecs;
    
    // target vector
    VectorXd target;

    // dimension of lattice (assume full rank)
    int32_t dim;
    
    CVP(MatrixXd &l, VectorXd &t, int32_t d)
        : lattice(l), target(t), dim(d) {}

    MatrixXd closest_vector();

private:
    // returns relevant vectors of the Voronoi cell
    void preprocess();
};

#endif // CVP_H
