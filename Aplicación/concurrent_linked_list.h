#ifndef CONCURRENT_LINKED_LIST_H
#define CONCURRENT_LINKED_LIST_H
#include <stdio.h>
#include <pthread.h>

typedef struct __book {
 int id;
 char* name;
 int num_pages;
 int pub_year;
} book;

typedef struct __node_t {
 int key;
 int available;
 struct __book *book;
 struct __node_t *next;
} node_t;

typedef struct __list_t {
 node_t *head;
 pthread_mutex_t lock;
} list_t;

void list_init(list_t *l);
void list_insert(list_t *l, int key, book *b);
int list_lookup(list_t *l, int key);
void books_init(list_t *l);
#endif


