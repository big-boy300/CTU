#include <stdio.h>
#include <stdlib.h>

/**
 * assignment
 * https://cw.felk.cvut.cz/brute/data/ae/release/2021z_b4b33alg/alg_cz_2021z/evaluation/input.php?task=buildingarea
 */

typedef struct {
    int curX, curY;
    int clearUpY, dirtyUpY, clearDownY, dirtyDownY;
    int clearLenUp, dirtyLenUp, clearLenDown, dirtyLenDown;
} dataStruct;

int main() {
    int rows, cols;
    if ((scanf("%d %d\n", &rows, &cols)) != 2) {
        fprintf(stderr, "scanf failed!");
    }

    // initial matrix will be stored on stack
    char matrix[rows][cols];

    // take matrix
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if ((scanf("%c ", &matrix[i][j])) != 1) {
                fprintf(stderr, "scanf failed!");
                return -1;
            }
        }
    }

    // array of structures will be stored on heap not to get a segfault
    dataStruct **arrOfStructs = (dataStruct **)malloc(rows * sizeof(dataStruct *));

    if (arrOfStructs == NULL) {
        fprintf(stderr, "MALLOC FAILURE ON LINE %d\n", __LINE__);
    }

    for (int i = 0; i < rows; ++i) {
        arrOfStructs[i] = (dataStruct *)malloc(cols * sizeof(dataStruct));
        if (arrOfStructs[i] == NULL) {
            fprintf(stderr, "MALLOC FAILURE ON LINE %d\n", __LINE__);
            free(arrOfStructs);
        }
    }

    // loop over matrix and save every clean and dirty column from concrete coordinate to a structure
    // when traversing to the up and to the bottom, take it like two different parts
    for (int j = 0; j < cols; ++j) {
        for (int i = 0; i < rows; ++i) {
            if (matrix[i][j] == 'X') {
                arrOfStructs[i][j].curX = j;
                arrOfStructs[i][j].curY = i;
                arrOfStructs[i][j].clearUpY = -1;
                arrOfStructs[i][j].dirtyUpY = -1;
                arrOfStructs[i][j].clearDownY = -1;
                arrOfStructs[i][j].dirtyDownY = -1;
                arrOfStructs[i][j].clearLenUp = 0;
                arrOfStructs[i][j].dirtyLenUp = 0;
                arrOfStructs[i][j].clearLenDown = 0;
                arrOfStructs[i][j].dirtyLenDown = 0;
                continue;
            }
            int counterYellowUp = 0, counterYellowDown = 0;
            int cleanLenUp = 0, dirtyLenUp = 0;
            int cleanLenDown = 0, dirtyLenDown = 0;
            int clearUpY = 0, dirtyUpY = 0, clearDownY = 0, dirtyDownY = 0;
            arrOfStructs[i][j].curX = j;
            arrOfStructs[i][j].curY = i;
            for (int k = 1; k < rows; ++k) {
                // wall down
                if (i + k <= rows - 1) {
                    if (counterYellowDown == 0) {
                        if (matrix[i + k][j] == '.') {
                            cleanLenDown++;
                        } else if (matrix[i + k][j] == 'o') {
                            counterYellowDown++;
                            dirtyLenDown++;
                        } else if (matrix[i + k][j] == 'X') {
                            break;
                        }
                    } else if (counterYellowDown == 1) {
                        if (matrix[i + k][j] == '.') {
                            dirtyLenDown++;
                        } else if (matrix[i + k][j] == 'o') {
                            break;
                        } else if (matrix[i + k][j] == 'X') {
                            break;
                        }
                    }
                } else {
                    break;
                }
            }
            dirtyLenDown += cleanLenDown;
            clearDownY = i + cleanLenDown;
            dirtyDownY = i + dirtyLenDown;

            for (int z = 1; z < rows; z++) {
                // wall up
                if (i - z >= 0) {
                    if (counterYellowUp == 0) {
                        if (matrix[i - z][j] == '.') {
                            cleanLenUp++;
                        } else if (matrix[i - z][j] == 'o') {
                            counterYellowUp++;
                            dirtyLenUp++;
                        } else if (matrix[i - z][j] == 'X') {
                            break;
                        }
                    } else if (counterYellowUp == 1) {
                        if (matrix[i - z][j] == '.') {
                            dirtyLenUp++;
                        } else if (matrix[i - z][j] == 'o') {
                            break;
                        } else if (matrix[i - z][j] == 'X') {
                            break;
                        }
                    }
                } else {
                    break;
                }
            }
            dirtyLenUp += cleanLenUp;
            clearUpY = i - cleanLenUp;
            dirtyUpY = i - dirtyLenUp;

            if (cleanLenUp == 0) {
                clearUpY = -1;
            }
            if (dirtyLenUp == 0) {
                dirtyUpY = -1;
            }
            if (cleanLenDown == 0) {
                clearDownY = -1;
            }
            if (dirtyLenDown == 0) {
                dirtyDownY = -1;
            }

            // write into an array
            arrOfStructs[i][j].clearUpY = clearUpY;
            arrOfStructs[i][j].dirtyUpY = dirtyUpY;
            arrOfStructs[i][j].clearDownY = clearDownY;
            arrOfStructs[i][j].dirtyDownY = dirtyDownY;
            arrOfStructs[i][j].clearLenUp = cleanLenUp;
            arrOfStructs[i][j].dirtyLenUp = dirtyLenUp;
            arrOfStructs[i][j].clearLenDown = cleanLenDown;
            arrOfStructs[i][j].dirtyLenDown = dirtyLenDown;
        }
    }

    // traverse matrix to find the largest pattern
    int patternLen = 0;
    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 0; j < cols; ++j) {
            int cleanHorLen = 0;
            int dirtyHorLen = 0;
            int counterYellow = 0;
            for (int k = j; k < cols; k++) {
                if (counterYellow == 0) {
                    if (matrix[i][k] == '.') {
                        cleanHorLen++;
                    } else if (matrix[i][k] == 'o') {
                        dirtyHorLen++;
                        counterYellow++;
                    } else if (matrix[i][k] == 'X') {
                        break;
                    }
                } else if (counterYellow == 1) {
                    if (matrix[i][k] == '.') {
                        dirtyHorLen++;
                    } else if (matrix[i][k] == 'o') {
                        break;
                    } else if (matrix[i][k] == 'X') {
                        break;
                    }
                }
            }
            dirtyHorLen += cleanHorLen;

            int cleanSize = 0;
            int dirtySize = 0;

            for (int m = 2; m < dirtyHorLen; ++m) {
                if (m < cleanHorLen) {
                    // searching for clean horizontal, 4 different variants are possible
                    int leftClearLenUp = arrOfStructs[i][j].clearLenUp;
                    int leftDirtyLenUp = arrOfStructs[i][j].dirtyLenUp;
                    int rightClearLenUp = arrOfStructs[i][j + m].clearLenUp;
                    int rightDirtyLenUp = arrOfStructs[i][j + m].dirtyLenUp;
                    int leftClearLenDown = arrOfStructs[i][j].clearLenDown;
                    int leftDirtyLenDown = arrOfStructs[i][j].dirtyLenDown;
                    int rightClearLenDown = arrOfStructs[i][j + m].clearLenDown;
                    int rightDirtyLenDown = arrOfStructs[i][j + m].dirtyLenDown;
                    int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;

                    // 1 variant: Left Upper Part is dirty, other are clean
                    if (!(leftDirtyLenUp == 0 || rightClearLenUp == 0 || leftClearLenDown == 0 || rightClearLenDown == 0)) {
                        sum1 = 2 * (leftDirtyLenUp > rightClearLenUp ? rightClearLenUp : leftDirtyLenUp) +
                               2 * (leftClearLenDown > rightClearLenDown ? rightClearLenDown : leftClearLenDown) +
                               m + 1;
                    }
                    // 2 variant: Right Upper Part is dirty, other are clean
                    if (!(leftClearLenUp == 0 || rightDirtyLenUp == 0 || leftClearLenDown == 0 || rightClearLenDown == 0)) {
                        sum2 = 2 * (leftClearLenUp > rightDirtyLenUp ? rightDirtyLenUp : leftClearLenUp) +
                               2 * (leftClearLenDown > rightClearLenDown ? rightClearLenDown : leftClearLenDown) +
                               m + 1;
                    }
                    // 3 variant: Left Down Part is dirty, other are clean
                    if (!(leftClearLenUp == 0 || rightClearLenUp == 0 || leftDirtyLenDown == 0 || rightClearLenDown == 0)) {
                        sum3 = 2 * (leftClearLenUp > rightClearLenUp ? rightClearLenUp : leftClearLenUp) +
                               2 * (leftDirtyLenDown > rightClearLenDown ? rightClearLenDown : leftDirtyLenDown) +
                               m + 1;
                    }
                    // 4 variant: Left Down Part is dirty, other are clean
                    if (!(leftClearLenUp == 0 || rightClearLenUp == 0 || leftClearLenDown == 0 || rightDirtyLenDown == 0)) {
                        sum4 = 2 * (leftClearLenUp > rightClearLenUp ? rightClearLenUp : leftClearLenUp) +
                               2 * (leftClearLenDown > rightDirtyLenDown ? rightDirtyLenDown : leftClearLenDown) +
                               m + 1;
                    }

                    cleanSize = sum1 > sum2 ? sum1 : sum2;
                    cleanSize = cleanSize > sum3 ? cleanSize : sum3;
                    cleanSize = cleanSize > sum4 ? cleanSize : sum4;
                } else {
                    // Dirty horizontal, other are clean
                    int leftLenUp = arrOfStructs[i][j].clearLenUp;
                    int rightLenUp = arrOfStructs[i][j + m].clearLenUp;
                    int maxLenUp = leftLenUp > rightLenUp ? rightLenUp : leftLenUp;

                    int leftLenDown = arrOfStructs[i][j].clearLenDown;
                    int rightLenDown = arrOfStructs[i][j + m].clearLenDown;
                    int maxLenDown = leftLenDown > rightLenDown ? rightLenDown : leftLenDown;

                    if (maxLenUp != 0 && maxLenDown != 0) {
                        dirtySize = 2 * (maxLenUp + maxLenDown) + m + 1;
                    }
                }
                int tmp = cleanSize > dirtySize ? cleanSize : dirtySize;
                if (tmp > patternLen) {
                    patternLen = tmp;
                }
            }
        }
    }

    // final pattern length
    printf("%d\n", patternLen);

    // free memory
    for (int i = 0; i < rows; ++i) {
        free(arrOfStructs[i]);
    }
    free(arrOfStructs);

    return 0;
}
