#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <queue>


using namespace std;

#define SIGMA 30
#define SQUARE(X) X*X

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

int height;
int width;

//vector< vector<node> > Graph;
struct node Graph[10000][10000];


int penalty(double a, double b);
int bfs(node src,node Graph[][10000]);
int edmondsKarp(node sNode,node Graph[][10000]);


int main(int argc, char *argv[]){

    ifstream inFile;
//    ofstream outFile;
    
    double data;
    struct arc *edgeTo, *edgeFrom, test;
    struct node src,term;


    inFile.open("imageSize.txt");
    inFile>> height;
    inFile>> width;
    inFile.close();

//    int size = height*width;


//    struct node Graph[height+1][width+1];

    inFile.open("image.txt");
    
    for (int i=0; i< height; i++){
        for (int j=0; j<width; j++){
            Graph[i][j].first = NULL;
            Graph[i][j].wentThrough = NULL;
            Graph[i][j].flow = 0;
            Graph[i][j].prev[0] = -1;
            Graph[i][j].prev[1] = -1;
            Graph[i][j].curr[0] = i;
            Graph[i][j].curr[1] = j;
            Graph[i][j].pixel = data;
        }
    }
    inFile.close();
    
    
    //Terminal
    Graph[height][width].first = NULL;
    Graph[height][width].wentThrough = NULL;
    Graph[height][width].flow = 0;
    Graph[height][width].prev[0] = -1;
    Graph[height][width].prev[1] = -1;
    Graph[height][width].curr[0] = height;
    Graph[height][width].curr[1] = width;
    Graph[height][width].pixel = 0;
    //Source
    src.first = NULL;
    src.wentThrough = NULL;
    src.curr[0] = height-1;
    src.curr[1] = width;
    src.prev[0] = height-1;
    src.prev[1] = width;
    Graph[height-1][width] = src;
    


    int bp;

    for (int i=0; i< height; i++){
        for (int j=0; j<width; j++){
            if (i-1 >= 0){
                bp = penalty(Graph[i][j].pixel, Graph[i-1][j].pixel);
                edgeTo = (struct arc *)malloc(sizeof(test));
                edgeTo->capacity = bp; edgeTo->end[0]= i-1; edgeTo->end[1] = j;
                edgeTo->next = Graph[i][j].first;
                Graph[i][j].first=edgeTo;
                
                edgeFrom = (struct arc *)malloc(sizeof(test));
                edgeFrom->capacity = bp; edgeFrom->end[0]= i; edgeFrom->end[1] = j;
                edgeFrom->next = Graph[i-1][j].first;
                Graph[i-1][j].first = edgeFrom;
                edgeTo->neigh = edgeFrom;
                edgeFrom->neigh = edgeTo;
            }
            if (j-1 >= 0){
                bp = penalty(Graph[i][j].pixel, Graph[i][j-1].pixel);
                edgeTo = (struct arc *)malloc(sizeof(test));
                edgeTo->capacity = bp; edgeTo->end[0]= i; edgeTo->end[1] = j-1;
                edgeTo->next = Graph[i][j].first;
                Graph[i][j].first=edgeTo;
                
                edgeFrom = (struct arc *)malloc(sizeof(test));
                edgeFrom->capacity = bp; edgeFrom->end[0]= i; edgeFrom->end[1] = j;
                edgeFrom->next = Graph[i][j-1].first;
                Graph[i][j-1].first = edgeFrom;
                edgeTo->neigh = edgeFrom;
                edgeFrom->neigh = edgeTo;
            }

        }
    }
    

    inFile.open("foreground.txt");

    for (int i=0; i< height; i++){
        for (int j=0; j<width; j++){
            inFile >> data;
            edgeTo = (struct arc *)malloc(sizeof(test));
            edgeTo->capacity = (int) 100* data; edgeTo->end[0] =i; edgeTo->end[1] = j;
            edgeTo->neigh = NULL;
            edgeTo->next = Graph[height-1][width].first;
            Graph[height-1][width].first=edgeTo;
            
            edgeFrom = (struct arc *)malloc(sizeof(test));
            edgeFrom->capacity = 0; edgeFrom->end[0]= height-1; edgeFrom->end[1] = width;
            edgeFrom->next = Graph[i][j].first;
            Graph[i][j].first = edgeFrom;
            edgeTo->neigh = edgeFrom;
            edgeFrom->neigh = edgeTo;
        }
    }
    inFile.close();

    inFile.open("background.txt");
    
//    int count=0;
//    //end[] = [-1,-1] == sink
    for (int i=0; i< height; i++){
        for (int j=0; j<width; j++){
            inFile >> data;
            edgeTo = (struct arc *)malloc(sizeof(test));
            edgeTo->capacity = (int) 100 * data; edgeTo->end[0] = height; edgeTo->end[1] = width;
            edgeTo->next = Graph[i][j].first;
            Graph[i][j].first=edgeTo;
            
            edgeFrom = (struct arc *)malloc(sizeof(test));
            edgeFrom->capacity = 0; edgeFrom->end[0]= height; edgeFrom->end[1] = width;
            edgeFrom->next = Graph[i][j].first;
            Graph[i][j].first = edgeFrom;
            edgeTo->neigh = edgeFrom;
            edgeFrom->neigh = edgeTo;
            
//            count += (int) 100 * data;

        }
    }
    inFile.close();
//    cout << count << endl;
    


    // From Here, Min Cut Goes in
    cout << edmondsKarp(src,Graph) << endl;

    
    
    
 
    
    return 0;
}


