#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <stdlib.h>
#include <math.h>
using namespace std;



typedef struct {
    float **matrix;
    int cols;
    int rows;
} matrix;

int from, to, matSize;
string fileName;
matrix mat;
int main(int argc, char* args[]){

    from = stoi(args[1]); //range
    to = stoi(args[2]);
    matSize = stoi(args[3]);
    fileName = args[4];


    createMatrix();
    printMatrix();

    return 0; 

}

void createMatrix(){
    for(int i = 0; i<matSize; i++){
        for(int j = 0; j<matSize; j++ ){
            
        }
    }
}