#ifndef CVPP_H
#define CVPP_H

#include <iostream>
#include <vector>
#include <vector>
#include <string>
#include <cassert>
#include <math.h>

#include "../include/Eigen/Dense"

using namespace std; 
using Eigen::MatrixXd;
using Eigen::VectorXd; 

// CVP assuming we have already computed Voronoi cell
class CVPP {
public:
    // Basis vectors
    MatrixXd lattice;
    
    // target vector
    VectorXd target;

    // Relevant vectors of voronoi cell
    MatrixXd relevant_vecs;

    // dimension of lattice (assume full rank)
    int32_t dim;

    CVPP(MatrixXd &l, VectorXd &t, MatrixXd &v, int32_t d)
        : lattice(l), target(t), relevant_vecs(v), dim(d) {}

    MatrixXd closest_vector();

private:
    // performs one phase of the "walk"
    VectorXd walk_phase(VectorXd &curr_target, int iteration);

    // checks if curr_target is in scaled voronoi cell
    bool in_cell(VectorXd &curr_target, int scaling);

    // returns scaling of relevant_vecs
    MatrixXd scaled_cell(int scaling);

    // returns the vector v in the scaled Voronoi cell that maximizes <v,t>/<v,v>
    VectorXd maximize_ratio(VectorXd &curr_target, int scaling);
};

#endif // CVPP_H