#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

typedef struct {
	double ** matrix;
	int cols;
	int rows;
} matrix;

extern matrix load_matrix(std::string path);
extern matrix create_matrix(int rows, int cols);
extern double norm(matrix m1, matrix m2);

int main(int argc, char ** argv) {
    matrix m1, m2;
    double result;
    
    if(argc != 3) {
		std::cout << "error: input parameters are matrix1 matrix2" << std::endl;
		exit(0);
	}

    m1 = load_matrix(argv[1]);
    m2 = load_matrix(argv[2]);

    result = norm(m1, m2);
    std::cout << std::setprecision(14) << result << endl;
}

/**
 * Load a matrix from file
 **/
matrix load_matrix(std::string path) {
	matrix m;
	fstream file; 
	int rows;
	int cols;

	file.open(path, ios::in);

	// Read the matrix dimensions and create matrix
	file >> rows;
	file >> cols;
	m = create_matrix(rows, cols);

	for(int i = 0; i<rows; i++)
		for(int j = 0; j<cols; j++)
			file >> m.matrix[i][j];
            
	file.close();
	return m;
}

/**
 * Create and zero initialize a matrix of size rows x cols
 **/
matrix create_matrix(int rows, int cols) {
	matrix m;

	m.matrix = new double*[rows];
	m.cols = cols;
	m.rows = rows;

	for(int i = 0; i<rows; i++)
		m.matrix[i] = new double[cols];

	for(int i = 0; i < rows; i++)
		for(int j = 0; j < cols; j++)
			m.matrix[i][j] = 0;

	return m;
}

double norm(matrix m1, matrix m2){
    double sum;

    sum = 0.0;

    for(int i = 0; i<m1.rows; i++)
        for(int j = 0; j<m1.cols; j++)
            sum += pow(m1.matrix[i][j] - m2.matrix[i][j], 2);

    return sqrt(sum);
}