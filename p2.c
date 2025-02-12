#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>

#define THINKING 0
#define HUNGRY 1
#define EATING 2

int N;
int *state;
sem_t mutex;
sem_t *s;

void *philosopher(void *arg);
void take_forks(int i);
void put_forks(int i);
void test(int i);

void *philosopher(void *arg) {
    int i = *((int *)arg);
    for (int j = 0; j < 5; j++) {
        
        printf("Philosopher %d is thinking.\n", i + 1);
        sleep(1);
        take_forks(i);
        
        printf("Philosopher %d is eating.\n", i + 1);
        sleep(2);
        put_forks(i);
    
    }
    pthread_exit(NULL);
}

void take_forks(int i) {
    sem_wait(&mutex);
    state[i] = HUNGRY;
    test(i);
    sem_post(&mutex);
    sem_wait(&s[i]);
}

void put_forks(int i) {
    sem_wait(&mutex);
    int check = rand() % 100;
    printf("Philosopher %d has finished %d%% eating.\n", i + 1, check);

    //helps to avoid "fork not release" deadlock
    while (check < 50) {
        printf("Philosopher %d will not release the forks and will continue eating.\n", i + 1);
        check = rand() % 100;
        printf("Philosopher %d has finished %d%% eating.\n", i + 1, check);
    }

    printf("Philosopher %d will release the forks.\n", i + 1);
    state[i] = THINKING;
    test((i + N - 1) % N);
    test((i + 1) % N);
    sem_post(&mutex);
}

void test(int i) {
    if (state[i] == HUNGRY && state[(i + N - 1) % N] != EATING && state[(i + 1) % N] != EATING) {
        state[i] = EATING;
        sem_post(&s[i]);
    }
}

int main() {
    srand(time(NULL));
    printf("Enter the number of philosophers: ");
    scanf("%d", &N);

    while (N % 2 == 0) {
        printf("Please enter an odd number: ");
        scanf("%d", &N);
    }

    state = (int *)malloc(N * sizeof(int));
    s = (sem_t *)malloc(N * sizeof(sem_t));

    sem_init(&mutex, 0, 1);

    for (int i = 0; i < N; i++) {
        state[i] = THINKING;
        sem_init(&s[i], 0, 0);
    }

    pthread_t tid[N];
    int pid[N];

    for (int i = 0; i < N; i++) {
        pid[i] = i;
        pthread_create(&tid[i], NULL, philosopher, &pid[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(tid[i], NULL);
    }

    sem_destroy(&mutex);
    for (int i = 0; i < N; i++) {
        sem_destroy(&s[i]);
    }

    free(state);
    free(s);

    return 0;
}

