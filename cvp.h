#ifndef CVP_H
#define CVP_H

#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std; 

class CVP {
public:
    set<vector<double>> lattice;
    vector<double> target;

    // returns relevant vectors of the Voronoi cell
    set<vector<double>> preprocess();

    // performs one phase of the "walk"
    vector<double> walk_phase(vector<double> curr_target);

private:

};

#endif // CVP_H