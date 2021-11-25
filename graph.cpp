#include <iostream>
#include <fstream>

using namespace std;


float Na,Nm,Or;
int maxnodes = 200000;

struct node{
   struct arc *first; /* first arc in linked list */
   int D;  /* Distance estimate */
   int P;  /* Predecessor node in shortest path */
   int Q;  /* Position of node in heap, from 1 to Nm, where 1 is best */
   };

struct node Nodes[maxnodes];

int height = 240;
int width = 180;


int main(int argc, char *argv[]){
//    int V;
//    int E;
////    char *infile;
//    FILE *fp1,*fpout;
    
    ifstream inFile;
    float data;
    int count = 1;
    
    inFile.open("image.txt");
    
    while(inFile >> data){
        Nodes[count].
        
        count++;
        
    }
    cout << count << endl;
    
    inFile.close();
    

}
