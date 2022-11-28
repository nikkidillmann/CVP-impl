#ifndef VORONOI_H
#define VORONOI_H

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <math.h>
#include <climits>

using namespace std;


class Voronoi {
public:
    // return the Voronoi relevant vectors for the lattice defined by basis in
    vector<vector<double>> voronoi_cell(vector<vector<double>> &in);

private:
    // assumes basis is an LLL reduced basis
    vector<double> rank_reduce(vector<double> &target,
                               vector<vector<double>> &basis,
                               vector<vector<double>> vor, int h);

    void find_relevant(vector<vector<double>> &in,
                       vector<vector<double>> v_partial);

    void remove_non_relevant();

    vector<vector<double>> compute_cell(vector<vector<double>> &curr_basis,
                      vector<vector<double>> &v, double scale);
};

#endif // VORONOI_H
