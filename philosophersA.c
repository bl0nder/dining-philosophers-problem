#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t fork1 = 1;
sem_t fork2 = 2;
sem_t fork3 = 3;
sem_t fork4 = 4;
sem_t fork5 = 5;

sem_t forks[5] = {fork1, fork2, fork3, fork4, fork5};

void eat() {

}

void think() {

}

void *doSomething(void* args) {
    printf("%d\n", args[0]);
}

int main() {
    pthread_t philosophers[5];

    for (int i=0; i<5; i++) {
        
        //Add threads to thread array
        pthread_t p;
        philosophers[i] = p;

        //Initialise semaphores
        sem_init(&forks[i], 0, 1);
    }

    for (int i=0; i<5; i++) {
        //Start threads so that each philosopher does something - thinks or eats
        pthread_create(&philosophers[i], NULL, doSomething, (void*) i);


    }

    return 0;
}
