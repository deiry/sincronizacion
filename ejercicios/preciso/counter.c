#include <stdio.h>
#include <pthread.h>
#include "counter.h"

void init(counter_t *c) {
    c->value = 0;
    if(pthread_mutex_init(&c->lock, NULL) != 0){
        printf("%s","Mutex init failed \n");
    }
}

void increment(counter_t *c) {
  
    pthread_mutex_lock(&c->lock);
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

void destroy(counter_t *c){
    pthread_mutex_destroy(&c->lock);
}
    

