#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * assignment
 * https://cw.felk.cvut.cz/brute/data/ae/release/2021z_b4b33alg/alg_cz_2021z/evaluation/input.php?task=totems
 */

typedef struct {
    int allWarriors;
    int price;
    int diff;
} elem_t;

int findMax(int num1, int num2) {
    int ret = num1 > num2 ? num1 : num2;
    return ret;
}

int main(void) {
    int villagesNum, totemPrice, priceOfWarrior;

    if ((scanf("%d %d %d\n", &villagesNum, &totemPrice, &priceOfWarrior)) != 3) {
        fprintf(stderr, "SCANF FAILURE ON LINE %d\n", __LINE__);
    }

    int* warriorsNumInVillage = (int*)malloc(sizeof(int) * villagesNum);
    for (int i = 0; i < villagesNum; ++i) {
        if ((scanf("%d", &warriorsNumInVillage[i])) != 1) {
            fprintf(stderr, "SCANF FAILURE ON LINE %d\n", __LINE__);
        }
    }

    elem_t** resMatrix = (elem_t**)malloc(villagesNum * sizeof(elem_t*));
    if (resMatrix == NULL) {
        fprintf(stderr, "MALLOC FAILURE ON LINE %d\n", __LINE__);
    }
    for (int i = 0; i < villagesNum; ++i) {
        resMatrix[i] = malloc(villagesNum * sizeof(elem_t));
        if (resMatrix[i] == NULL) {
            fprintf(stderr, "MALLOC FAILURE ON LINE %d\n", __LINE__);
        }
    }

    // fill result matrix with zeroes to start working with it
    for (int i = 0; i < villagesNum; ++i) {
        for (int j = 0; j < villagesNum; ++j) {
            resMatrix[i][j].allWarriors = 0;
            resMatrix[i][j].price = 0;
            resMatrix[i][j].diff = 0;
        }
    }

    // fill result matrix, need to traverse it diagonally
    for (int l = 0; l < villagesNum; ++l) {
        for (int i = 0, j = l; j < villagesNum; ++i, ++j) {
            if (i == j) {  // fill main diagonal from input
                resMatrix[i][j].allWarriors = warriorsNumInVillage[i];
                resMatrix[i][j].price = 0;
            } else if (j - i == 1) {  // fill second diagonal, only one variant possible
                resMatrix[i][j].allWarriors = resMatrix[i][j - 1].allWarriors + resMatrix[i + 1][j].allWarriors;
                resMatrix[i][j].price = (totemPrice - (priceOfWarrior * abs(resMatrix[i][j - 1].allWarriors - resMatrix[i + 1][j].allWarriors)));
            } else {  // fill other diagonals, more than 1 variant possible, need some tmp variables
                int price = INT_MIN, warriors = 0, diff = 0;
                for (int k = i; k < j; ++k) {
                    int newPrice = totemPrice - (priceOfWarrior * abs(resMatrix[i][k].allWarriors - resMatrix[k + 1][j].allWarriors)) + resMatrix[i][k].price + resMatrix[k + 1][j].price;
                    int newWarriors = resMatrix[i][k].allWarriors + resMatrix[k + 1][j].allWarriors;
                    int newDiff = findMax(resMatrix[i][k].price, resMatrix[i][k].diff) + findMax(resMatrix[k + 1][j].price, resMatrix[k + 1][j].diff);
                    if (newPrice > price) {
                        price = newPrice;
                    }
                    if (newWarriors > warriors) {
                        warriors = newWarriors;
                    }
                    if (newDiff > diff) {
                        diff = newDiff;
                    }
                }
                resMatrix[i][j].allWarriors = warriors;
                resMatrix[i][j].price = price;
                resMatrix[i][j].diff = diff;
            }
        }
    }

    // print result
    printf("%d\n", findMax(resMatrix[0][villagesNum - 1].price, resMatrix[0][villagesNum - 1].diff));
}
