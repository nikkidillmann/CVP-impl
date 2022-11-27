#include "lll_algorithm.h"

void one_dim();
void two_dim();
void three_dim();
void three_dim_red();
void print_lat(vector<vector<double>> &lat);

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
    vector<vector<double>> correct = {{0,1,0}, {1,0,1}, {-1,0,2}};
    lattice = LLL::lll_reduce(lattice);
    print_lat(lattice);
}

void three_dim_red() {
    vector<vector<double>> correct = {{0,1,0}, {1,0,1}, {-1,0,2}};
    vector<vector<double>> lattice = correct;
    lattice = LLL::lll_reduce(lattice);
    print_lat(lattice);
}

void print_lat(vector<vector<double>> &lat) {
    for(size_t i = 0; i < lat.size(); i++) {
        for(size_t j = 0; j < lat[0].size(); j++) {
            cout << lat[i][j] << " ";
        }
        cout << "\n";
    }
}