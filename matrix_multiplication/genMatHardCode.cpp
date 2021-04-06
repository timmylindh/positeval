#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>

using namespace std;

typedef struct {
    float **matrix;
    int cols;
    int rows;
} matrix;

int range, matSize;

matrix m;

void createMatrix();
float randVal();
void printMatrix(string fileName);


int main(int argc, char* args[]){
    matrix m;
    range= stoi(args[1]); //range
    matSize = stoi(args[2]);
    string fileName = args[3];
    srand(time(NULL));

    for(int i = 0; i<5; i++){
        createMatrix();
        printMatrix(fileName + i);
    }



    return 0; 

}

void createMatrix(){

    m.matrix = new float*[matSize];
	m.cols = matSize;
	m.rows = matSize;

    for(int i = 0; i<m.cols; i++){
        m.matrix[i] = new float[matSize];
        for(int j = 0; j<matSize; j++ ){
            m.matrix[i][j] = randVal();
        }
    }

}

float randVal(){
    return (-range) + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2*range))); 
}

void printMatrix(string fileName){
    std::ofstream printer;
    printer.open("matrices/in/" + fileName, ios::out);
    printer << matSize << " ";
    printer << matSize << endl;
     for(int i = 0; i<matSize; i++){
        for(int j = 0; j<matSize; j++ ){
            printer << std::setprecision(14) << m.matrix[i][j] << " ";
        }
        printer << endl;
    }
    printer.close();
}