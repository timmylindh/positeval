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

### Matrix generator

To compile the matrix generator, use the following commands:

```
cd matrix_multiplication/
g++ -o gen.out generateMatrix.cpp
``` 

### Matrix comparator

To compile the matrix comparator, use the following commands:

```
cd matrix_multiplication/
g++ -o comp.out comparator.cpp
``` 

## Running

### Matrix Multiplication

To run the matrix multiplication program, issue the following command:

```
./p32.out [m1] [m2] [result]
```

- m1, m2 are the files of which the matrices to multiply reside.
- result is the resulting file of where to store the matrix.

Change p32.out to the program which is being used.

### Matrix generator

To run the matrix generator program, issue the following command:

```
./gen.out [range] [size] [result]
```

- range: a positive integer (x) representing a range from -x to x of which the numbers in the matrix are generated.
- size: a positive integer (n) representing the size of the matix n X n 
- result is the resulting file of where to store the matrix.

### Matrix comparator

To run the matrix comparator, use the following command:

```
./comp.out [m1] [m2]
``` 

- m1, m2 are the files of which the matrices to compare reside.

The resulting Euclidian norm is returned to stdout.