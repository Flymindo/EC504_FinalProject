#include <iostream>
#include <fstream>

using namespace std;


#define maxnodes 200000

struct node{
   struct arc *first; /* first arc in linked list */
   int D;  /* Distance estimate */
   int P;  /* Predecessor node in shortest path */
   float pixel;  /* Position of node in heap, from 1 to Nm, where 1 is best */
   };

struct arc{
  struct arc *next;
  float capacity;
  int end;
  };


int height;
int width;


int main(int argc, char *argv[]){
    
    ifstream inFile;
    float data;
    struct arc *edge, test;
    struct node s,t;
    
    
    
    inFile.open("imageSize.txt");
    inFile>> height;
    inFile>> width;
    inFile.close();
    
    
    
    struct node Graph[height][width];
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
//    cout << Graph[0][1].pixel << endl;
    inFile.close();
    
    inFile.open("foreground.txt");
    // 0 => foreground
    count_col=0;
    count_row=0;
    while(inFile >> data){
        edge = (struct arc *)malloc(sizeof(test));
        edge->capacity = data; edge->end = 0;
        edge->next = Graph[count_row][count_col].first;
        Graph[count_row][count_col].first=edge;
        
        count_col++;
        if (count_col == width){
            count_col = 0;
            count_row +=1;
        }
    }
    cout << Graph[0][1].first->capacity << endl;
    
    inFile.close();
    
    
    
  

}
