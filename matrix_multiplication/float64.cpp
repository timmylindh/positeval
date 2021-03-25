#include <iostream>
#include <fstream>
#include <iomanip>

namespace float64 {

typedef struct {
	double ** matrix;
	int cols;
	int rows;
} matrix;

extern matrix matrix_mul(matrix m1, matrix m2);
extern matrix create_matrix(int rows, int cols);
extern matrix load_matrix(std::string path);
extern void print_matrix(matrix m);

using namespace std;

int main() { 
	matrix m1, m2, result;

	m1 = load_matrix("matrices/example.dat");
	m2 = load_matrix("matrices/example2.dat");
	
	result = matrix_mul(m1, m2);
	
	print_matrix(result);
	
	return 0;
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
 * Perform matrix multiplication
 **/
matrix matrix_mul(matrix m1, matrix m2) {
	matrix result;
	int c;
	int rows;
	int cols;

	c = m1.cols; //common dimension 
	rows = m1.rows;
	cols = m2.cols;

	result = create_matrix(cols, rows);

	for(int i = 0; i<rows; i++)
		for(int j = 0; j<cols; j++)
			for(int k = 0; k<c; k++)
				result.matrix[i][j] += m1.matrix[i][k] * m2.matrix[k][j];
                
	return result;
}

/**
 * Print matrix
 **/
void print_matrix(matrix m)  {

	for(int i = 0; i < m.rows; i++) {
		for(int j = 0; j < m.cols; j++)
			std::cout << std::setprecision(std::numeric_limits<double>::digits10) << m.matrix[i][j] << " "; //kolla med digits

		std::cout << std::endl;
	}

}

}