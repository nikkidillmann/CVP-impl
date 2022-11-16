#include "cvp.h"

using namespace std;

vector<double> CVP::walk_phase(vector<double> &curr_target, int iteration) {
    if(in_cell(curr_target, iteration - 1)) return curr_target;
    vector<double> to_subtract = maximize_ratio(curr_target, iteration - 1);
    return subtract_vectors(curr_target, to_subtract);
}

bool CVP::in_cell(vector<double> &curr_target, int scaling) {
    set<vector<double>> scaling = scaled_vector(scaling);
    double length_target = distance(curr_target, vector<double> origin(curr_target.size(), 0));
    for(vector<double> vec : scaling) {
        if(distance(vec, curr_target) > length_target) return false;
    }
    return true;
}

vector<double> CVP::maximize_ratio(vector<double> &curr_target, int scaling) {
    set<vector<double>> scaling = scaled_vector(scaling);
    double curr_max = 0;
    vector<double> maximizes;
    for(vector<double> vec : scaling) {
        double ratio = inner_product(curr_target, vec) / inner_product(vec, vec);
        if(ratio > curr_max) {
            curr_max = ratio;
            maximizes = vec;
        }
    }
    return maximizes;
}

set<vector<double>> CVP::scaled_cell(int scaling) {
    set<vector<double>> scaled = relevant_vecs;
    for(vector<double> vec : scaled) {
        std::for_each(vec.begin(), vec.end(), [scaling](auto &elem) { elem *= scaling; })
    }
    return scaled;
}

double CVP::distance(vector<double> &v1, vector<double> &v2) {
    assert(v1.size() == v2.size());
    double running_sum = 0;
    for(size_t i = 0; i < v1.size(); i++) {
        running_sum += pow((v1[i] - v2[i]), 2);
    }
    return sqrt(running_sum);
}

double CVP::inner_product(vector<double> &v1, vector<double> &v2) {
    assert(v1.size() == v2.size());
    double running_sum = 0;
    for(size_t i = 0; i < v1.size(); i++) {
        running_sum += v1[i]*v2[i];
    }
}

vector<double> CVP::subtract_vectors(vector<double> &v1, vector<double> &v2) {
    assert(v1.size() == v2.size());
    vector<double> result;
    result.resize(v1.size());
    for(size_t i = 0; i < v1.size(); i++) {
        result[i] = v1[i] - v2[i];
    }
    return result;
}