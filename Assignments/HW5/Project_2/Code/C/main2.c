//
// Created by Eve Liang on 3/26/23.
//

#include <stdio.h>
#include <pthread.h>


#include <unistd.h>   // sleep
#include <stdlib.h>
#include <semaphore.h>

#define CHAIRS 3  // There are three CHAIRS in the hallway outside
#define TRUE 1

time_t end;

pthread_t TA;
pthread_t *S;


sem_t ta_sem;
sem_t students_sem;
sem_t chair_sem[CHAIRS];

pthread_mutex_t chairlock;

void *ta();
void *students(void *param);

int n_chair = 0;
int my_index = 0;

int main(int argc, char *argv[]){
    int n_students = atoi(argv[1]);
    int i;

    // Initializing
    sem_init(&ta_sem, 0, 0);
    sem_init(&students_sem, 0, 0);
    for (i = 0; i < 3; i++){
        sem_init(&chair_sem[i], 0, 0);
    }

    pthread_mutex_init(&chairlock, NULL);

    if (argc < 2){
        fprintf(stderr,"Please use the command format: <file name> <number of students> \n");
        return -1;
    }

    S = (pthread_t*) malloc(sizeof(pthread_t)*n_students);

    pthread_create(&TA, NULL, ta, NULL);
    for(i = 0; i < n_students; i++){
        pthread_create(&S[i], NULL, students, (void *) (long)i);

    }

    pthread_join(TA, NULL);
    for(i = 0; i < n_students; i++){
        pthread_join(S[i],NULL);
    }

    //
    free(S);
    return 0;

}


void *ta() {
    while(TRUE){
        sem_wait(&ta_sem);
        printf("TA is sleeping and awakened by a student.\n");

        while(TRUE){
            pthread_mutex_lock(&chairlock);

            if (n_chair == 0){
                pthread_mutex_unlock(&chairlock);
                break;
            }

            sem_post(&chair_sem[my_index]);
            n_chair--;
            printf("One student left the chair.\n");
            my_index = (my_index + 1) % 3;

            pthread_mutex_unlock(&chairlock);
            printf("TA is helping a student.\n");
            sleep(rand() % 5);
            sem_post(&students_sem);
            sleep(rand() % 5);
        }
    }
}

void *students(void *param) {
    int time;

    while(TRUE){
        printf("Student %ld is talking with TA.\n",(long) param);
        time = rand() % CHAIRS + 1;
        sleep(time);

        printf("Student %ld is talking with TA.\n", (long) param);

        pthread_mutex_lock(&chairlock);
        int count = n_chair;
        pthread_mutex_unlock(&chairlock);

        if (count < 3){
            if (count == 0){
                sem_post(&ta_sem);
            }else{
                printf("Student %ld is waiting.\n", (long) param);
            }

            pthread_mutex_lock(&chairlock);
            int newone = (my_index + n_chair) % 3;
            n_chair++;
            printf("There are %d chair empty.\n", 3 - n_chair);
            pthread_mutex_unlock(&chairlock);

            sem_wait(&chair_sem[newone]);
            printf("Student %ld is talking with TA\n", (long) param);
            sem_wait(&students_sem);
            printf("Student %ld finish.\n", (long) param);

        }else{
            printf("Student %ld will come to TA office later.\n", (long) param);
        }

    }

}
