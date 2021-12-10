#include "graph.h"

using namespace std;

#define SIGMA 30
#define SQUARE(X) ((X)*(X))

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

int bfs(node sNode,node Graph[][10000], int height, int width)
{
    queue<node> q;//declare queue vector
    q.push(Graph[height-1][width]);

    
    for (int i=0; i< height; i++){
        for (int j=0; j<width; j++){
            Graph[i][j].wentThrough = NULL;
            Graph[i][j].prev[0] = -1;
            Graph[i][j].prev[1] = -1;
            Graph[i][j].flow = 0;
        }
    }
    
    Graph[height][width].wentThrough = NULL;
    Graph[height][width].prev[0] = -1;
    Graph[height][width].prev[1] = -1;
    Graph[height][width].flow = 0;

    int toGo[2];
    int flowPassed = 0;
    int C; //Capacity
    int maxFlow;
    arc* temp;

    while(!q.empty())// if q is not empty
    {
        node currNode = q.front();
        q.pop();
        
        temp = currNode.first;
        while(temp){
            toGo[0] = temp->end[0];
            toGo[1] = temp->end[1];
            C = temp->capacity;
            if (C >0){
                if ( Graph[toGo[0]][toGo[1]].prev[0] == -1 && Graph[toGo[0]][toGo[1]].prev[1] == -1){
                    Graph[toGo[0]][toGo[1]].prev[0] =currNode.curr[0];
                    Graph[toGo[0]][toGo[1]].prev[1] =currNode.curr[1];
                    Graph[toGo[0]][toGo[1]].wentThrough = temp;
                                        
                    maxFlow = min(C, currNode.flow);
                    Graph[toGo[0]][toGo[1]].flow = maxFlow;

                    if(toGo[0] == height && toGo[1] == width){
                        return maxFlow;
                    }
                    q.push(Graph[toGo[0]][toGo[1]]);

                }
            }
            temp = temp->next;
        }
    }
    return 0;
}

int edmondsKarp(node sNode,node Graph[][10000], int height, int width)
{
    ofstream outFile;
    
    int maxFlow = 0;
    int x;
    int y;
    int count;
    while(true)
    {
        int flow = bfs(sNode,Graph, height, width);
//        cout << flow << endl;
        if (flow == 0)
        {
            break;
        }
        
        maxFlow += flow;
//        cout << maxFlow << endl;

        node temp = Graph[height][width];
        

        while(true)
        {
            x =temp.prev[0];
            y =temp.prev[1];
            
            temp.wentThrough->capacity -= flow;
            temp.wentThrough->neigh->capacity -= flow;

            if (x == height-1 && y == width){
                
                break;
            }
            temp = Graph[x][y];
        }
        
    }
    
    outFile.open("data/result.txt");
    
    
    for (int i=0; i<height;i++){
        for (int j=0; j<width; j++){
            if (Graph[i][j].prev[0] == -1 && Graph[i][j].prev[1] == -1){
                outFile << 0 << " ";
            }
            else{
                outFile << 1 << " ";
            }

        }
        outFile << endl;
    }
    outFile.close();
    
    return maxFlow;
}

int penalty(double a, double b) {
    return (int)100 * exp( (-1 * (a - b)*(a-b)) / (2 * SIGMA * SIGMA) );
}
