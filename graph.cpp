#include <iostream>
#include <fstream>

using namespace std;


#define maxnodes 200000

struct node{
   struct arc *first; /* first arc in linked list */
   int D;  /* Distance estimate */
   int P;  /* Predecessor node in shortest path */
   int Q;  /* Position of node in heap, from 1 to Nm, where 1 is best */
   };


int height;
int width;


int main(int argc, char *argv[]){
    
    ifstream inFile;
    float data;
    
    
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
        Graph[count_row][count_col].Q = 0;
        
        count_col++;
//        cout << count_row << endl;
        
        if (count_col == width){
            count_col = 0;
            count_row +=1;
        }
    
        
    }
    inFile.close();
    
    
    cout << Graph[2][55].D << "    " << Graph[2][55].P << endl;
    cout << Graph[23][10].D << "   "  << Graph[23][10].P << endl;
    cout << Graph[239][179].D << "   "  << Graph[239][179].P << endl;
    
    

  

}
