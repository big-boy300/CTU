#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define THREAD_CHARS 6
#define WHITESPACE 1
#define ZERO_CHAR 1
#define COLON_CHAR 1
#define THREAD_NUM_CHARS 2
#define MALLOC_FAILURE 101

typedef struct input {
    char* text;
    int number;
    struct input* next;
} input_t;

typedef struct {
    input_t* head;
    input_t* tail;
    int length;
} ll_t;

void pushEnd(ll_t* ll, input_t* input);
input_t* pop(ll_t* ll);
bool isEmpty(ll_t* ll);

ll_t* createNewLL();
void freeLL(ll_t* list);

void* consumerFunc(void* arg);
void* producerFunc(void* args);

ll_t* list;

pthread_mutex_t mutex;
sem_t semaphore;

void pushEnd(ll_t* ll, input_t* input) {
    input_t* new_input = (input_t*)malloc(sizeof(input_t));
    if (new_input == NULL) {
        exit(MALLOC_FAILURE);
    }
    new_input->text = input->text;
    new_input->number = input->number;
    new_input->next = NULL;
    if (ll->tail == NULL) {
        ll->head = ll->tail = new_input;
    } else {
        ll->tail->next = new_input;
        ll->tail = new_input;
    }
    ll->length++;
}

input_t* pop(ll_t* ll) {
    if (isEmpty(ll)) {
        return NULL;
    }
    input_t* prev_head = ll->head;
    input_t* ret = prev_head;
    ll->head = prev_head->next;
    ll->length--;
    if (ll->head == NULL) {
        ll->tail = NULL;
    }
    return ret;
}

bool isEmpty(ll_t* ll) {
    bool ret = false;
    if (ll->length == 0) {
        ret = true;
    }
    return ret;
}

ll_t* createNewLL() {
    ll_t* list = (ll_t*)malloc(sizeof(ll_t));
    if (list == NULL) {
        exit(MALLOC_FAILURE);
    }
    list->head = list->tail = NULL;
    list->length = 0;
    return list;
}

void freeLL(ll_t* list) {
    if (list) {
        input_t* tmp = list->head;
        while (tmp) {
            input_t* prev = tmp;
            tmp = tmp->next;
            free(prev->text);
            free(prev);
        }
    }
    free(list);
}

bool producerFinished = false;

void* producerFunc(void* args) {
    int ret, number;
    char* text;
    int* retValue = (int*)malloc(sizeof(int));
    if (retValue == NULL) {
        exit(MALLOC_FAILURE);
    }
    *retValue = 0;
    while ((ret = scanf("%d %ms", &number, &text)) == 2) {
        if (number < 0) {
            *retValue = 1;
            free(text);
            return (void*)retValue;
        }
        input_t* new_input = (input_t*)malloc(sizeof(input_t));
        if (new_input == NULL) {
            exit(MALLOC_FAILURE);
        }
        new_input->number = number;
        new_input->text = text;
        pthread_mutex_lock(&mutex);
        pushEnd(list, new_input);
        pthread_mutex_unlock(&mutex);
        sem_post(&semaphore);
        free(new_input);
    }
    if (ret != 2 && ret != EOF) {
        *retValue = 1;
    }
    pthread_mutex_lock(&mutex);
    producerFinished = true;
    pthread_mutex_unlock(&mutex);
    return (void*)retValue;
}

void* consumerFunc(void* arg) {
    int threadNum = *(int*)arg;
    while (1) {
        pthread_mutex_lock(&mutex);
        if (isEmpty(list) && producerFinished) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);
        sem_wait(&semaphore);
        pthread_mutex_lock(&mutex);
        input_t* output = pop(list);
        pthread_mutex_unlock(&mutex);
        if (output == NULL) {
            free(arg);
            return NULL;
        }
        int allocSize = THREAD_CHARS + WHITESPACE + THREAD_NUM_CHARS + COLON_CHAR + output->number + strlen(output->text) * output->number;
        char* finalOutputStr = (char*)malloc(allocSize + ZERO_CHAR);
        if (finalOutputStr == NULL) {
            printf("Thread %d:", threadNum);
            for (int i = 0; i < output->number; ++i) {
                printf(" %s", output->text);
            }
            printf("\n");
        } else {
            sprintf(finalOutputStr, "Thread %d:", threadNum);
            long int strIdx = strlen(finalOutputStr);
            for (int i = 0; i < output->number; ++i) {
                finalOutputStr[strIdx++] = ' ';
                for (int j = 0; j < strlen(output->text); ++j) {
                    finalOutputStr[strIdx++] = output->text[j];
                }
            }
            finalOutputStr[strIdx++] = '\0';
            printf("%s\n", finalOutputStr);
            free(finalOutputStr);
        }
        free(output->text);
        free(output);
    }
    free(arg);
    return NULL;
}

int main(int argc, char* argv[]) {
    int numOfConsumers;
    if (argc > 1) {
        numOfConsumers = atoi(argv[1]);
    } else {
        numOfConsumers = 1;
    }
    int availableProcessors = sysconf(_SC_NPROCESSORS_ONLN);
    if (numOfConsumers < 1 || numOfConsumers > availableProcessors) {
        return EXIT_FAILURE;
    }

    list = createNewLL();

    sem_init(&semaphore, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_t producer;
    if (pthread_create(&producer, NULL, &producerFunc, NULL) != 0) {
        return EXIT_FAILURE;
    }

    pthread_t consumers[numOfConsumers];
    for (int i = 0; i < numOfConsumers; ++i) {
        int* var = malloc(sizeof(int));
        if (var == NULL) {
            return MALLOC_FAILURE;
        }
        *var = i + 1;
        if (pthread_create(&consumers[i], NULL, &consumerFunc, var) != 0) {
            return EXIT_FAILURE;
        }
    }

    int* retValue;
    if (pthread_join(producer, (void**)&retValue) != 0) {
        return EXIT_FAILURE;
    }
    for (int i = 0; i < numOfConsumers; ++i) {
        sem_post(&semaphore);
    }
    int ret = *retValue;
    free(retValue);

    for (int i = 0; i < numOfConsumers; ++i) {
        if (pthread_join(consumers[i], NULL) != 0) {
            return EXIT_FAILURE;
        }
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&semaphore);

    freeLL(list);

    return ret;
}
