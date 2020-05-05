#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "concurren_linked_list.h"
#include <sys/time.h>

typedef struct __office_results {
    int successful_loan;
    int failed_loan;
} office_results;

typedef struct __office{
    int id;
    int seed;
    office_results *results;
} office;

list_t books;
void *lend_books(void *offc);

int main(){
    struct timeval ti, tf;
    double time;
    list_init(&books);
    books_init(&books);
    pthread_t offices[4];
    office *office_info[4];
    int total_success = 0, total_fails = 0;

    
    for (int i = 0; i < 4; i++)
    {
        office *offc = malloc(sizeof(office));
        offc->id = i;
        offc->seed = (int)rand();
        offc->results = malloc(sizeof(results));
        office_info[i] = offc;
        printf("Office %d initialized with seed %d\n", i, offc->seed);
    }
    


    /* Time starts counting */
    gettimeofday(&ti, NULL);

   
    for (int i = 0; i < 4; i++)
    {
        pthread_create(&offices[i], NULL, &lend_books,office_info[i]);
    }
    

    for (int i = 0; i < 4; i++)
    {
        pthread_join(offices[i], NULL);
        printf("Office %d has finished its workload, successful loans %d, failed loans %d\n",i,office_info[i]->results->successful_loan,office_info[i]->results->failed_loan);
        total_success = total_success + office_info[i]->results->successful_loan;
        total_fails = total_fails + office_info[i]->results->c;
    }
    
    
    /* time ends */
    gettimeofday(&tf, NULL); 

    /* get the elapset time (end_time - start_time) */
    time = (tf.tv_sec - ti.tv_sec) * 1000 + (tf.tv_usec - ti.tv_usec) / 1000.0;
    printf("Simulation done! execution time: %g ms\n",time);
    printf("Total successful loans %d, total failed loans %d\n",total_success, total_fails);
    printf("Number of remaining available books %d\n", 10000 - total_success);
    return 0;
}

void *lend_books(void *offc){
  office offc_info= *((office *)offc);
    int seed = offc_info.seed;
    srand(seed);
    for (int i = 0; i < 1000; i++)
    {
        int random_book = rand()%10000;
        int isAvailable = list_lookup(&books,random_book);
        if(isAvailable == 1){
            offc_info.results->successful_loan++;
        }else{
            offc_info.results->failed_loan++;
        }
    }
    return 0;  
}