#ifndef GRAPH_H
#define GRAPH_H

/* namespace variables */

using namespace std;

/* macro definitions */

#define SIGMA 30
#define SQUARE(X) ((X)*(X))

/* struct definitions */

struct node{
    struct arc *first; /* first arc in linked list */
    int flow;  /* Distance estimate */
//    struct node *P;  /* Predecessor node in shortest path */
    int curr[2];
    int prev[2];  /* Predecessor node in shortest path */
    struct arc *wentThrough;
    double pixel;  /* Position of node in heap, from 1 to Nm, where 1 is best */
};

struct arc{
    struct arc *next;
    int capacity;
    struct arc *neigh;
    int end [2];
};

/* function definitions */

int bfs(node sNode,node Graph[][10000]);

int edmondsKarp(node sNode,node Graph[][10000]);

int penalty(double a, double b);

#endif