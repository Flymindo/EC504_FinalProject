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
    int P[2];  /* Predecessor node in shortest path */
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

vector< vector<node> > Graph;


int penalty(double a, double b);


int main(int argc, char *argv[]){

    ifstream inFile;
    
    double data;
    struct arc *edgeTo, *edgeFrom, test;
    struct node src,term;
    src.first = NULL;

//    int height;
//    int width;



    inFile.open("imageSize.txt");
    inFile>> height;
    inFile>> width;
    inFile.close();

    int size = height*width;


//    struct node Graph[height][width];
    int count_col=0;
    int count_row=0;


    inFile.open("image.txt");

    while(inFile >> data){
        Graph[count_row][count_col].first = NULL;
        Graph[count_row][count_col].flow = 0;
        Graph[count_row][count_col].P[0] = -1;
        Graph[count_row][count_col].P[1] = -1;
        Graph[count_row][count_col].pixel = data;

        count_col++;
        if (count_col == width){
            count_col = 0;
            count_row +=1;
        }


    }
    inFile.close();
    
    


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
//            if (i+1 < height){
//                bp = penalty(Graph[i][j].pixel, Graph[i+1][j].pixel);
//                edge = (struct arc *)malloc(sizeof(test));
//                edge->capacity = bp; edge->end[0] = i+1; edge->end[1] = j;
//                edge->next = Graph[i][j].first;
//                Graph[i][j].first=edge;
//            }
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
//            if (j+1 < width){
//                bp = penalty(Graph[i][j].pixel, Graph[i][j+1].pixel);
//                edge = (struct arc *)malloc(sizeof(test));
//                edge->capacity = bp; edge->end[0] = i; edge->end[1] = j+1;
//                edge->next = Graph[i][j].first; edge->neigh = Graph[i-1][j];
//                Graph[i][j].first=edge;
//            }
        }
    }
    
    
//    inFile.open("segmented.txt");
//    for (int i=0; i< height; i++){
//        for (int j=0; j<width; j++){
//            inFile >> data;
//            edgeTo = (struct arc *)malloc(sizeof(test));
//            edgeTo->capacity = (int)data;
//            if (data == 0){
//                edgeTo->end[0] = -1; edgeTo->end[1] = -1;
//                edgeTo->next = Graph[i][j].first;
//                Graph[i][j].first=edgeTo;
//            }
//            else{
//                edgeTo->capacity = (int) data; edgeTo->end[0] =i; edgeTo->end[1] = j;
//                edgeTo->next = src.first;
//                src.first=edgeTo;
//            }
//
//        }
//    }
//    inFile.close();

    

    inFile.open("foreground.txt");

    for (int i=0; i< height; i++){
        for (int j=0; j<width; j++){
            inFile >> data;
            edgeTo = (struct arc *)malloc(sizeof(test));
            edgeTo->capacity = (int) 100* data; edgeTo->end[0] =i; edgeTo->end[1] = j;
            edgeTo->neigh = NULL;
            edgeTo->next = src.first;
            src.first=edgeTo;

        }
    }
    inFile.close();

    inFile.open("background.txt");
//
//    //end[] = [-1,-1] == sink
    for (int i=0; i< height; i++){
        for (int j=0; j<width; j++){
            inFile >> data;
            edgeTo = (struct arc *)malloc(sizeof(test));
            edgeTo->capacity = (int) 100 * data; edgeTo->end[0] = -1; edgeTo->end[1] = -1;
            edgeTo->next = Graph[i][j].first;
            Graph[i][j].first=edgeTo;

        }
    }
    inFile.close();
    
//
//    for (int i=0; i< height; i++){
//        for (int j=0; j<width; j++){
//            while(Graph[i][j].first){
////                cout << Graph[i][j].first->end[0] << "   ";
////                cout << Graph[i][j].first->end[1] << "   " << Graph[i][j].first->capacity << "  " << Graph[i][j].first->neigh->end[0] << "    " << Graph[i][j].first->neigh->end[1] << endl;
//                cout << Graph[i][j].first->end[0] << "   ";
//                cout << Graph[i][j].first->end[1] << "   " << Graph[i][j].first->capacity << "  " << endl;
//                Graph[i][j].first = Graph[i][j].first->next;
//            }
//
//        }
//    }
    
    while(src.first){
        cout << src.first->end[0] << "  "<< src.first->end[1] << "   " << src.first->capacity << endl;
        src.first = src.first->next;
    }

    // From Here, Min Cut Goes in
    
}


int bfs(node sNode)
{
//   memset(parList, -1, sizeof(parList));
//   memset(currentPathC, 0, sizeof(currentPathC));
    queue<node> q;//declare queue vector
    q.push(sNode);
//   parList[sNode] = -1;//initialize parlist’s source node
//   currentPathC[sNode] = 999;//initialize currentpath’s source node
    
    int toGo[2];
    int flowPassed = 0;
    int C; //Capacity
    int maxFlow;
    
    while(!q.empty())// if q is not empty
    {
        node currNode = q.front();
        q.pop();
        
        while(currNode.first){
            toGo[0] = currNode.first->end[0];
            toGo[1] = currNode.first->end[1];
            C = currNode.first->capacity;
            
            if (Graph[toGo[0]][toGo[1]].P[0] != -1 && Graph[toGo[0]][toGo[1]].P[1] != -1){
                if (C >0){
                    Graph[toGo[0]][toGo[1]].P[0] = toGo[0];
                    Graph[toGo[0]][toGo[1]].P[1] = toGo[1];
                    maxFlow = min(C, currNode.flow);
                    if(toGo[0] == -1 && toGo[1] == -1){
                        return maxFlow;
                    }
                    q.push(Graph[toGo[0]][toGo[1]]);
                }
                
            }
        }
       
//        for(int i=0; i<g[currNode].size(); i++)
//        {
//         int to = g[currNode][i];
//         if(parList[to] == -1)
//         {
//            if(c[currNode][to] - flowPassed[currNode][to] > 0)
//            {
//               parList[to] = currNode;
//               currentPathC[to] = min(currentPathC[currNode],
//               c[currNode][to] - flowPassed[currNode][to]);
//               if(to == eNode)
//               {
//                  return currentPathC[eNode];
//               }
//               q.push(to);
//            }
//         }
//        }
    }
    return 0;
}

//int edmondsKarp(int sNode, int eNode)
//{
//   int maxFlow = 0;
//   while(true)
//   {
//      int flow = bfs(sNode, eNode);
//      if (flow == 0)
//      {
//         break;
//      }
//      maxFlow += flow;
//      int currNode = eNode;
//      while(currNode != sNode)
//      {
//         int prevNode = parList[currNode];
//         flowPassed[prevNode][currNode] += flow;
//         flowPassed[currNode][prevNode] -= flow;
//         currNode = prevNode;
//      }
//}

int penalty(double a, double b) {
//    cout << 100 * exp(-SQUARE((double)a - (double)b)) / (2 * SQUARE(SIGMA)) << endl;
    return (int)100 * exp( (-1 * (a - b)*(a-b)) / (2 * SIGMA * SIGMA) );
//    return (int) 100 * (1- SQUARE( ((a-b)/255) ));
//    return abs(a-b);
    
}
