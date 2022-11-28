#include "voronoi.h"

using namespace std;


vector<vector<double>> Voronoi::voronoi_cell(vector<vector<double>> &in) {
    vector<vector<double>> gs = LLL:gram_schmidt(in);
    vector<vector<double>> voronoi;
    voronoi.push_back(gs[0], VectorOps::scale(gs[0], -1));
    for(size_t k = 2; k < in.size(); k++) {
        vector<vector<double>> curr_basis(k);
        std::copy(gs.begin(), gs.begin() + k, curr_basis);
        voronoi = compute_cell(curr_basis, voronoi, pow(2, .5*k));
    }
    return voronoi;
}


vector<double> Voronoi::rank_reduce(vector<double> &target, vector<vector<double>> &basis, vector<vector<double>> vor, int h) {
    vector<vector<double>> gs = LLL::gram_schmidt(basis);
    double i = LLL::gs_coefficient(target, gs[gs.size()-1]);
    vector<double> closest;
    double min_dist = INT_MAX;
    int start = round(i - h);
    while (abs(start - i) < h) {
        CVP c(vor, target - VectorOps::scale(t, start));
        vector<double> curr = VectorOps::add(c.closest_vector(), VectorOps::scale(basis[basis.size()-1], start));
        if (VectorOps::distance(curr, target) < min_dist) {
            closest = curr;
            min_dist = VectorOps::distance(curr, target);
        }
    }
    return closest;
}

// Daniel
void Voronoi::find_relevant() {
    
}

void Voronoi::remove_non_relevant() {

}

void Voronoi::compute_cell() {

}
