//
// Created by Eve Liang on 3/26/23.
//
#include "buffer.h"

#include <pthread.h>
#include <semaphore.h>

/* the buffer */
buffer_item buffer[BUFFER_SIZE];

pthread_mutex_t mutex;   /*pthread mutex lock*/

/* semaphore data type */
sem_t empty; // buffer empty
sem_t full;  // buffer full

int insertIndex = 0;
int removeIndex = 0;

/* threads function */
void *producer(void *param);
void *consumer(void *param);


int insert_item(buffer_item item){
    /* insert item into buffer
    return 0 if successful, otherwise
    return -1 indicating an error condition */

    /* produce an item in next_produced */
    sem_wait(&empty); // wait(empty)
    pthread_mutex_lock(&mutex); // wait(mutex)

    /* add next_produced to the buffer */
    buffer[insertIndex] = item;
    insertIndex++;
    insertIndex = insertIndex % BUFFER_SIZE;

    pthread_mutex_unlock(&mutex); // signal(mutex)
    sem_post(&full); // signal(full)

    return 0;
}

int remove_item(buffer_item *item){
    /* remove an object from buffer
    placing it in item
    return 0 if successful, otherwise
    return -1 if indicating an error condition */
    sem_wait(&full);   // wait(full)
    pthread_mutex_lock(&mutex);  // wait(mutex)

    /* remove an item from buffer to next_consumed */
    *item = buffer[removeIndex];
    buffer[removeIndex] = -1;
    removeIndex++;
    removeIndex = removeIndex % BUFFER_SIZE;

    pthread_mutex_unlock(&mutex);  // signal(mutex)
    sem_post(&empty);       // signal(empty)

    /* consume the item in next_consumed */
    return 0;
}