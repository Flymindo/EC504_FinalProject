#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;


#define maxnodes 200000
#define SIGMA 30
#define SQUARE(X) X*X

struct node{
   struct arc *first; /* first arc in linked list */
   int D;  /* Distance estimate */
   int P;  /* Predecessor node in shortest path */
   double pixel;  /* Position of node in heap, from 1 to Nm, where 1 is best */
   };

struct arc{
  struct arc *next;
  double capacity;
  int end [2];
  };


double penalty(double a, double b);





int main(int argc, char *argv[]){
    
    ifstream inFile;
    double data;
    struct arc *edge, test;
    struct node src,term;
    
    int height;
    int width;
    
    
    
    inFile.open("imageSize.txt");
    inFile>> height;
    inFile>> width;
    inFile.close();
    
    
    
    struct node Graph[height+1][width+1];
    int count_col=0;
    int count_row=0;
    
    
    inFile.open("image.txt");
    
    while(inFile >> data){
        Graph[count_row][count_col].first = NULL;
        Graph[count_row][count_col].D = count_row;
        Graph[count_row][count_col].P = count_col;
        Graph[count_row][count_col].pixel = data;
        
        count_col++;
        if (count_col == width){
            count_col = 0;
            count_row +=1;
        }
    
        
    }
    inFile.close();
    
    double bp;
    
    for (int i=0; i< height; i++){
        for (int j=0; j<width; j++){
            if (i-1 >= 0){
                bp = penalty(Graph[i][j].pixel, Graph[i-1][j].pixel);
                edge = (struct arc *)malloc(sizeof(test));
                edge->capacity = bp; edge->end[0] = i-1; edge->end[1] =j;
                edge->next = Graph[i][j].first;
                Graph[i][j].first=edge;
            }
            if (i+1 < height){
                bp = penalty(Graph[i][j].pixel, Graph[i+1][j].pixel);
                edge = (struct arc *)malloc(sizeof(test));
                edge->capacity = bp; edge->end[0] = i+1; edge->end[1] = j;
                edge->next = Graph[i][j].first;
                Graph[i][j].first=edge;
            }
            if (j-1 >= 0){
                bp = penalty(Graph[i][j].pixel, Graph[i][j-1].pixel);
                edge = (struct arc *)malloc(sizeof(test));
                edge->capacity = bp; edge->end[0]= i; edge->end[1] = j-1;
                edge->next = Graph[i][j].first;
                Graph[i][j].first=edge;
            }
            if (j+1 < width){
                bp = penalty(Graph[i][j].pixel, Graph[i][j+1].pixel);
                edge = (struct arc *)malloc(sizeof(test));
                edge->capacity = bp; edge->end[0] = i; edge->end[1] = j+1;
                edge->next = Graph[i][j].first;
                Graph[i][j].first=edge;
            }
        }
    }
    
//    while(Graph[1][1].first){
//        cout << Graph[1][1].first->end[0] << "   ";
//        cout << Graph[1][1].first->end[1] << "   " << Graph[1][1].first->capacity << endl;
//        Graph[1][1].first = Graph[1][1].first->next;
//    }
    
    inFile.open("foreground.txt");

    for (int i=0; i< height; i++){
        for (int j=0; j<width; j++){
            inFile >> data;
            edge = (struct arc *)malloc(sizeof(test));
            edge->capacity = data; edge->end[0] =i; edge->end[1] = j;
            edge->next = src.first;
            src.first=edge;
            
        }
    }
    inFile.close();
    
    inFile.open("background.txt");
    
    //Graph[height][width] == Term
    for (int i=0; i< height; i++){
        for (int j=0; j<width; j++){
            inFile >> data;
            edge = (struct arc *)malloc(sizeof(test));
            edge->capacity = data; edge->end[0] = height; edge->end[1] = width;
            edge->next = Graph[i][j].first;
            Graph[i][j].first=edge;
            
        }
    }
    inFile.close();
    
//    for (int i=0; i< height; i++){
//        for (int j=0; j<width; j++){
//            cout << Graph[i][j].first->end[0] << "    " << Graph[i][j].first->end[1] << endl;
//        }
//    }


    
    
    

}

double penalty(double a, double b) {
//    cout << 100 * exp(-SQUARE((double)a - (double)b)) / (2 * SQUARE(SIGMA)) << endl;
//    return 100 * exp(-SQUARE((int)a - (int)b)) / (2 * SQUARE(SIGMA));
    return 1- SQUARE( ((a-b)/255) );
}
