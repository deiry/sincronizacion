#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include "counter.h"

//#define NUMTHREADS 4
//#define MAXCNT 100

/* structs */
counter_t counter;



/* start_routine header */
void * start_routine(void *);

/* Global variables */
int MAXCNT;
int NUMTHREADS;


int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Ingrese todos los argumentos\n");
        exit(0);
    }
    MAXCNT = atoi(argv[1]);
    NUMTHREADS = atoi(argv[2]);

    struct timeval ti, tf;

    init(&counter);

    double tiempo;
    pthread_t tid[NUMTHREADS];
    int i = 0;

    gettimeofday(&ti, NULL);
    for (i = 0; i < NUMTHREADS; i++)
    {
        pthread_create(&tid[i], NULL, &start_routine, NULL);
    }
    for (i = 0; i < NUMTHREADS; i++)
    {
        pthread_join(tid[i], NULL);
    }

    gettimeofday(&tf, NULL); // Instante final
    //destroy(&counter);
    tiempo = (tf.tv_sec - ti.tv_sec) * 1000 + (tf.tv_usec - ti.tv_usec) / 1000.0;
    
    printf("\nHilos %d - Tiempo %f\n", NUMTHREADS,  tiempo);
    printf("Valor del contador: %d\n", get(&counter));
    printf("Contador debería ser: %d\n", MAXCNT*NUMTHREADS);
 
    return 0;
}

/* Function Thread*/
void * start_routine(void *unused)
{
    int i= 0;
    int current = get(&counter);
    printf("Value counter %d",current);


    do{
        increment(&counter);
    }while(current < MAXCNT);

    /*for(i=0; i < MAXCNT; i++){
         increment(&counter);
    }*/
   

    return NULL;
}

