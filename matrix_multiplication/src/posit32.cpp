#include <iostream>
#include <fstream>
#include <iomanip>
#include "../../Softposit/source/include/softposit_cpp.h"

typedef struct {
	posit32 ** matrix;
	int cols;
	int rows;
} matrix;

extern matrix matrix_mul(matrix m1, matrix m2);
extern matrix create_matrix(int rows, int cols);
extern matrix load_matrix(std::string path);
extern void print_matrix(matrix m);
extern void export_matrix(matrix m, std::string file_path);

using namespace std;

int main(int argc, char ** argv) { 
	matrix m1, m2, result;

	if(argc != 4) {
		std::cout << "error: input parameters are matrix1 matrix2 result" << std::endl;
		exit(0);
	}
		
	m1 = load_matrix(argv[1]);
	m2 = load_matrix(argv[2]);
	
	result = matrix_mul(m1, m2);
	
    //print_matrix(result);
	export_matrix(result, argv[3]);

	return 0;
}

/**
 * Create and zero initialize a matrix of size rows x cols
 **/
matrix create_matrix(int rows, int cols) {
	matrix m;

	m.matrix = new posit32 *[rows];
	m.cols = cols;
	m.rows = rows;

	for(int i = 0; i<rows; i++)
		m.matrix[i] = new posit32[cols];

	for(int i = 0; i < rows; i++)
		for(int j = 0; j < cols; j++)
			m.matrix[i][j] = p32(0);

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

    double x;
	for(int i = 0; i<rows; i++)
		for(int j = 0; j<cols; j++) {
			file >> x;
            m.matrix[i][j] = p32(x);
        }
            
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
 * Export a matrix to file
 */
void export_matrix(matrix m, std::string file_path) {
	fstream file;

	file.open(file_path, fstream::out);
	
	file << m.rows << " " << m.cols << std::endl;

	for(int i = 0; i < m.rows; i++) {
		for(int j = 0; j < m.cols; j++)
			file << std::setprecision(14) << m.matrix[i][j] << " ";

		file << std::endl;
	}

	file.close();
}

/**
 * Print matrix
 **/
void print_matrix(matrix m)  {

	for(int i = 0; i < m.rows; i++) {
		for(int j = 0; j < m.cols; j++)
			std::cout << std::setprecision(14) << m.matrix[i][j] << " "; //kolla med digits

		std::cout << std::endl;
	}

}