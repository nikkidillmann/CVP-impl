#include "cvp.h"


using namespace std;


MatrixXd CVP::closest_vector() {
    preprocess();
    CVPP c(lattice, target, relevant_vecs, dim);
    return c.closest_vector();
}

void CVP::preprocess() {
    Voronoi v;
    relevant_vecs = v.voronoi_cell(lattice);
}


