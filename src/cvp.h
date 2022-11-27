#ifndef CVP_H
#define CVP_H

#include <iostream>
#include <vector>
#include <vector>
#include <string>
#include <cassert>
#include <math.h>

using namespace std; 

// I think we might need to switch to long long for our data types because of
// precision?
class CVP {
public:
    // Maybe we can just reduce the lattice itself?
    // Think it might speed up our algorithm
    
    // vector<vector<double>> lll_reduced;

    // Basis vectors
    vector<vector<double>> lattice;
    
    // Relevant vectors of voronoi cell
    // vector<vector<double>> relevant_vecs;
    
    vector<double> target;
    
    CVP(vector<vector<double>> &l, vector<double> &t)
        : lattice(l), target(t) {}

    vector<double> closest_vector();

private:
    // returns relevant vectors of the Voronoi cell
    vector<vector<double>> preprocess();

    // performs one phase of the "walk"
    vector<double> walk_phase(vector<double> &curr_target);

    // checks if curr_target is in scaled voronoi cell
    bool in_cell(vector<double> &curr_target, int scaling);

    // returns scaling of relevant_vecs
    vector<vector<double>> scaled_cell(int scaling);

    // returns the vector v in the scaled Voronoi cell that maximizes <v,t>/<v,v>
    static vector<double> maximize_ratio(vector<double> &curr_target, int scaling);
};

#endif // CVP_H
