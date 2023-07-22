# Project 3 The Dining-Philosophers Problem

In Section 7.1.3, we provide an outline of a solution to the dining-philosophers problem using
monitors. This project involves implementing a solution to this problem using either POSIX mutex
locks and condition variables of Java condition variables. Solutions will be based on the algorithm
illustrated in Figure 7.7.

```c
monitor DiningPhilosophers
{
  enum {THINKING, HUNGRY, EATING} state[5];
  condition self[5];
  
  void pickup(int i){
    state[i] = HUNGRY;
    test(i);
    if (state[i] != EATING)
      self[i].wait();
  }
  
  void putdown(int i){
    state[i] = THINKING:
    test((i + 4) % 5);
    test((i + 1) % 5);
  }
  
  void test(int i){
    if (state[(i + 4) % 5] != EATING && 
        (state[i] == HUNGRY) &&
        (state[(i + 1) % 5] != EATING)){ // The philosopher left and right has not eating
      state[i] = EATING;
      self[i].signal();
    }
  }
  
  initialization_code()
    for (int i = 0; i < 5; i++){
      state[i] = THINKING;
    }
}
```

Both implementations will require creating five philosophers, each identified by a number 0 . . . 4.
Each philosopher will run as a separate thread. Philosophers alternate between thinking and eating.
To simulate both activities, have each thread sleep for a random period between one and three
seconds.

https://www.programiz.com/c-programming/c-enumeration

### POSIX

Thread creation using Pthreads is covered in Section 4.41. When a philosopher wishes to eat, she invokes the function

```
pickup_forks(int philosopher_number)
```

where `philosopher_number` identifies the number of the philosopher wishing to eat. When a philosopher finishes eating, she invokes

`return_forks(int philosopher_number)`

Your implementation will require the use of POSIX condition variables, which are covered in Section 7.3

```c
#include <pthread.h>
#include <stdlib.h>

#include <stdlib.h>

int sum; /* this data is shared by the threads(s) */
void *runner(void *param);/* threads call this funciton*/

int main(int argc, char *argv[]){
  pthread_t tid; /* the thread identifier */
  pthread_attr_t attr; /* set of thread attributes */
  
  /* set the default attributes of the thread */
  pthread_attr_init(&attr); // Create and initialize a thread's attribute structure
  
  /* create the thread */
  pthread_create(&tid, &attr, runner, argv[1]); // create a new thread
  
  /* wait for the thread to exit */
  pthread_join(tid, NULL); // Wait for a specific thread to exit4
  
  printf("sum = %d\n", sum);
  
}

/* The thread will execute in this function */
void *runner(void *param){
  int i, upper = atoi(param); // convert param to integer
  sum = 0;
  
  for (i = 1, i <= upper; i++)
    sum += i;
  
  pthread_exit(0);
  
}
```



POSIX Threads

`pthread_create`: create a new thread

`pthread_exit`: Terminate the calling thread

`pthread_join`: Wait for a specific thread to exit

`pthread_yield`: Release the CPU to let another thread run

`pthread_attr_init`: Create and initialize a thread's attribute structure

`pthread_attr_destroy`: Remove a thread's attribute structure



pthread lib 



从某种角度上看, 这种互斥性也是一种原子性(atomic), 即线程在临界区的执行过程中, 不会出现只执行了一部分, 就被打断并且切换到其他线程执行的情况. 即, 要么线程执行的这一系列操作/指令都完成, 要么这一系列操作/治理都不做, 不会出现指令序列执行中被打断的情况.

