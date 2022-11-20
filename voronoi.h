#define VORONOI_H
#ifndef VORNOI_H

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <math.h>

class Voronoi {
public:
    // return the Voronoi relevant vectors for the lattice defined by basis in
    vector<vector<double>> voronoi_cell(vector<vector<double>> &in);

private:
    // assumes basis is an LLL reduced basis
    vector<double> rank_reduce(vector<double> &target, vector<vector<double>> &basis, vector<vector<double>> vor, int h);

    void find_relevant();

    void remove_non_relevant();

    void compute_cell();
}

#endif // VORONOI_H