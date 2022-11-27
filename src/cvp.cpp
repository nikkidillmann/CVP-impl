#include "cvp.h"

using namespace std;


vector<double> CVP::closest_vector() {
    // TODO
}

vector<vector<double>> CVP::preprocess() {

}

vector<double> CVP::walk_phase(vector<double> &curr_target, int iteration) {
    while(!in_cell(curr_target, iteration - 1)) {
        vector<double> to_subtract = maximize_ratio(curr_target, iteration - 1);
        vector<double> subtracted = VectorOps::subtract_vectors(curr_target, to_subtract);
        return walk_phase(subtracted, iteration);
    }
    return curr_target;
}

bool CVP::in_cell(vector<double> &curr_target, int scaling) {
    vector<vector<double>> scaling = scaled_cell(scaling);
    double length_target =
      VectorOps::distance(curr_target,
                          vector<double> origin(curr_target.size(), 0));
    for(vector<double> vec : scaling) {
        if(distance(vec, curr_target) > length_target) return false;
    }
    return true;
}

vector<double> CVP::maximize_ratio(vector<double> &curr_target, int scaling) {
    vector<vector<double>> scaling = scaled_cell(scaling);
    double curr_max = 0;
    vector<double> maximizes;
    for(vector<double> vec : scaling) {
        double ratio = VectorOps::inner_product(curr_target, vec) /
          VectorOps::inner_product(vec, vec);
        if(ratio > curr_max) {
            curr_max = ratio;
            maximizes = vec;
        }
    }
    return maximizes;
}

vector<vector<double>> CVP::scaled_cell(int scaling) {
    vector<vector<double>> scaled = relevant_vecs;
    for(vector<double> vec : scaled) {
        std::for_each(vec.begin(), vec.end(),
                      [scaling](auto &elem) { elem *= scaling; })
    }
    return scaled;
}
