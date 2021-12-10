#include "main.h"

using namespace std;

struct node Graph[10000][10000];

int main(int argc, char *argv[]){

    ifstream inFile;
//    ofstream outFile;
    
    double data;
    struct arc *edgeTo, *edgeFrom, test;
    struct node src;
    int height, width;


    inFile.open("../data/imageSize.txt");
    inFile>> height;
    inFile>> width;
    inFile.close();

//    int size = height*width;


//    struct node Graph[height+1][width+1];

    inFile.open("../data/image.txt");
    
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
    

    inFile.open("../data/foreground.txt");

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

    inFile.open("../data/background.txt");
    
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
            

        }
    }
    inFile.close();
    


    // From Here, Min Cut Goes in
    cout << "Max Flow = " << edmondsKarp(src,Graph,height,width) << endl;
 
    return 0;
}
