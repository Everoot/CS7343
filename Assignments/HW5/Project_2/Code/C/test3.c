//
// Created by Eve Liang on 4/9/23.
//
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define MAX 10
#define TRUE 1
#define p(x) sem_wait(&x)
#define v(x) sem_post(&x)

sem_t customer,barber;
int chairs;
pthread_mutex_t mutex;

void init ( )
{
    sem_init ( &customer , 0 , 0 );
    sem_init ( &barber , 0 , 1 );
    chairs = MAX;
}

void* _barber ( )
{
    while ( TRUE )
    {
        p(customer);
        pthread_mutex_lock(&mutex);
        chairs++;
        pthread_mutex_unlock(&mutex);
        sleep(5);
        printf ( "one work done....\n" );
        v(barber);
    }
}

void* _customer ( void* arg )
{
    int *p = (int*) arg;
    int x = *p;
    pthread_mutex_lock(&mutex);
    if ( chairs > 0 )
    {
        chairs--;
        v(customer);
        printf ( "the %dth student sitting and waiting , %d customers wating...\n" , x , MAX-chairs );
        pthread_mutex_unlock(&mutex);
        p(barber);
    }
    else
    {
        pthread_mutex_unlock(&mutex);
        printf ( "the %dth student go away!\n" , x );
    }
}

int main ( ) {
    int i;
    init();
    pthread_t b;
    pthread_t pthreads[MAX * 100];
    int cid[MAX * 100];
    pthread_create(&b, NULL, _barber, NULL);
    for (i = 0; i < MAX * 100; i++) {
        sleep(1);
        cid[i] = i;
        pthread_create(&pthreads[i], NULL, _customer, &cid[i]);
    }
    pthread_join(b, NULL);
    for (i = 0; i < MAX * 100; i++)
        pthread_join(cid[i], NULL);

}