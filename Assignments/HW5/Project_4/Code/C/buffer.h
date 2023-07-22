//
// Created by Eve Liang on 3/26/23.
//
/* buffer.h */
/* buffer fix array, statement of item; */
typedef int buffer_item;

/* The definition of the array size */
#define BUFFER_SIZE 5

/* The operation in the buffer, separately used for producer and consumer thread */
int insert_item(buffer_item item);
int remove_item(buffer_item *item);

