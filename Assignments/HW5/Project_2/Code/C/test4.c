//
// Created by Eve Liang on 4/9/23.
//

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mutex_chair;
sem_t ta, stu;
void *thread_ta();
void *thread_stu(void *arg);
int chair = 3;

#define p(x) sem_wait(&x)
#define v(x) sem_post(&x)

int n;
int pass = 0;
int leave = 0;

int main()
{

    scanf("%d", &n);
    //printf("we have received %d", n);

    sem_init(&ta, 0, 1);
    sem_init(&stu, 0, 0);

    pthread_t ta_tid;
    pthread_t stu_tid[n];

    pthread_create(&ta_tid, NULL, thread_ta, NULL);
    int i;
    for (i = 0; i < n; i++)
    {

        pthread_create(&stu_tid[i], NULL, thread_stu, &i);
        sleep(1);
    }
    pthread_join(ta_tid, NULL);
    for (int i = 0; i < n; i++)
    {
        pthread_join(stu_tid[i], NULL);
    }

    return 0;
}

void *thread_ta(void)
{
    printf("this is in the office hour");
    while (1)
    {
        p(stu);
        pthread_mutex_lock(&mutex_chair);
        chair++;
        pthread_mutex_unlock(&mutex_chair);
        v(ta);
        pass++;
        printf("now we have the %d thta assistance done\n\n", pass);

        if (chair == 3)
        {
            printf("*****no more student, the TA can sleep!*****\n\n");
            if (pass + leave == n)
            {
                printf("well done!\n");
                break;
            }
        }

        sleep(2);
    }
}

void *thread_stu(void *arg)
{

    int stu_no = *(int *)arg;
    stu_no = stu_no + 1;
    printf("----the %d th student is comming\n", stu_no);
    pthread_mutex_lock(&mutex_chair);
    if (chair <= 0)
    {
        printf("no more chair for waiting! The %d the student leave\n\n", stu_no);
        leave++;
        pthread_mutex_unlock(&mutex_chair);
    }
    else if (chair > 0)
    {
        chair--;
        printf("the %d th sit on the chair\n\n", stu_no);
        v(stu);
        pthread_mutex_unlock(&mutex_chair);

        p(ta);

        sleep(2);
    }
}
