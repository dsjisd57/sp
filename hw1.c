#include <stdio.h>
#include <stdlib.h>
//BY CHARTGPT 3.5 and change it into a second-order matrix
//RESULT:
//Original matrix 1：
//Matrix content:
//1.00    2.00
//3.00    4.00
//Original matrix 2：
//Matrix content:
//1.00    2.00
//3.00    4.00
//transposed matrix 1：
//Matrix content:
//1.00    3.00
//2.00    4.00
//added matrix 1：
//Matrix content:
//2.00    5.00
//5.00    8.00
//matrix result after multiplication：
//Matrix content:
//17.00   24.00
//29.00   42.00

// Transpose matrix
void transpose(double *matrix, int rows, int cols) {
    double *result = malloc(rows * cols * sizeof(double));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j * rows + i] = matrix[i * cols + j];
        }
    }
    // Copy the result back to the original matrix
    for (int i = 0; i < rows * cols; i++) {
        matrix[i] = result[i];
    }
    free(result);
}

// matrix addition
void add(double *matrix1, double *matrix2, int rows, int cols) {
    for (int i = 0; i < rows * cols; i++) {
        matrix1[i] += matrix2[i];
    }
}

// matrix multiplication
void multiply(double *matrix1, double *matrix2, double *result, int rows1, int cols1, int rows2, int cols2) {
    if (cols1 != rows2) {
        printf("Matrix size does not meet multiplication requirements!\n");
        return;
    }
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            result[i * cols2 + j] = 0;
            for (int k = 0; k < cols1; k++) {
                result[i * cols2 + j] += matrix1[i * cols1 + k] * matrix2[k * cols2 + j];
            }
        }
    }
}

// print matrix
void dump(double *matrix, int rows, int cols) {
    printf("Matrix content:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%.2f\t", matrix[i * cols + j]);
        }
        printf("\n");
    }
}

// test function
int main() {
    int rows = 2, cols = 2;

    // Create and initialize the matrix
    double *matrix1 = malloc(rows * cols * sizeof(double));
    double *matrix2 = malloc(rows * cols * sizeof(double));
    double *result = malloc(rows * cols * sizeof(double));

    for (int i = 0; i < rows * cols; i++) {
        matrix1[i] = i + 1;
        matrix2[i] = i + 1;
    }

    // Print out the original matrix
    printf("Original matrix 1：\n");
    dump(matrix1, rows, cols);
    printf("Original matrix 2：\n");
    dump(matrix2, rows, cols);

    // Transpose matrix
    transpose(matrix1, rows, cols);
    printf("transposed matrix 1：\n");
    dump(matrix1, cols, rows);

    // matrix addition
    add(matrix1, matrix2, rows, cols);
    printf("added matrix 1：\n");
    dump(matrix1, rows, cols);

    // matrix multiplication
    multiply(matrix1, matrix2, result, rows, cols, rows, cols);
    printf("matrix result after multiplication：\n");
    dump(result, rows, cols);

    // free memory
    free(matrix1);
    free(matrix2);
    free(result);

    return 0;
}
