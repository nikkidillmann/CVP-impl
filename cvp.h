#ifndef CVP_H
#define CVP_H

#include <iostream>
#include <vector>
#include <vector>
#include <string>
#include <cassert>
#include <math.h>

using namespace std; 

class CVP {
public:
    vector<vector<double>> lattice;
    vector<vector<double>> lll_reduced;
    vector<double> target;
    vector<vector<double>> relevant_vecs;

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