//
// Created by Eve Liang on 3/26/23.
//
#include <stdlib.h> /* required for rand() */
#include <unistd.h>
#include <stdio.h>
#include "buffer.h"
#define true 1

void *producer(void*param) {
    buffer_item item;
    while(true){
        sleep(rand() % BUFFER_SIZE);
        item = rand();
        if(insert_item(item))
            fprintf(stderr,"report error condition");
        else
            printf("Producer produced %d \n", item);


    }
}

void *consumer(void *param){
    buffer_item item;
    while(true){
        sleep(rand() % BUFFER_SIZE);
        if(remove_item(&item))
            fprintf(stderr, "report error condition");
        else
            printf("Consumer consumed %d\n", item);
    }
}