#include "cvp.h"


using namespace std;


MMatrixXd CVP::closest_vector() {
    preprocess();
    CVPP::CVPP c(lattice, target, relevant_vecs, dim);
    return c.closest_vector();
}

void CVP::preprocess() {
    Voronoi v;
    relevant_vecs = v.voronoi_cell(lattice);
}


