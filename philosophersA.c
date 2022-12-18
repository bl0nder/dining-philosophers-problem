#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t forks[5];

typedef struct {
    int semNumber;
} semStruct;

int getLeftFork(int philNum) {
    return philNum;
}

int getRightFork(int philNum) {
    if (philNum == 0) {
        return 4;
    }
    return philNum-1;
}

void eat(int philNum) {

    if (philNum == 4) {

        //Wait for right fork to be free
        sem_wait(&forks[getRightFork(philNum)]);

        //Wait for left fork to be free
        sem_wait(&forks[getLeftFork(philNum)]); 

        //Atomic operation of acquiring both forks and then eating
        printf("Philosopher %d is eating\n", philNum);

        //Unlock right and left forks respectively
        sem_post(&forks[getRightFork(philNum)]);
        sem_post(&forks[getLeftFork(philNum)]);
    }
    else {

        sem_wait(&forks[getLeftFork(philNum)]);
        sem_wait(&forks[getRightFork(philNum)]);

        getLeftFork(philNum);
        getRightFork(philNum);
        printf("Philosopher %d is eating\n", philNum);
        
        sem_post(&forks[getLeftFork(philNum)]);
        sem_post(&forks[getRightFork(philNum)]);

    }
}

void think() {
    //Think for 1 second before trying to eat 
    sleep(1000);
}

void *doSomething(void* args) {
    semStruct* arg = args;
    
    //Test
    // printf("%d\n", arg->semNumber);

    //Perform eating and thinking operations
    while (1) {
        think();
        eat(arg->semNumber);
    }

    return 0;
}

int main() {
    pthread_t philosophers[5];

    for (int i=0; i<5; i++) {
        
        // //Add threads to thread array
        // pthread_t p;
        // philosophers[i] = p;

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
        
        //Args for function executed by thread
        semStruct* args = malloc(sizeof(semStruct));
        args -> semNumber = i;

        //Create thread
        int createErr = pthread_create(&philosophers[i], NULL, doSomething, (void*) args);

        //Error handling while creating thread
        if (createErr) {
            printf("Error in creating thread %d\n", i+1);
        }
    }

    for (int i=0; i<5; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}
