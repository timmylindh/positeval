#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

extern double calc_average(double * norms, int length);

int main(int argc, char ** argv) {
    string path;
    fstream file;
    int num;

    double mean, min, max, average;

    // Get the arguments
    path = argv[1];
    num = stoi(argv[2]) - 1;
    double norms[num];

    // Open file
    file.open(path, ios::in); 

    // Read norms
	for(int i = 0; i<num; i++)
        file >> norms[i];
    
    // Sort and fetch the data we're interested in
    sort(norms, norms + num);
    
    min = norms[0];
    max = norms[num-1];
    mean = norms[num/2];
    average = calc_average(norms, num);

    std::cout << std::setprecision(14) << min << endl;
    std::cout << std::setprecision(14) << max << endl;
    std::cout << std::setprecision(14) << mean << endl;
    std::cout << std::setprecision(14) << average << endl;

    file.close();
    return 0;

}

double calc_average(double * norms, int length) {
    double sum;
    
    sum = 0;

    for(int i = 0; i < length; i++)
        sum += norms[i];

    return sum / length;
}