int bfs(node sNode,node Graph[][10000])
{
//   memset(parList, -1, sizeof(parList));
//   memset(currentPathC, 0, sizeof(currentPathC));
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
//    Graph[height-1][width].wentThrough = NULL;
//    Graph[height-1][width].prev[0] = height-1;
//    Graph[height-1][width].prev[1] = width;
//    Graph[height-1][width].flow = 0;
    
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
//        cout << "I'm in" << endl;
        node currNode = q.front();
        q.pop();
//        cout <<currNode.curr[0] << "   " << currNode.curr[1] << endl;
        
        temp = currNode.first;
//        cout << temp->capacity << endl;
        while(temp){
            toGo[0] = temp->end[0];
            toGo[1] = temp->end[1];
//            cout << toGo[0] << "   " << toGo[1] << endl;
            C = temp->capacity;
            if (C >0){
                if ( Graph[toGo[0]][toGo[1]].prev[0] == -1 && Graph[toGo[0]][toGo[1]].prev[1] == -1){
//                    cout << "I'm in" << endl;
                    Graph[toGo[0]][toGo[1]].prev[0] =currNode.curr[0];
                    Graph[toGo[0]][toGo[1]].prev[1] =currNode.curr[1];
                    Graph[toGo[0]][toGo[1]].wentThrough = temp;
                    
//                        cout << Graph[toGo[0]][toGo[1]].wentThrough->capacity  << endl;
                    
                    maxFlow = min(C, currNode.flow);
                    Graph[toGo[0]][toGo[1]].flow = maxFlow;
//
                    if(toGo[0] == height && toGo[1] == width){
//                        cout <<currNode.curr[0] << "   " << currNode.curr[1] << endl;
//                        cout << maxFlow << endl;
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

int edmondsKarp(node sNode,node Graph[][10000])
{
    ofstream outFile;
    
    int maxFlow = 0;
    int x;
    int y;
    int count;
    while(true)
    {
        int flow = bfs(sNode,Graph);
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
//            temp.wentThrough->neigh->capacity -= flow;
//            cout << temp.curr[0] << "   " << temp.curr[1] <<  "   "<< temp.wentThrough->capacity <<endl;
//            cout << temp.curr[0] << "   " << temp.curr[1] <<  "   "<< temp.wentThrough->neigh->capacity <<endl;
            if (x == height-1 && y == width){
                
                break;
            }
            temp = Graph[x][y];
        }
        
    }
    
    outFile.open("result.txt");
    
    
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
//    cout << 100 * exp(-SQUARE((double)a - (double)b)) / (2 * SQUARE(SIGMA)) << endl;
    return (int)100 * exp( (-1 * (a - b)*(a-b)) / (2 * SIGMA * SIGMA) );
//    return (int) 100 * (1- SQUARE( ((a-b)/255) ));
//    return abs(a-b);
    
}
