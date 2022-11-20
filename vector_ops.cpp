#include "vector_ops.h"


double VectorOps::distance(vector<double> &v1, vector<double> &v2) {
    assert(v1.size() == v2.size());
    double running_sum = 0;
    for(size_t i = 0; i < v1.size(); i++) {
        running_sum += pow((v1[i] - v2[i]), 2);
    }
    return sqrt(running_sum);
}

double VectorOps::length(vector<double> &v1) {
    double running_sum = 0;
    for(size_t i = 0; i < v1.size(); i++) {
        running_sum += pow(v1[i], 2);
    }
    return sqrt(running_sum);
}

double VectorOps::inner_product(vector<double> &v1, vector<double> &v2) {
    assert(v1.size() == v2.size());
    double running_sum = 0;
    for(size_t i = 0; i < v1.size(); i++) {
        running_sum += v1[i]*v2[i];
    }
}

vector<double> VectorOps::scale(vector<double> &v, double scaling) {
    vector<double> vec = v;
    std::for_each(vec.begin(), vec.end(), [scaling](auto &elem) { elem *= scaling; })
    return vec;
}

vector<double> VectorOps::subtract_vectors(vector<double> &v1, vector<double> &v2) {
    assert(v1.size() == v2.size());
    vector<double> result;
    result.resize(v1.size());
    for(size_t i = 0; i < v1.size(); i++) {
        result[i] = v1[i] - v2[i];
    }
    return result;
}

vector<double> VectorOps::add_vectors(vector<double> &v1, vector<double> &v2) {
    assert(v1.size() == v2.size());
    vector<double> result;
    result.resize(v1.size());
    for(size_t i = 0; i < v1.size(); i++) {
        result = v1[i] + v2[i];
    }
    return result;
}