//
// Created by Eve Liang on 3/26/23.
//
#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#include "pcthreads.c"
#include "buffer.c"

#define TRUE 1

int main(int argc, char*argv[]) {
    /*  The `main()` function will be passed three parameters on the command line:
        1. How long to sleep before terminatin
        2. The number of producer threads
        3. The number of consumer threads
     */

    /* 1. Get command line arguments argv[1], argv[2], argv[3] */
    int sleepTime;
    int n_producer;  // n_producer thread
    int n_consumer;  // n_consumer thread
    int i, j;
    if (argc != 4) {
        fprintf(stderr,
                "Please use the command format: <How long to sleep before terminatin> <producer number> <consumer number>\n");
        return -1;
    }

    sleepTime = atoi(argv[1]);
    n_producer = atoi(argv[2]);
    n_consumer = atoi(argv[3]);

    /* 2. Initialize buffer */
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&empty, 0, BUFFER_SIZE);
    srand(time(0));

    /* 3. Create producer thread(s) */
    for (i = 0; i < n_producer; i++) {
        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, producer, NULL);
    }

    /* 4. Create n_consumer thread(s) */
    for (j = 0; j < n_consumer; j++) {
        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, consumer, NULL);
    }

    /* 5. Sleep */
    sleep(sleepTime);

    /* 6 Exit */
    return 0;
}

