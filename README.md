# Assessing Differences in Precision with Posit Floating Point Format compared to IEEE 754

The purpose of this project is to conduct a comparative study of the precision comparing the 32-bit IEEE 754 and Posit32 floating point representations in high performance computing. For this we will use Matrix multiplication.

## Compilation

To compile the nessecary binaries and libraries, issue the following command in *matrix_multiplication/*:

```
make compile
```

## Running

To run the automated mean error calculations, issue:

    ```
make all RANGE=xx SIZE=yy NUM=zz
```

This will create *NUM* randomly generated matrices of size *SIZE x SIZE*, where each matrix entry is a value between *-RANGE and RANGE* in the *matrices/in* folder. Each matrix is then multiplied with another, and the resulting matrix is stored in *out/32*, *out/64* and *out/posit*

