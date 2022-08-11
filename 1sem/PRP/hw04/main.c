#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
#define ERROR_INPUT 100
#define MAX_NUMBER 1000000
#define BORDER 100000000

/**
 * The purpose of this task is to learn how to use arrays, 
 * improve using loops, taking input and coding style. 
 * The program implements prime factorization using Sieve of Eratosthenes.
 * The data for testing the program can be found in data folder.
 */

long int input_number(void);
int is_number_composite(long int);
 
int find_primes(int max_size, int prime_nums[max_size]);
void decompose_sieve(long int n, int num_of_prime_nums, int prime_nums[num_of_prime_nums]);
 
int main()
{
    int ret = EXIT_SUCCESS;
    long int n;
    int max_prime_number = MAX_NUMBER;
    int prime_nums[max_prime_number];
    int num_of_prime_nums = find_primes(max_prime_number, prime_nums);
    while ((n = input_number()) > 0) {
        printf("Prvociselny rozklad cisla %ld je:\n", n);
        if (n == 1) {
            printf("1\n");
        } else if (n < BORDER){
            is_number_composite(n);
        } else if (n >= BORDER) {
            decompose_sieve(n, num_of_prime_nums, prime_nums);
        }
    }
    if (n < 0) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        ret = ERROR_INPUT;
    }
    return ret;
}
 
long int input_number(void)
{
    long int n = -1;
    if (scanf("%ld", &n) != 1) {
        n = -1;
    }
    return n;
}
 
int is_number_composite(long int n)
{
    int ret = EXIT_SUCCESS;
    int i, j;
    _Bool var = false;
    for(i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            for(j = 0; n % i == 0; ++j) {
                n = n / i;
            }
            if (j > 0) {
                if (var) {
                    printf(" x ");
                }
                if (j > 1) {
                    printf("%d^%d", i, j);
                } if (j == 1) {
                    printf("%d", i);
                }
                var = true;
            }
        } 
    }
    if (n > 1) {
        if (var) {
            printf(" x ");
        }
        printf("%ld", n);
    }
    printf("\n");
    return ret;
}
 
int find_primes(int max_size, int prime_nums[max_size])
{
    int num_of_prime_nums = 0;
    bool sieve[MAX_NUMBER] = {false};
    for (int i = 2; i < MAX_NUMBER; ++i){
        if (sieve[i] == false) {
            prime_nums[num_of_prime_nums] = i;
            num_of_prime_nums += 1;
            for (int j = i; j < MAX_NUMBER; ++j)
            {
                if (i * j < MAX_NUMBER) {
                    sieve[i * j] = true;
                } else {
                    break;
                }
            }
        }
    }
    return num_of_prime_nums;
}
 
void decompose_sieve(long int n, int num_of_prime_nums, int prime_nums[num_of_prime_nums]) 
{
    bool var = false;
    for (int i = 0; i < num_of_prime_nums; ++i) {
        int counter = 0;
        while (n % prime_nums[i] == 0) {
            n = n / prime_nums[i];
            counter += 1;
        }
        if (counter > 0) {
            if (var) {
                printf(" x ");
            }
            if (counter > 1) {
                printf("%d^%d", prime_nums[i], counter);
            } else {
                printf("%d", prime_nums[i]);
            }
            var = true;
            break;
        }
    }
    if (n > 1) {
        if (var) {
            printf(" x ");
        }
        printf("%ld", n);
    }
    printf("\n");
}
