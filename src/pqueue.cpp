#include "pqueue.hpp"

void setSemaphores() {
    int semid_A, semid_B;

    semid_A = semget(SKEY_A, SEM_NUM, IPC_CREAT | 0600);
    semid_B = semget(SKEY_B, SEM_NUM, IPC_CREAT | 0600);

    semctl(semid_A, FULL, SETVAL, (int)0);
    semctl(semid_B, FULL, SETVAL, (int)0);

    semctl(semid_A, EMPTY, SETVAL, (int)CAP);
    semctl(semid_B, EMPTY, SETVAL, (int)CAP);

    semctl(semid_A, BIN, SETVAL, (int)1);
    semctl(semid_B, BIN, SETVAL, (int)1);
}