#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include "counter.h"

#define THRESHOLD 1024

/* structs */
counter_t counter;

/* start_routine header */
void * start_routine(void *);

/* Global variables */
int MAXCNT;
int NUMTHREADS;

int main(int argc, char *argv[]) { 

        if (argc < 3)
    {
        printf("Ingrese todos los argumentos\n");
        exit(0);
    }
    /* get the command's line parameters */
    MAXCNT = atoi(argv[1]);
    NUMTHREADS = atoi(argv[2]);


    /* Declaration of struct timeval variables */
    struct timeval ti, tf;


    /* Initializing conter */
     init(&counter, THRESHOLD);


    /* Threads handlers */
    // code here...


    /* Thread creation */
    double tiempo;
    pthread_t tid[NUMTHREADS];
    int i = 0;


    /* Time starts counting */
    gettimeofday(&ti, NULL);


    /* Creating a Threads */
    for (i = 0; i < NUMTHREADS; i++)
    {
        pthread_create(&tid[i], NULL, &start_routine, NULL);
    }
   

    /* Threads joins */
    for (i = 0; i < NUMTHREADS; i++)
    {
        pthread_join(tid[i], NULL);
    }


    /* Time stops counting here */
    gettimeofday(&tf, NULL); 

   


    /* get the end time */
    // code here...
    

    /* get the elapset time (end_time - start_time) */
    tiempo = (tf.tv_sec - ti.tv_sec) * 1000 + (tf.tv_usec - ti.tv_usec) / 1000.0;


    /* print the results (number threads employed, counter value, elasep time) */
    printf("\nHilos %d - Tiempo %f\n", NUMTHREADS,  tiempo);
   
    printf("Valor del contador: %d\n",get(&counter));
    printf("Contador debería ser: %d\n", MAXCNT);


    return 0;
}

/* start_routine definition */
void * start_routine(void * param){
        
        while(get(&counter) < MAXCNT){
            printf("Value counter %d\n",get(&counter));
            update(&counter,pthread_self(),1);
        }  


}





