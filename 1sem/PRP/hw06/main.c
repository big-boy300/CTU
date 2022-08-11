#include <stdio.h>
#include <stdlib.h>

#define INPUT_ERROR 100
#define SYS_ERR -1

/**
 * The purpose of the task is to improve skills when using functions, 
 * 2d arrays, pointers and dynamic memory allocation.
 * The program implements mathematical operations with matrices.
 * The data for testing the program can be found in data folder.
 */

int **read_matrix(int rows_num, int cols_num, int **matrix);
void sum_matrix(int **matrix1, int rows_num1, int cols_num1, int **matrix2);
void substract_matrix(int **matrix1, int rows_num1, int cols_num1, int **matrix2);
void multiplication(int **matrix1, int rows_num1, int cols_num1, int **matrix2, int rows_num2, int cols_num2, int **matrix_after_multiplication);
void free_matrix(int **matrix, int rows);
int **alloc_matrix(int rows_num, int cols_num);
int read_param();
char operation_detector();

int main() {
    int ret = EXIT_SUCCESS;
    int rows_num1, cols_num1;
    if ((rows_num1 = read_param()) == -1) {
        ret = INPUT_ERROR;
        fprintf(stderr, "Error: Chybny vstup!\n");
    }

    if ((cols_num1 = read_param()) == -1) {
        ret = INPUT_ERROR;
        fprintf(stderr, "Error: Chybny vstup!\n");
    }

    int **matrix1 = alloc_matrix(rows_num1, cols_num1);
    if (matrix1 == NULL) {
        fprintf(stderr, "FAILED TO ALLOCATE MATRIX ON LINE: %d\n", __LINE__);
        ret = EXIT_FAILURE;
        return ret;
    }
    matrix1 = read_matrix(rows_num1, cols_num1, matrix1);

    char operation = operation_detector();

    int rows_num2, cols_num2;
    if ((rows_num2 = read_param()) == -1) {
        ret = INPUT_ERROR;
        fprintf(stderr, "Error: Chybny vstup!\n");
    }
    if ((cols_num2 = read_param()) == -1) {
        ret = INPUT_ERROR;
        fprintf(stderr, "Error: Chybny vstup!\n");
    }

    int **matrix2 = alloc_matrix(rows_num2, cols_num2);
    if (matrix2 == NULL) {
        fprintf(stderr, "FAILED TO ALLOCATE MATRIX ON LINE: %d\n", __LINE__);
        ret = EXIT_FAILURE;
        free_matrix(matrix1, rows_num1);
        return ret;
    }
    matrix2 = read_matrix(rows_num2, cols_num2, matrix2);

    int **matrix_after_multiplication = alloc_matrix(rows_num1, cols_num2);
    if (matrix_after_multiplication == NULL) {
        fprintf(stderr, "FAILED TO ALLOCATE MATRIX ON LINE: %d\n", __LINE__);
        ret = EXIT_FAILURE;
        free_matrix(matrix1, rows_num1);
        free_matrix(matrix2, rows_num2);
        return ret;
    }

    if (operation == '+') {
        if (rows_num1 == rows_num2 && cols_num1 == cols_num2) {
            sum_matrix(matrix1, rows_num1, cols_num1, matrix2);
        } else {
            fprintf(stderr, "Error: Chybny vstup!\n");
            ret = INPUT_ERROR;
        }
    } else if (operation == '-') {
        if (rows_num1 == rows_num2 && cols_num1 == cols_num2) {
            substract_matrix(matrix1, rows_num2, cols_num2, matrix2);
        } else {
            fprintf(stderr, "Error: Chybny vstup!\n");
            ret = INPUT_ERROR;
        }
    } else if (operation == '*') {
        if (cols_num1 == rows_num2) {
            multiplication(matrix1, rows_num1, cols_num1, matrix2, rows_num2, cols_num2, matrix_after_multiplication);
        } else {
            fprintf(stderr, "Error: Chybny vstup!\n");
            ret = INPUT_ERROR;
        }
    } else {
        fprintf(stderr, "Error: Chybny vstup!\n");
        ret = INPUT_ERROR;
    }

    free_matrix(matrix1, rows_num1);
    free_matrix(matrix2, rows_num2);
    free_matrix(matrix_after_multiplication, rows_num1);

    return ret;
}

int **read_matrix(int rows_num, int cols_num, int **matrix) {
    int row, col;
    int var1, ret;
    for (row = 0; row < rows_num; ++row) {
        for (col = 0; col < cols_num; ++col) {
            if ((ret = scanf("%d", &var1)) != 1) {
                fprintf(stderr, "Error: Chybny vstup!\n");
                for (row = 0; row < rows_num; ++row) {
                    free(matrix[row]);
                }
                free(matrix);
                exit(INPUT_ERROR);
            }
            matrix[row][col] = var1;
        }
    }
    return matrix;
}

void sum_matrix(int **matrix1, int rows_num1, int cols_num1, int **matrix2) {
    int row, col;
    for (row = 0; row < rows_num1; ++row) {
        for (col = 0; col < cols_num1; ++col) {
            matrix1[row][col] += matrix2[row][col];
        }
    }
    printf("%d %d\n", rows_num1, cols_num1);
    for (row = 0; row < rows_num1; ++row) {
        for (col = 0; col < cols_num1; ++col) {
            printf("%d", matrix1[row][col]);
            if (col != cols_num1 - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void substract_matrix(int **matrix1, int rows_num1, int cols_num1, int **matrix2) {
    int row, col;
    for (row = 0; row < rows_num1; ++row) {
        for (col = 0; col < cols_num1; ++col) {
            matrix1[row][col] -= matrix2[row][col];
        }
    }
    printf("%d %d\n", rows_num1, cols_num1);
    for (row = 0; row < rows_num1; ++row) {
        for (col = 0; col < cols_num1; ++col) {
            printf("%d", matrix1[row][col]);
            if (col != cols_num1 - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void multiplication(int **matrix1, int rows_num1, int cols_num1, int **matrix2, int rows_num2, int cols_num2, int **matrix_after_multiplication) {
    int row, col;
    for (row = 0; row < rows_num1; ++row) {
        for (col = 0; col < cols_num2; ++col) {
            matrix_after_multiplication[row][col] = 0;
            for (int r_or_c = 0; r_or_c < cols_num1; ++r_or_c) {
                matrix_after_multiplication[row][col] += matrix1[row][r_or_c] * matrix2[r_or_c][col];
            }
        }
    }
    printf("%d %d\n", rows_num1, cols_num2);
    for (row = 0; row < rows_num1; ++row) {
        for (col = 0; col < cols_num2; ++col) {
            printf("%d", matrix_after_multiplication[row][col]);
            if (col != cols_num2 - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

char operation_detector() {
    char operation;
    if (scanf(" %c", &operation) != 1) {
        return SYS_ERR;
    }
    return operation;
}

void free_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

int **alloc_matrix(int rows_num, int cols_num) {
    int **ret = (int **)malloc(rows_num * cols_num * sizeof(int *));
    for (int i = 0; i < rows_num; ++i) {
        ret[i] = (int *)malloc(cols_num * sizeof(int));
    }
    return ret;
}

int read_param() {
    int tmp, param;
    if ((tmp = scanf("%d", &param)) != 1 || param < 0) {
        return SYS_ERR;
    }
    return param;
}
