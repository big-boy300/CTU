#include <stdio.h>
#include <stdlib.h>

/**
 * The purpose of the task is to learn how to take input data using the scanf() function, 
 * process it and print it out to the console using the printf() function.
 * The data for testing the program can be found in data folder.
 */

int main() {
    int a, b;
    int ret = EXIT_SUCCESS;

    if (scanf("%i%i", &a, &b) == 2) {
        if (a < -10000) {
            printf("Vstup je mimo interval!\n");
            return ret;
        } else if (a > 10000) {
            printf("Vstup je mimo interval!\n");
            return ret;
        } else if (b < -10000) {
            printf("Vstup je mimo interval!\n");
            return ret;
        } else if (b > 10000) {
            printf("Vstup je mimo interval!\n");
            return ret;
        }

        printf("Desitkova soustava: %i %i\n", a, b);
        printf("Sestnactkova soustava: %x %x\n", a, b);
        printf("Soucet: %i + %i = %i\n", a, b, a + b);
        printf("Rozdil: %i - %i = %i\n", a, b, a - b);
        printf("Soucin: %i * %i = %i\n", a, b, a * b);

        if (b != 0) {
            printf("Podil: %i / %i = %i\n", a, b, a / b);
        } else {
            printf("Nedefinovany vysledek!\n");
        }

        printf("Prumer: %0.1f\n", (a + b) / 2.);
        return ret;
    } else {
        fprintf(stderr, "SCANF ERROR\n");
        return EXIT_FAILURE;
    }
}
