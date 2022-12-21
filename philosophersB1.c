#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int forks[5];
int sauceBowls;

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

void getSauceBowl(int philNum) {

    //Wait for a free sauce bowl and take one whenever it becomes available
    while (sauceBowls < 1) {
        continue;
    }

    printf("Philosopher %d has a sauce bowl\n", philNum);
    sauceBowls -=1;
    sleep(1);   //Let operation of taking sauce bowl take 1 sec - clearly shows that a philosopher proceeds to eat only if they have a sauce bowl as is required
}

void eat(int philNum) {

    //Using if-else conditions for strict ordering of resource requests (elaborated in coresponding report)
    if (philNum == 4) {
        //Wait for right fork to be free
        while (forks[getRightFork(philNum)] != 0) {
            continue;
        }

        forks[getRightFork(philNum)] = 1;

        //Wait for left fork to be free
        while (forks[getLeftFork(philNum)] != 0) {
            continue;
        }

        forks[getLeftFork(philNum)] = 1;

        //Atomic operation of eating - 1 seconds (say)
        printf("Philosopher %d is eating\n", philNum);
        sleep(1);


    }

    else {
        while (forks[getLeftFork(philNum)] != 0) {
            continue;
        }

        forks[getLeftFork(philNum)] = 1;


        // sem_wait(&forks[getRightFork(philNum)]);
        while (forks[getRightFork(philNum)] != 0) {
            continue;
        }

        forks[getRightFork(philNum)] = 1;

        //Atomic operation of eating - 1 seconds (say)
        printf("Philosopher %d is eating\n", philNum);
        sleep(1);
    }

    forks[getLeftFork(philNum)] = 0;
    forks[getRightFork(philNum)] = 0;
    sauceBowls += 1;  

    printf("Philosopher %d has left the sauce bowl\n", philNum);    //Message to notify user of free sauce bowls (helps in checking program's functioning)
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
        getSauceBowl(philNum);  //Trying to get sauce bowl before eating since philosophers cannot eat without sauce in this part of the question
        eat(philNum);
    }

    return 0;
}

int main() {
    pthread_t philosophers[5];

    sauceBowls = 2;

    for (int i=0; i<5; i++) {
        forks[i] = 0;
    }

    //Start threads so that each philosopher does something - thinks, eats or gets a sauce bowl
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

