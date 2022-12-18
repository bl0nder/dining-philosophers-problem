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
    semStruct* arg = args;
    printf("Hello world\n");
    printf("%d\n", arg->semNumber);
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
        semStruct* args = malloc(sizeof(semStruct));
        args -> semNumber = i;
        pthread_create(&philosophers[i], NULL, doSomething, (void*) args);
        free(args);
    }

    return 0;
}
