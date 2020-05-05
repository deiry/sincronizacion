 ￼
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "concurrent_linked_list.h"

void list_init(list_t *l) {
    l->head = NULL;
    pthread_mutex_init(&l->lock, NULL);
}

void list_insert(list_t *l, int key, book *b) {
    // synchronization not needed
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) {
        perror("malloc");
        return;
    }
    new->key = key;
    new->book = b;
    pthread_mutex_lock(&l->lock); //I don't know
    new->next = l->head;
    l->head = new;
    pthread_mutex_unlock(&l->lock);
    new->available = 1;
 }

 int list_lookup(list_t *l, int key) {
    int rv = -1;
    pthread_mutex_lock(&l->lock);    
    node_t *curr = l->head;
    while (curr) {
        if (curr->key == key) {
            if(curr->available == 1){
                curr->available = 0;
                rv = 1;
            }else{
                rv = 0;
            }
            break;
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&l->lock);
    return rv;
}

void books_init(list_t *l){
    printf("Initializing list of available books\n");
    for (int i = 0; i < 10000; i++)
    {
        char name_construction[10];
        book *b = malloc(sizeof(book));
        sprintf(name_construction, "book_%d", i);
        b->id = i;
        b->name = name_construction;
        b->num_pages = 100;
        b->pub_year = 2020;
        list_insert(l,i,b);
    }
}