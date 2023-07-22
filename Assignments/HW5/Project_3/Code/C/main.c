//
// Created by Eve Liang on 3/26/23.
//
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

/*    p0   p1   p2
        p3   p4
 */


void pickup(int i);
void putdown(int i);
void test(int i);
void *runner(void *param); /* threads call this function */

pthread_mutex_t mutex;
pthread_cond_t cond_var[5];

int eating_number;

// monitor DiningPhilosophers
enum {THINKING, HUNGRY, EATING} state[5];

// pi hungry, pi want to pickup if yes state --> EAT
void pickup(int i){
    pthread_mutex_lock(&mutex);
    state[i] = HUNGRY;
    test(i);
    while (state[i] != EATING) {
        //self[i].wait();
        //printf("Philosopher%d is HUNGRY and waiting to pick up.\n", i);
        pthread_cond_wait(&cond_var[i], &mutex);
    }
    pthread_mutex_unlock(&mutex);
}

// check pi whether can eat
void test(int i){
    if ((state[(i + 4) % 5] != EATING) &&
    (state[i] == HUNGRY) && (state[(i + 1) % 5] != EATING)){
        state[i] = EATING;
        pthread_cond_signal(&cond_var[i]);                    // self[i].signal();
    }
}

// putdown, pi change to think, and check neighbour pi+1, p-1 whether want to pickup
void putdown(int i){
    pthread_mutex_lock(&mutex);
    state[i] = THINKING;
    test((i + 4) % 5);
    test((i + 1) % 5);
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char *argv[]) {
    if (argc != 2){
        fprintf(stderr,"Please use the command format: <the number of philosophers eating times>\n");
        return -1;
    }
    eating_number = atoi(argv[1]);
    int index[5];

    pthread_t tid[5]; /* the thread identifier */
    pthread_attr_t attr; /* set of the thread attributes */

    /* set the default attributes of the thread */
    pthread_attr_init(&attr);// create and initialize a thread's attribute structure

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 5; i++) {
        state[i] = THINKING;
        pthread_cond_init(&cond_var[i], NULL);
    }

    //  create the thread
    for (int i = 0; i < 5; i++) {
        index[i] = i;
        pthread_create(&tid[i], &attr, runner, &index[i]); // create a new thread
    }

    /* wait for the thread to exit */
    for (int i = 0; i < 5; i++) {
        pthread_join(tid[i], NULL); // Wait for a specific thread to exit4
    }

    return 0;
}

void *runner(void *param){
    int i = *((int *) param);
    int count = 0;
    int time; // sleep for a random period between one and three seconds.
    while (count < eating_number){
        count++;
        printf("Philosopher%d is thinking in %d times.\n", i, count);
        time = rand() % 3 + 1;
        sleep(time);
        printf("Philosopher%d is ending %d times thinking, time is %d seconds\n", i, count, time);
        printf("Philosopher%d is hungry now.\n", i);
        pickup(i);
        printf("Philosopher%d is pickup chopsticks and eating in %d times\n", i, count);
        time = rand() % 3 + 1;
        sleep(time);
        printf("Philosopher%d is ending %d times of eating.\n", i, count);
        putdown(i);
        printf("Philosopher%d is put down chopsticks.\n", i);

    }

    pthread_exit(0);
}

