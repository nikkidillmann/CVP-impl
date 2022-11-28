#ifndef VECTOR_OPS_H
#define VECTOR_OPS_H

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <math.h>
n
using namespace std; 

class VectorOps {
public:
    
    // returns the Euclidean distance between v1 and v2
    static double distance(vector<double> &v1, vector<double> &v2);

    // returns the Euclidean norm of v1
    static double length(vector<double> &v1);

    // returns the inner product of v1 and v2
    static double inner_product(vector<double> &v1, vector<double> &v2);

    // scale v by scaling
    static vector<double> scale(vector<double> &v, double scaling);

    // returns v1 - v2
    static vector<double> subtract_vectors(vector<double> &v1,
                                           vector<double> &v2);

    // returns v1 + v2
    static vector<double> add_vectors(vector<double> &v1, vector<double> &v2);

};

#endif // VECTOR_OPS_H
