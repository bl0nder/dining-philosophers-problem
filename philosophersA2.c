#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t forks[5];

typedef struct {
    int semNumber;
} semStruct;

/*  Assumed order of philosophers (P0-P4) and forks (F0-F4):

        P0
      /    \
    F4      F0
  /            \
P4              P1
 \             /
  F3          F1
   \          /
    P3      P2
      \    /
        F2
*/

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

    //Using if-else conditions for strict ordering of resource requests (elaborated in coresponding report)

    if (philNum == 4) {
        //Wait for right fork to be free
        sem_wait(&forks[getRightFork(philNum)]);

        //Wait for left fork to be free
        sem_wait(&forks[getLeftFork(philNum)]);

        //Atomic operation of eating - 1 seconds (say)
        printf("Philosopher %d is eating\n", philNum);
        sleep(1);


    }

    else {
        sem_wait(&forks[getLeftFork(philNum)]);
        sem_wait(&forks[getRightFork(philNum)]);

        //Atomic operation of eating - 1 seconds (say)
        printf("Philosopher %d is eating\n", philNum);
        sleep(1);
    }


    //Unlock 
    sem_post(&forks[getLeftFork(philNum)]);
    sem_post(&forks[getRightFork(philNum)]);
    
}

void think(int philNum) {
    //Think for 1 second 
    printf("Philosopher %d is thinking\n", philNum);
    sleep(1);
}

void *doSomething(void* args) {
    semStruct* arg = args;

    //Perform eating and thinking operations
    while (1) {
        int philNum = arg -> semNumber;
        think(philNum);
        eat(philNum);
    }

    return 0;
}

int main() {
    pthread_t philosophers[5];

    for (int i=0; i<5; i++) {
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

    //Joining threads
    for (int i=0; i<5; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}
