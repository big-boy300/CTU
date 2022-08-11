#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
 
#define STARTING_MSG_LEN 10
#define ERROR_INPUT 100
#define ERROR_LENGTH 101
#define DIFF_BETWEEN_UPPER_AND_LOWER 6
#define NUM_OF_LETTERS_IN_ALPHABET 26 

/**
 * The purpose of the task is to learn how to use pointers, 
 * dynamic memory allocation with the help of malloc() 
 * and realloc() functions and get acquainted with ASCII. 
 * The program implements Caesar cipher.
 * The data for testing the program can be found in data folder.
 */

char *read_input(int *msg_len);
int get_offset(char *msg_encrypted, char *msg, int msg_encrypted_len);
void msg_shift(char *msg_encrypted, int msg_encrypted_len, int offset);
 
int main()
{
    int ret = EXIT_SUCCESS;
 
    char *msg_encrypted, *msg;
    int msg_encrypted_len, msg_len;
 
    msg_encrypted = msg = NULL;
    msg_encrypted_len = msg_len = 0;
 
    msg_encrypted = read_input(&msg_encrypted_len);
    if (msg_encrypted){
        msg = read_input(&msg_len);
    }
 
    if ((msg_encrypted == NULL) || (msg == NULL)){
        ret = ERROR_INPUT;
    } else if (msg_encrypted_len != msg_len){
        ret = ERROR_LENGTH;
    }
 
    if (ret == ERROR_INPUT){
        fprintf(stderr, "Error: Chybny vstup!\n");
    } else if (ret == ERROR_LENGTH){
        fprintf(stderr, "Error: Chybna delka vstupu!\n");
    } else if (ret == EXIT_SUCCESS){
        int offset = get_offset(msg_encrypted, msg, msg_encrypted_len);
        msg_shift(msg_encrypted, msg_encrypted_len, offset);
    }
 
    free(msg_encrypted);
    free(msg);
 
    return ret;
}
 
char *read_input(int *msg_len)
{
    int capacity = STARTING_MSG_LEN;
    char *msg = (char*)malloc(capacity);
    int msg_length = 0;
    if(msg == NULL){
        fprintf(stderr, "Malloc error.\n");
    } else {
        int c;
        while((c = getchar()) != EOF && c != '\n'){
            if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))){
                free(msg);
                msg = NULL;
                msg_length = 0;
                break;
            }
            if(msg_length == capacity){
                char *tmp = (char*)realloc(msg, capacity * 2);
                if(tmp == NULL){
                    free(msg);
                    msg = NULL;
                    msg_length = 0;
                    break;
                }
                capacity *= 2;
                msg = tmp;
            }
            msg[msg_length++] = c;
        }
    }
    *msg_len = msg_length;
    return msg;
}
 
int get_offset(char *msg_encrypted, char *msg, int msg_encrypted_len)
{
    char *all_distances = (char*) malloc(msg_encrypted_len + 1);
    char c;
    for(int i = 0; i < msg_encrypted_len; ++i){
        if(islower(msg_encrypted[i]) && isupper(msg[i])){
            c = msg_encrypted[i] - msg[i] - DIFF_BETWEEN_UPPER_AND_LOWER;   
        } else if (isupper(msg_encrypted[i]) && islower(msg[i])){
            c = msg_encrypted[i] - msg[i] + DIFF_BETWEEN_UPPER_AND_LOWER;
        } else {
            c = msg_encrypted[i] - msg[i];
        }        
        if ((int) c < 0){
            c += (2*NUM_OF_LETTERS_IN_ALPHABET);
        }
        all_distances[i] = c;
    }
     
    int offset = all_distances[0];
    int max_frequency = 1;
    for(int i = 0; i < msg_encrypted_len; ++i){
        int frequency = 1;
        for(int j = i + 1; j < msg_encrypted_len; ++j){
            if (all_distances[i] == all_distances[j]){
                frequency += 1;
            }
            if (frequency > max_frequency){
                max_frequency = frequency;
                offset = all_distances[i];
            }
        }
    }
    free(all_distances);
    return offset;
}
 
void msg_shift(char *msg_encrypted, int msg_encrypted_len, int offset)
{
    int tmp_var = 0;
    int tmp_var2 = 0;
    int tmp_offset = 0;
    for (int i = 0; i < msg_encrypted_len; ++i) {
        if(islower(msg_encrypted[i])){
            if(msg_encrypted[i] - offset >= 'a'){
                msg_encrypted[i] -= offset;
                continue;
            } else if(msg_encrypted[i] - offset < 'a'){
                tmp_var = msg_encrypted[i] - 'a';
                tmp_offset = offset - tmp_var;
                msg_encrypted[i] = ('Z' + 1) - tmp_offset;
                if(msg_encrypted[i] < 'A'){
                    tmp_var2 = 'A' - msg_encrypted[i];
                    msg_encrypted[i] = ('z' + 1) - tmp_var2;
                    continue;    
                }
            }
        } else {
            if(msg_encrypted[i] - offset >= 'A'){
                msg_encrypted[i] -= offset;
                continue;
            } else if(msg_encrypted[i] - offset < 'A'){
                tmp_var = msg_encrypted[i] - 'A';
                msg_encrypted[i] = ('z' + 1) - (offset - tmp_var);
                if(msg_encrypted[i] < 'a'){
                    tmp_var2 = 'a' - msg_encrypted[i];
                    msg_encrypted[i] = ('Z' + 1) - tmp_var2;
                }
            }
        }
    }
     
    for(int i = 0; i < msg_encrypted_len; ++i){
        putchar(msg_encrypted[i]);
    }
    putchar('\n');
}
