#ifndef CVP_H
#define CVP_H

#include <iostream>
#include <vector>
#include <vector>
#include <string>
#include <cassert>
#include <math.h>
#include "vector_ops.h"
#include "voronoi.h"

#include "Eigen/Dense"

using namespace std; 

// I think we might need to switch to long long for our data types because of
// precision?
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
    
    CVP(MatrixXd &l, MatrixXd &t, int32_t d)
        : lattice(l), target(t), dim(d) {}

    MatrixXd closest_vector();

private:
    // returns relevant vectors of the Voronoi cell
    void preprocess();

    // performs one phase of the "walk"
    VectorXd walk_phase(VectorXd &curr_target, int iteration);

    // checks if curr_target is in scaled voronoi cell
    bool in_cell(VectorXd &curr_target, int scaling);

    // returns scaling of relevant_vecs
    MatrixXd scaled_cell(int scaling);

    // returns the vector v in the scaled Voronoi cell that maximizes <v,t>/<v,v>
    VectorXd maximize_ratio(VectorXd &curr_target, int scaling);
};

#endif // CVP_H
