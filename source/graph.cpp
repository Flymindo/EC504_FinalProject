#include "graph.h" 
#include <vector>
#include <cmath>

#define SQUARE(X) X*X
#define SIGMA 30
#define OBJCODE 1
#define BKGCODE 2
#define SOURCE -2 
#define SINK -1 

using namespace std;

double penalty(double a, double b) {
    return 100 * exp(-SQUARE((int)a - (int)b)) / (2 * SQUARE(SIGMA)); 
}

double buildSpatialGraph(const vector<vector<double>>& image, vector<vector<double>>& graph) {
    int rows = image.size();
    int cols = image[0].size();
    double x = 0;
    double y = 0;
    double K = 0;
    double bp = 0;

    for (int i=0; i<image.size(); i++) {
        for (int j=0; j<image[0].size(); j++) {
            x = i * cols + j;
            if (i + 1 < rows) {
                y = (i + 1) * cols + j;
                bp = penalty(image[i][j], image[i + 1][j]);
                graph[x][y] = graph[y][x] = bp;
                K = max(K, bp);
            }
            if (j + 1 < cols) {
                y = i * cols + j + 1;
                bp = penalty(image[i][j], image[i][j + 1]);
                graph[x][y] = graph[y][x] = bp;
                K = max(K, bp);
            }

        }
    }

    return K;
}

void buildSourceSink(vector<vector<double>>& graph, const vector<vector<int>>& seeds, int K) {
    int r = seeds.size();
    int c = seeds[0].size();
    double x = 0;

    for (int i=0; i<r; i++) {
        for (int j=0; j<c; j++) {
            x = i * c + j;
            if (seeds[i][j] == OBJCODE) {
                graph[r+SOURCE][x] = K;
            }
            else if (seeds[i][j] == BKGCODE) {
                graph[x][c+SINK] = K;
            }
        }
    }
}