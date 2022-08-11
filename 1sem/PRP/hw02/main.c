#include <stdio.h>
#include <stdlib.h>

#define ERR 100
#define MIN -10000
#define MAX 10000
#define PROC 100

/**
 * The purpose of the task is to learn how to use loops, 
 * simple mathematical operations and improve coding style. 
 * The data for testing the program can be found in data folder.
 */

int main(void) {

    int ret = EXIT_SUCCESS;
    int r, v, counter = 0, amount_num = 0, num_pos = 0, num_neg = 0, 
        num_even = 0, num_odd = 0, sum = 0, min = 10000, max = -10000;
    double proc_pos = 0, proc_neg = 0, proc_even = 0, proc_odd = 0, avrg_num = 0;

    while ((r = scanf("%d", &v)) > 0) {
        if (v >= MIN && v <= MAX) {
            if (counter == 0) {
                printf("%d", v);
                counter += 1;
            } else if (counter > 0) {
                printf(", %d", v);
            }
        } else {
            printf("\nError: Vstup je mimo interval!\n");
            ret = ERR;
            return ret;
        }
        amount_num += 1;
        if (v > 0) {
            num_pos += 1;
        }
        if (v < 0) {
            num_neg += 1;
        }
        proc_pos = ((double)num_pos / amount_num) * PROC;
        proc_neg = ((double)num_neg / amount_num) * PROC;
        if (v % 2 == 0) {
            num_even += 1;
        }
        if (v % 2 != 0) {
            num_odd += 1;
        }
        proc_even = ((double)num_even / amount_num) * PROC;
        proc_odd = ((double)num_odd / amount_num) * PROC;
        sum += v;
        avrg_num = ((double)sum / amount_num);
        if (v > max) {
            max = v;
        }
        if (v < min) {
            min = v;
        }
    }

    if (r == EOF) {
        if (v >= MIN && v <= MAX) {
            printf("\nPocet cisel: %d\n", amount_num);
            printf("Pocet kladnych: %d\n", num_pos);
            printf("Pocet zapornych: %d\n", num_neg);
            printf("Procento kladnych: %.2f\n", proc_pos);
            printf("Procento zapornych: %.2f\n", proc_neg);
            printf("Pocet sudych: %d\n", num_even);
            printf("Pocet lichych: %d\n", num_odd);
            printf("Procento sudych: %.2f\n", proc_even);
            printf("Procento lichych: %.2f\n", proc_odd);
            printf("Prumer: %.2f\n", avrg_num);
            printf("Maximum: %d\n", max);
            printf("Minimum: %d\n", min);
        }
    }

    return ret;
}
