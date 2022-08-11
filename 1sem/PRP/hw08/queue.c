#include "queue.h"
 
/* creates a new queue with a given size */
queue_t* create_queue(int capacity)
{
    queue_t *tmp = malloc(sizeof(queue_t));
    tmp->cap = capacity;
    tmp->head_idx = tmp->tail_idx = 0;
    tmp->size = 0;
    tmp->dt = malloc(capacity * sizeof(void *));
    return tmp;
}
 
/* deletes the queue and all allocated memory */
void delete_queue(queue_t *queue)
{
    free(queue->dt);
    free(queue);
}
 
/*
 * inserts a reference to the element into the queue
 * returns: true on success; false otherwise
 */
bool push_to_queue(queue_t *queue, void *data)
{ 
    int temp_idx; 
    if(queue->size >= queue->cap){
       return false; 
    }
    temp_idx = (queue->tail_idx + 1) % queue->cap;
    queue->dt[queue->tail_idx] = data;
    queue->tail_idx = temp_idx;
    ++(queue->size);
    return true;
}
 
/*
 * gets the first element from the queue and removes it from the queue
 * returns: the first element on success; NULL otherwise
 */
void* pop_from_queue(queue_t *queue)
{
    void *temp_dt;  
    if(queue->size <= 0){
        return NULL;
    } 
    temp_dt = queue->dt[queue->head_idx];
    queue->dt[queue->head_idx] = NULL;
    ++(queue->head_idx);
    queue->head_idx %= queue->cap;
    --(queue->size);
    return temp_dt;
}
 
/*
 * gets idx-th element from the queue, i.e., it returns the element that 
 * will be popped after idx calls of the pop_from_queue()
 * returns: the idx-th element on success; NULL otherwise
 */
void* get_from_queue(queue_t *queue, int idx)
{
    int cur_idx = (queue->head_idx + idx) % queue->cap;
    if((idx < 0)||(idx >= queue->size)) {
        return NULL;
    } 
    if((queue->tail_idx > queue->head_idx)&&((cur_idx < queue->head_idx)||(queue->tail_idx <= cur_idx))){
        return NULL;
    } 
    if((queue->tail_idx < queue->head_idx)&&((queue->tail_idx <= cur_idx)&&(cur_idx < queue->head_idx))){
        return NULL;
    } 
    return queue->dt[cur_idx]; 
}
 
/* gets number of stored elements */
int get_queue_size(queue_t *queue)
{
    return queue->size;
}
