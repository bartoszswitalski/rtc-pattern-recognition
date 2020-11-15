#include "pqueue.hpp"

int main() {
    int semid_A = semget(SKEY_A, SEM_NUM, IPC_CREAT | 0600);
    int semid_B = semget(SKEY_B, SEM_NUM, IPC_CREAT | 0600);

    PQueue<ImageRaw> *pqA = setSHM<ImageRaw>(PQ_A);
    PQueue<ProcessedValue> *pqB = setSHM<ProcessedValue>(PQ_B);

    semctl(semid_A, FULL, SETVAL, 0);
    semctl(semid_B, FULL, SETVAL, 0);

    semctl(semid_A, EMPTY, SETVAL, CAP);
    semctl(semid_B, EMPTY, SETVAL, CAP);

    semctl(semid_A, BIN, SETVAL, 1);
    semctl(semid_B, BIN, SETVAL, 1);

    return 0;
}
