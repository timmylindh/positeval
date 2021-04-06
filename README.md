# Assessing Differences in Precision with Posit Floating Point Format compared to IEEE 754

The purpose of this project is to conduct a comparative study of the precision comparing the 32-bit IEEE 754 and Posit32 floating point representations in high performance computing. For this we will use Matrix multiplication.

## Compilation

### Float32 / Float64 Matrix Multiplication

To compile the float32 version of the Matrix multiplication, run the following commands:

```
cd matrix_multiplication/
g++ float32.cpp -o f32.out
```

To compile the float64 version:

```
cd matrix_multiplication/
g++ float64.cpp -o f64.out
```

### Posit32 Matrix Multiplication

To compile the posit32 version of the Matrix multiplication the Softposit library has to be linked. Use the following command:

```
cd matrix_multiplication/
g++ -std=gnu++11 -o p32.out posit32.cpp ../SoftPosit/build/Linux-x86_64-GCC/softposit.a -I../SoftPosit/build/Linux-x86_64-GCC  -O2
```

