#include "float32.cpp"
#include "float64.cpp"

int main() {
    float32::matrix m32_1, m32_2, res32;
    float64::matrix m64_1, m64_2, res64;

    m32_1 = float32::load_matrix("matrices/example.dat");
    m32_2 = float32::load_matrix("matrices/example2.dat");

    m64_1 = float64::load_matrix("matrices/example.dat");
    m64_2 = float64::load_matrix("matrices/example2.dat");

    res32 = float32::matrix_mul(m32_1, m32_2);
    res64 = float64::matrix_mul(m64_1, m64_2);
}