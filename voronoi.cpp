#include "voronoi.h"


vector<vector<double>> Voronoi::voronoi_cell(vector<vector<double>> &in) {
    // nikki
}


void Voronoi::rank_reduce(vector<double> &target, vector<vector<double>> &basis, vector<vector<double>> vor, int h) {
    double i = LLL::gs_coefficient(target, basis[basis.size()-1]);
    vector<double> curr_closest;
    // nikki
}

// Daniel
void Voronoi::find_relevant() {
    
}

void Voronoi::remove_non_relevant() {

}

void Voronoi::compute_cell() {

}