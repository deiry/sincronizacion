#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include "counter.h"


/* structs */
 counter_t counter;


// code here (if you required it)...

/* start_routine header */
void do_nothing();
void init(counter_t *c);
void* increment(void *c);
void decrement(counter_t *c);
int get(counter_t *c);

/* Global variables */
int MAXCNT;
int NUMTHREADS;
char *x, *y;
int main(int argc, char *argv[]) { 

    if(argc < 3){
        printf("Ingrese todos los argumentos\n");
        exit(0);
    }
    MAXCNT =  atoi(argv[1]);
    NUMTHREADS = atoi(argv[2]);

    printf("Max cont %d Num threads %d\n",MAXCNT,NUMTHREADS);

    /* Declaration of struct timeval variables */
    struct timeval ti, tf;


    /* Initializing conter */
    init(&counter);
    double tiempo;
  

    /* Threads handlers */
     pthread_t hilo[NUMTHREADS];


    /* Thread creation */
    

    /* Time starts counting */
    gettimeofday(&ti, NULL); 



    /* Creating a Threads */
    for(int i=0 ; i < NUMTHREADS ; i++){   
        int count = get(&counter);
        printf("%s %d \n", "Antes del if ",count);
             pthread_create(&hilo[i], NULL,(void *)increment, &counter);
     
       
    };

   

    /* Threads joins */
    for(int j = 0; j < NUMTHREADS; j++){
         printf("%s","join thread\n");
        pthread_join(hilo[j], NULL);
    }


    /* Time stops counting here */
    gettimeofday(&tf, NULL);   // Instante final


    /* get the end time */
    
     tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
    

    /* get the elapset time (end_time - start_time) */
    // code here...


    /* print the results (number threads employed, counter value, elasep time) */
    printf("%lf", tiempo);


    return 0;
}

/* start_routine definition */
void do_nothing(){
    int z;
    pthread_exit(NULL);
}

void init(counter_t *c) {
    c->value = 0;
    pthread_mutex_init(&c->lock, NULL);
    printf("%s","init lock\n");
}

void* increment(void *param) { 
    counter_t *c = (struct counter_t *)param;
    printf("%s","antes lock metodo increment\n");
    
    pthread_mutex_lock(&c->lock);
    printf("%s","metodo increment\n");
    c->value++;
    pthread_mutex_unlock(&c->lock);
}

void decrement(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    c->value--;
    pthread_mutex_unlock(&c->lock);
}

int get(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    return c->value;
    pthread_mutex_unlock(&c->lock);
}