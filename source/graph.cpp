#include "graph.h" 
#include <vector>
#include <cmath>

#define SQUARE(X) X*X
#define SIGMA 30

using namespace std;

double penalty(double a, double b) {
    return 100 * exp(-SQUARE((int)a - (int)b)) / (2 * SQUARE(SIGMA)); 
}

vector<vector<double>> buildGraph(vector<vector<double>> image) {
    vector<vector<double>> graph;
    for (int i=0; i<image.size(); i++) {
        for (int j=0; j<image[0].size(); j++) {

        }
    }

    return graph;
}

