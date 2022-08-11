#include <stdio.h>
#include <stdlib.h>
 
#define REALLOC_CAPACITY 15

/**
 * The purpose of the program is to learn how to work
 * with files and strings.
 * The program implements basic functionality of grep program
 * of UNIX type OS's, it prints out all lines containing specific pattern
 * from a given file.
 * The data for testing the program can be found in data folder.
 */

int main(int argc, char* argv[])
{
    int ret = EXIT_FAILURE;
    FILE *input_file = NULL;
     
    char *pattern;
    pattern = argv[1];
    if (argv[2]){ 
        input_file = fopen(argv[2], "r");
        if(input_file == NULL){
            fprintf(stderr, "File cannot be opened.\n");
            return 100;
        }
    } else {
        input_file = stdin;
    }
 
    char *line = (char*)malloc(sizeof(char));
    int size = 0;
    int mem_allocd = sizeof(char);
 
    int c, flag_pattern = 0, pat_index = 0, counter = 0;
    while((c = fgetc(input_file)) != EOF){        
        if (size + 1 == mem_allocd){
            mem_allocd += REALLOC_CAPACITY;
            line = realloc(line, sizeof(char) * mem_allocd);
        }
 
        if(c == '\n'){
            line[size++] = c;
            line[size++] = '\0';
            if (flag_pattern == 1){
                printf("%s", line);
                flag_pattern = 0;
            } 
            size = 0;
        } else {
            if ((char) c == pattern[pat_index]) {              
                counter++;
                pat_index++;
                if(pattern[pat_index] == '\0') {
                    flag_pattern = 1;
                    pat_index = 0;
                    ret = EXIT_SUCCESS;
                }
            } else if(counter > 0 && (char) c != pattern[pat_index]){
                    counter = 1;
                    pat_index = 0; 
            }               
            line[size++] = c;
            line[size] = '\0';
        }
    }
 
    free(line);
    fclose(input_file);
     
    return ret;
}
