#ifndef CVP_H
#define CVP_H

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <cassert>
#include <math.h>

using namespace std; 

class CVP {
public:
    set<vector<double>> lattice;
    vector<double> target;
    set<vector<double>> relevant_vecs;

    vector<double> closest_vector();

private:
    // returns relevant vectors of the Voronoi cell
    set<vector<double>> preprocess();

    // performs one phase of the "walk"
    vector<double> walk_phase(vector<double> &curr_target);

    // checks if curr_target is in scaled voronoi cell
    bool in_cell(vector<double> &curr_target, int scaling);

    // returns scaling of relevant_vecs
    vector<double> scaled_vec(int scaling);
    
    // returns the Euclidean distance between v1 and v2
    double distance(vector<double> &v1, vector<double> &v2);

    // returns the inner product of v1 and v2
    double inner_product(vector<double> &v1, vector<double> &v2);

    // returns the vector v in the scaled Voronoi cell that maximizes <v,t>/<v,v>
    vector<double> maximize_ratio(vector<double> &curr_target, int scaling);

    // returns v1 - v2
    vector<double> subtract_vectors(vector<double> &v1, vector<double> &v2);

};

#endif // CVP_H