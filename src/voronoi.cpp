#include "voronoi.h"
#include "cvp.h"
#include "vector_ops.h"
#include "lll_algorithm.h"

using namespace std;


vector<vector<double>> Voronoi::voronoi_cell(vector<vector<double>> &in) {
    vector<vector<double>> gs = LLL::gram_schmidt(in);
    vector<vector<double>> voronoi;
    VectorOps::scale(gs[0], -1);
    voronoi.push_back(gs[0]);
    for(size_t k = 2; k < in.size(); k++) {
        vector<vector<double>> curr_basis(k);
        std::copy(gs.begin(), gs.begin() + k, back_inserter(curr_basis));
        voronoi = this->compute_cell(curr_basis, voronoi, pow(2, .5*k));
    }
    return voronoi;
}


vector<double> Voronoi::rank_reduce(vector<double> &target,
                                    vector<vector<double>> &basis,
                                    vector<vector<double>> vor, int h) {
    vector<vector<double>> gs = LLL::gram_schmidt(basis);
    double i = LLL::gs_coefficient(target, gs[gs.size()-1]);
    vector<double> closest;
    double min_dist = INT_MAX;
    int start = round(i - h);
    while (abs(start - i) < h) {
        // Had to comment this out because compiler is saying t is not defined
        // - Daniel
        // CVP c(vor, target - VectorOps::scale(t, start));
        CVP c;
        vector<double> scaled_basis = VectorOps::scale(basis.back(), start);
        vector<double> closest = c.closest_vector();
        vector<double> curr = VectorOps::add_vectors(closest,
                                                     scaled_basis);
        
        if (VectorOps::distance(curr, target) < min_dist) {
            closest = curr;
            min_dist = VectorOps::distance(curr, target);
        }
    }
    return closest;
}

// Daniel
void Voronoi::find_relevant(vector<vector<double>> &in,
                            vector<vector<double>> v_partial) {
    
}

void Voronoi::remove_non_relevant() {

}

vector<vector<double>> Voronoi::compute_cell(vector<vector<double>> &curr_basis,
                           vector<vector<double>> &v, double scale) {
    // Prevent compiler errors
    assert(false);
}
