#ifndef GRAPH_H
#define GRAPH_H

/* utility for writing adjacency matrix to space delimited text file */
void matrix2file(vector<vector<double>> graph, const char* fname);

/* calculates inter-pixel weights according to Boykov et al. "Graph cuts and efficient ND image segmentation" .*/
double penalty(double a, double b);

/* builds the image graph */
double buildSpatialGraph(const vector<vector<double>>& image, vector<vector<double>>& graph);

/* builds source and sinks graph */
void buildSourceSink(vector<vector<double>>& graph, const vector<vector<int>>& seeds, int K);

#endif