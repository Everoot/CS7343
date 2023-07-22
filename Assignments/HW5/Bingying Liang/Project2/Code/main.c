// Created by Eve Liang on 3/26/23.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>

int ta_teaching_time;
int s_visit_time;
int s_leave_time;

int chair_num;
int ta_num;
int student_num;

sem_t student_sem;
sem_t ta_sem;

sem_t mutex;
sem_t s_mutex;
sem_t t_mutex;

int i, j, k;

int working_ta = 1;
int waiting_students = 0;

int leave_cnt = 0;
int served_cnt = 0;
int ta_serve_cnt[50] = {0};
void msleep(int tms);

void set_useed(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_sec + tv.tv_usec);
}
void *TA(void *tid_){
    while (1)
    {
        set_useed();
        long tid = (long)tid_;

        sem_wait(&student_sem);
        sem_wait(&mutex);
        waiting_students--;
        printf("TA start teaching.\n");
        printf("The number of waiting students: %d\n", waiting_students);
        sem_post(&mutex);
        set_useed();
        ta_teaching_time = rand() % 1001;
        msleep(ta_teaching_time);

        int current_served_cnt;
        sem_wait(&t_mutex);
        served_cnt++;
        current_served_cnt = served_cnt;
        ta_serve_cnt[tid]++;
        sem_post(&t_mutex);

        printf("%dth arrived student finishes.", current_served_cnt);
        printf("This time TA service time is: %d\n", ta_teaching_time);
        sem_post(&ta_sem);
        printf("TA if no students will sleep\n");

    }
}

void *student(void *sid_){
    s_leave_time = rand() % 21;
    long sid = (long)sid_;
    printf("%ldth students come here\n", sid);

    sem_wait(&mutex);    // for waiting_students
    sem_wait(&s_mutex);

    if (waiting_students == chair_num){
        leave_cnt++;

        printf("There is no seats, %ldth student leave:%d\n", sid, leave_cnt);
        /* free mutexes */
        sem_post(&s_mutex);
        sem_post(&mutex);
    }
    else{
        waiting_students++;
        printf("%ldth student has chair, sit down. The waiting student number is:%d\n", sid, waiting_students);

        int student_value;

        /* free mutexes */
        sem_post(&s_mutex);
        sem_post(&mutex);

        sem_post(&student_sem);

        sem_wait(&ta_sem);
    }

    msleep(s_leave_time);
}

void msleep(int tms){
    struct timeval tv;

    tv.tv_sec = tms / 1000;
    tv.tv_usec = (tms % 1000) * 1000;
    select(0, NULL, NULL, NULL, &tv);
}

int main(int argc, char *argv[]){

    chair_num = 4; // one in office, the other three hallway
    ta_num = 1;

    student_num = atoi(argv[1]);

    if (argc != 2){
        fprintf(stderr, "Please use the command format: <file> <number of students>");
    }

    pthread_t ta_thread[ta_num], student_thread[student_num];

    sem_init(&ta_sem, 0, 0);
    sem_init(&student_sem, 0, 0);

    sem_init(&mutex, 0, 1);
    sem_init(&s_mutex, 0, 1);
    sem_init(&t_mutex, 0, 1);


    for (i = 1; i <= ta_num; i++)
    {
        pthread_create(&ta_thread[i], NULL, TA, (void *) (long) (i));
    }

    for (i = 1; i <= student_num; i++)
    {
        s_visit_time = rand() % 500000 / 2;
        printf("(create)student_visit_time:%d,usleeping...\n", s_visit_time);
        usleep(s_visit_time);
        pthread_create(&student_thread[i], NULL, student, (void *) (long) (i));

    }

    for (i = 1; i <= student_num; i++)
    {
        pthread_join(student_thread[i], NULL);
    }

    printf("All students has finished. TA sleep\n");

    return 0;

}
