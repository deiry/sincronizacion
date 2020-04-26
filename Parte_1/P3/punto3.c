#include <stdio.h>
#include <pthread.h>

#define NUMTHREADS 4
#define MAXCNT 10000000

/* Global variables - shared between threads */
double counter = 0;
pthread_mutex_t lock;

/* Declaring functions*/
void* counting(void *);

int main(void) {
  pthread_t tid[NUMTHREADS];
  int i=0;
  /* mutex init*/
  if (pthread_mutex_init(&lock, NULL) != 0)
  {
   printf("\n mutex init failed\n");
   return 1;
  }
  for( i=0; i<NUMTHREADS; i++){
     pthread_create (&tid[i], NULL, &counting, NULL);
  }
  for( i=0; i< NUMTHREADS; i++){
     pthread_join(tid[i], NULL);
  }
  /* mutex destroy*/
  pthread_mutex_destroy(&lock);
  printf("\nCounter must be in: %d\n", MAXCNT*NUMTHREADS);
  printf("\nCounter value is: %.0f\n\n", counter);
  return 0;
}

/* Function Thread*/
void* counting(void * unused) {
  int i=0;
  for(i=0; i<MAXCNT; i++){
     pthread_mutex_lock(&lock);
     counter++; // Región crítica
     pthread_mutex_unlock(&lock);
  }
  return NULL;
}





