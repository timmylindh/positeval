#include <iostream>
#include <fstream>
using namespace std;
int main(){
    double sum, val;
    sum = 0;

	fstream file; 
    file.open("matrices/result", ios::in); //check filepath

	for(int i = 0; i<5; i++){ //average of 5 doubles
		file >> val;
        sum += val;
    }
	file.close();

    std::cout << setprecision(14) << sum/5;

    return 0;

}

