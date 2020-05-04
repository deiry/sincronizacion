#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include "counter.h"


/* structs */
counter_t counter;
/* start_routine header */
void *start_routine(void *);

/* Global variables */
int MAXCNT;
int NUMTHREADS;
pthread_mutex_t global_lock;


int main(int argc, char *argv[]) { 
  /* get the command's line parameters */
   if (argc < 3)
    {
        printf("Ingrese todos los argumentos\n");
        exit(0);
    }
    
    pthread_mutex_init(&global_lock, NULL);
    MAXCNT = atoi((char *) argv[1]);
    NUMTHREADS = atoi((char *) argv[2]);
    
    /* Declaration of struct timeval variables */
    struct timeval ti, tf;

    /* Initializing conter */
    init(&counter);

    /* Threads handlers */
    pthread_t threads[NUMTHREADS];

    /* Thread creation */
    int maxNumberThread = MAXCNT/NUMTHREADS;

    /* Time starts counting */
    gettimeofday(&ti, NULL);

    /* Creating a Threads */
    for(int i = 0; i < NUMTHREADS; i++){
      pthread_create(&threads[i], NULL, start_routine,maxNumberThread);
    }
   

    /* Threads joins */
    for (int i= 0; i < NUMTHREADS; i++) {
      pthread_join(threads[i], NULL);
    }

    /* get the end time */
    gettimeofday(&tf, NULL);
    

    /* get the elapset time (end_time - start_time) */
    long time = (tf.tv_sec - ti.tv_sec) * 1000 + (tf.tv_usec - ti.tv_usec) / 1000.0;
    
    /* print the results (number threads employed, counter value, elasep time) */
    printf("Número de hilos: %d y valor del contador: %d\n", NUMTHREADS, get(&counter));
    printf("Tiempo de ejecución: %ld ms \n", time);

    return 0;
}

/* start_routine definition */
void *start_routine(void * arg){
  
  int maxThread = (int)arg;
  pthread_mutex_lock(&global_lock);
  
  for(int i = 0; i < maxThread; i++){
    increment(&counter);
  }

  pthread_mutex_unlock(&global_lock);
  return 0;
}