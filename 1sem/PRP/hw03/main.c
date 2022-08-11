#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR_WRONG_INPUT 100
#define ERROR_IMPOSSIBLE_INPUT 101
#define ERROR_WIDTH 102
#define ERROR_FENCE 103

/**
 * The purpose of this task is to learn how to use nested loops, 
 * improve "printing skills" and coding style. 
 * This program basically prints out a house to the console, depending on its
 * size house can be with or without fence and windows.
 * The data for testing the program can be found in data folder.
 */

int print_house(int, int);
int print_with_fence(int, int, int);
int test_house_size(int, int);
int test_fence_size(int, int, int);

int main() {
    int ret = 0;
    int width, height, fence_size;
    bool fence = false;

    if (scanf("%d %d", &width, &height) == 2) {
        if (width == height) {
            if (scanf("%d", &fence_size) == 1) {
                fence = true;
            } else {
                fprintf(stderr, "Error: Chybny vstup!\n");
                ret = ERROR_WRONG_INPUT;
                return ret;
            }
        }
    } else {
        fprintf(stderr, "Error: Chybny vstup!\n");
        ret = ERROR_WRONG_INPUT;
        return ret;
    }

    if (test_house_size(width, height) == ERROR_IMPOSSIBLE_INPUT) {
        fprintf(stderr, "Error: Vstup mimo interval!\n");
        ret = ERROR_IMPOSSIBLE_INPUT;
        return ret;
    }

    if (test_house_size(width, height) == ERROR_WIDTH) {
        fprintf(stderr, "Error: Sirka neni liche cislo!\n");
        ret = ERROR_WIDTH;
        return ret;
    }

    if (test_fence_size(width, height, fence_size) == ERROR_FENCE) {
        fprintf(stderr, "Error: Neplatna velikost plotu!\n");
        ret = ERROR_FENCE;
        return ret;
    }

    if (!fence) {
        print_house(width, height);
    } else {
        print_with_fence(width, height, fence_size);
    }

    return ret;
}

int print_house(int width, int height) {
    int ret = test_house_size(width, height);
    
    if (ret == 0) {
        int i, j, m;

        for (i = 0; i <= (width / 2) - 1; ++i) {
            for (j = 0; j < (width / 2) - i; ++j) {
                printf(" ");
            }
            printf("X");

            for (m = 0; m <= (2 * i) - 2; ++m) {
                printf(" ");
            }
            if (i > 0) {
                printf("X");
            }
            printf("\n");
        }

        for (i = 0; i < width; ++i) {
            printf("X");
        }
        printf("\n");

        for (m = 0; m < height - 2; ++m) {
            printf("X");
            for (i = 0; i < width - 2; ++i) {
                printf(" ");
            }
            printf("X\n");
        }

        for (j = 0; j < width; ++j) {
            printf("X");
        }
        printf("\n");
    }

    return ret;
}

int print_with_fence(int width, int height, int fence_size) {
    int ret = test_house_size(width, height);

    if (ret == 0) {
        ret = test_fence_size(width, height, fence_size);
    }

    if (ret == 0) {
        int i, j, m;

        for (i = 0; i <= (width / 2) - 1; ++i) {
            for (j = 0; j < (width / 2) - i; ++j) {
                printf(" ");
            }
            printf("X");

            for (m = 0; m <= (2 * i) - 2; ++m) {
                printf(" ");
            }
            if (i > 0) {
                printf("X");
            }
            printf("\n");
        }

        for (i = 0; i < width; ++i) {
            printf("X");
        }
        printf("\n");

        for (m = 0; m < height - 2; ++m) {
            printf("X");
            for (i = 0; i < width - 2; ++i) {
                if (m % 2 == 0) {
                    if (i % 2 == 0) {
                        printf("o");
                    } else {
                        printf("*");
                    }
                } else {
                    if (i % 2 == 0) {
                        printf("*");
                    } else {
                        printf("o");
                    }
                }
            }
            printf("X");

            if (m >= height - fence_size - 1) {
                if (fence_size % 2 == 1) {
                    printf("|");
                }
                if (m == height - fence_size - 1) {
                    for (i = 0; i < fence_size / 2; ++i) {
                        printf("-|");
                    }
                } else {
                    for (i = 0; i < fence_size / 2; ++i) {
                        printf(" |");
                    }
                }
            }
            printf("\n");
        }
        for (j = 0; j < width; ++j) {
            printf("X");
        }
        if (fence_size % 2 == 1) {
            printf("|");
        }
        for (i = 0; i < fence_size / 2; ++i) {
            printf("-|");
        }
        printf("\n");
    }

    return ret;
}

int test_house_size(int width, int height) {
    int ret = 0;

    if ((width < 3 || width > 69) || (height < 3 || height > 69)) {
        ret = ERROR_IMPOSSIBLE_INPUT;
        return ret;
    }
    if (width % 2 == 0) {
        ret = ERROR_WIDTH;
        return ret;
    }

    return ret;
}

int test_fence_size(int width, int height, int fence_size) {
    int ret = 0;

    if (fence_size > 0 && fence_size < height) {
        ret = 0;
    } else {
        if (width != height) {
            ret = 0;
        } else {
            ret = ERROR_FENCE;
            return ret;
        }
    }

    return ret;
}
