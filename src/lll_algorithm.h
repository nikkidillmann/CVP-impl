#ifndef LLL_ALGORITHM_H
#define LLL_ALGORITHM_H

#include <iostream>
#include <vector>
#include <vector>
#include <string>
#include <cassert>
#include <math.h>

using namespace std; 

class LLL {
public:

    // Does static make the code faster? - Daniel
    
    // returns the Euclidean distance between v1 and v2
    static vector<vector<double>> lll_reduce(vector<vector<double>& to_reduce);

    static vector<vector<double>> gram_schmidt(vector<vector<double>& in);

    static vector<vector<double> size_reduce(vector<vector<double>& in);

    // computes <v1, v2> / <v2, v2>
    static double gs_coefficient(vector<double> &v1, vector<double> &v2);

};

#endif // LLL_ALGORITHM_H
