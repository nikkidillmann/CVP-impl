#include "src/lll_algorithm.h"

void one_dim();
void two_dim();
void three_dim();
void three_dim_red();
void print_lat(vector<vector<double>> &lat);
bool check_reduced(vector<vector<double>> &lat);

int main(int argc, char** argv) {
    one_dim();
    two_dim();
    three_dim();
    three_dim_red();
}

void one_dim() {
    vector<double> b1 = {1};
    vector<vector<double>> lattice;
    lattice.push_back(b1);
    lattice = LLL::lll_reduce(lattice);
    vector<vector<double>> correct = {{1}};
    assert(lattice == correct);
    cout << "PASSED!\n";
}

void two_dim() {
    vector<vector<double>> lattice = {{1,0},{0,1}};
    vector<vector<double>> correct = lattice;
    lattice = LLL::lll_reduce(lattice);
    assert(lattice == correct);
    cout << "PASSED!\n";
}

void three_dim() {
    vector<vector<double>> lattice = {{1,1,1}, {-1,0,2}, {3,5,6}};
    lattice = LLL::lll_reduce(lattice);
    assert(check_reduced(lattice));
    cout << "PASSED!\n";
}

void three_dim_red() {
    vector<vector<double>> lattice = {{0,1,0}, {1,0,1}, {-1,0,2}};
    lattice = LLL::lll_reduce(lattice);
    assert(check_reduced(lattice));
    cout << "PASSED!\n";
}

void print_lat(vector<vector<double>> &lat) {
    for(size_t i = 0; i < lat.size(); i++) {
        for(size_t j = 0; j < lat[0].size(); j++) {
            cout << lat[i][j] << " ";
        }
        cout << "\n";
    }
}

bool check_reduced(vector<vector<double>> &lat) {
    // Lovasz condition
    vector<vector<double>> gs_reduced = LLL::gram_schmidt(lat);
    for(size_t i = 0; i < lat.size()-1; i++) {
        double lhs = (.75) * pow(VectorOps::length(gs_reduced[i]), 2);
        double coeff = LLL::gs_coefficient(lat[i], gs_reduced[i+1]);
        vector<double> scaled = VectorOps::scale(gs_reduced[i], coeff);
        vector<double> comp = VectorOps::add_vectors(scaled, gs_reduced[i+1]);
        double rhs = pow(VectorOps::length(comp), 2);
        if(lhs > rhs) {  
            return false;
        }
    }
    // size_reduced
    for(size_t i = 0; i < lat.size() - 1; i++) {
        for(size_t j = i +1; j < lat.size(); j++) {
            if(LLL::gs_coefficient(lat[i], gs_reduced[j]) > .5) return false;
        }
    }
    return true;
}