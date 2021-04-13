#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <random>

using namespace std;

typedef struct {
    float **matrix;
    int cols;
    int rows;
} matrix;

double range;
int matSize;

matrix m;

void createMatrix();
float randVal();
void printMatrix(string fileName);

std::default_random_engine * generator;
std::uniform_real_distribution<double> * double_generator;

int main(int argc, char* args[]){
    matrix m;
    range= stod(args[1]); //range
    matSize = stoi(args[2]);
    string fileName = args[3];
    srand(time(NULL));

    // construct a trivial random generator engine from a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator = new std::default_random_engine(seed);

    double_generator = new std::uniform_real_distribution<double>((double) -1 * range, (double) range);

    createMatrix();
    printMatrix(fileName);

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
    return (*double_generator)(*generator);
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