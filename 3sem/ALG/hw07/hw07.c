#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * assignment
 * https://cw.felk.cvut.cz/brute/data/ae/release/2021z_b4b33alg/alg_cz_2021z/evaluation/input.php?task=retrogame
 */

typedef struct egg {
    int eggCol;
    int eggRow;
} egg_t;

void merge(egg_t *arr, int p, int q, int r) {
    int size1 = q - p + 1;
    int size2 = r - q;

    egg_t L[size1], M[size2];

    for (int i = 0; i < size1; ++i) {
        L[i] = arr[p + i];
    }

    for (int j = 0; j < size2; ++j) {
        M[j] = arr[q + 1 + j];
    }

    int i = 0, j = 0, k = p;
    while (i < size1 && j < size2) {
        if (L[i].eggRow < M[j].eggRow || (L[i].eggRow == M[j].eggRow && L[i].eggCol < M[j].eggCol)) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = M[j];
            j++;
        }
        k++;
    }

    while (i < size1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < size2) {
        arr[k] = M[j];
        j++;
        k++;
    }
}

void mergeSort(egg_t *arr, int left, int right) {
    if (left < right) {
        int divPoint = left + (right - left) / 2;
        mergeSort(arr, left, divPoint);
        mergeSort(arr, divPoint + 1, right);
        merge(arr, left, divPoint, right);
    }
}

int findMaxBetween2Nums(int num1, int num2) {
    if (num1 >= num2) {
        return num1;
    } else {
        return num2;
    }
}

int findMaxBetween3Nums(int num1, int num2, int num3) {
    if (num1 >= num2 && num1 >= num3) {
        return num1;
    } else if (num2 >= num1 && num2 >= num3) {
        return num2;
    } else {
        return num3;
    }
}

int main() {
    int playingAreaWidth, numberOfEggs;
    if ((scanf("%d %d\n", &playingAreaWidth, &numberOfEggs)) != 2) {
        fprintf(stderr, "SCANF ERROR ON LINE %d\n", __LINE__);
    }

    egg_t *eggs = (egg_t *)malloc(numberOfEggs * sizeof(egg_t));
    if (eggs == NULL) {
        fprintf(stderr, "MALLOC ERROR ON LINE %d\n", __LINE__);
    }

    for (int i = 0; i < numberOfEggs; ++i) {
        if ((scanf("%d %d\n", &eggs[i].eggCol, &eggs[i].eggRow)) != 2) {
            fprintf(stderr, "SCANF ERROR ON LINE %d\n", __LINE__);
        }
    }

    // sort eggs
    mergeSort(eggs, 0, numberOfEggs - 1);

    int basketPositions = playingAreaWidth - 1;
    int **solCols = (int **)malloc(basketPositions * sizeof(int *));
    if (solCols == NULL) {
        fprintf(stderr, "MALLOC ERROR ON LINE %d\n", __LINE__);
    }
    for (int i = 0; i < basketPositions; ++i) {
        solCols[i] = calloc(2, sizeof(int));
        if (solCols[i] == NULL) {
            fprintf(stderr, "CALLOC ERROR ON LINE %d\n", __LINE__);
        }
    }

    int curRow = 0;
    int i = 0;
    int prevEggRow = 0;

    while (curRow < eggs[numberOfEggs - 1].eggRow && i < numberOfEggs) {
        if (prevEggRow != eggs[i].eggRow) {
            // change cols - find maximum
            for (int j = 0; j < basketPositions; ++j) {
                if (j == 0) {
                    if (curRow % 2 == 0) {
                        solCols[j][1] = findMaxBetween2Nums(solCols[j][0], solCols[j + 1][0]);
                    } else {
                        solCols[j][0] = findMaxBetween2Nums(solCols[j][1], solCols[j + 1][1]);
                    }
                } else if (j == basketPositions - 1) {
                    if (curRow % 2 == 0) {
                        solCols[j][1] = findMaxBetween2Nums(solCols[j][0], solCols[j - 1][0]);
                    } else {
                        solCols[j][0] = findMaxBetween2Nums(solCols[j][1], solCols[j - 1][1]);
                    }
                } else {
                    if (curRow % 2 == 0) {
                        solCols[j][1] = findMaxBetween3Nums(solCols[j][0], solCols[j - 1][0], solCols[j + 1][0]);
                    } else {
                        solCols[j][0] = findMaxBetween3Nums(solCols[j][1], solCols[j - 1][1], solCols[j + 1][1]);
                    }
                }
            }
        }

        if (curRow + 1 == eggs[i].eggRow) {
            // write to cols
            if (eggs[i].eggCol - 1 >= 0 && eggs[i].eggCol <= basketPositions) {
                if (eggs[i].eggCol <= curRow + 2) {
                    solCols[eggs[i].eggCol - 1][(curRow % 2)]++;
                }
            }
            if (eggs[i].eggCol - 2 >= 0) {
                if (eggs[i].eggCol <= curRow + 3) {
                    solCols[eggs[i].eggCol - 2][(curRow % 2)]++;
                }
            }
            prevEggRow = eggs[i].eggRow;
            i++;
        } else {
            // change row
            curRow++;
        }
    }

    int result = 0;
    for (int i = 0; i < basketPositions; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (result < solCols[i][j]) {
                result = solCols[i][j];
            }
        }
    }
    printf("%d\n", result);

    return 0;
}
