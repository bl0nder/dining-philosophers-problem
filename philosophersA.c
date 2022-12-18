#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
sem_t forks[5];

typedef struct {
    int semNumber;
} semStruct;

void eat() {

}

void think() {

}

void *doSomething(void* args) {
    int* temp = args;
    printf("Hello world\n");
    printf("%d\n", temp[0]);

    return NULL;
}

int main() {
    pthread_t philosophers[5];

    for (int i=0; i<5; i++) {
        
        //Add threads to thread array
        pthread_t p;
        philosophers[i] = p;

        //Create semaphores
        sem_t fork;
        forks[i] = fork;
    }

    //Initialise semaphores
    for (int i=0; i<5; i++) {
        sem_init(&forks[i], 0, 1);
    }

    //Start threads so that each philosopher does something - thinks or eats
    for (int i=0; i<5; i++) {
        // printf("test: %d\n", i);
        int *temp = &i;
        int createErr = pthread_create(&philosophers[i], NULL, doSomething, temp);

        if (createErr) {
            printf("Error in creating thread %d\n", i+1);
        }
    }

    return 0;
}
