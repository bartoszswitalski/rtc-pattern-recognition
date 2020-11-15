#include "pqueue.hpp"

int main() {
    int shmidA = shmget(KEY_A, sizeof(PQueue<ImageRaw>), 0);
    int shmidB = shmget(KEY_B, sizeof(PQueue<ProcessedValue>), 0);

    PQueue<ImageRaw> *pqA = (PQueue<ImageRaw> *)shmat(shmidA, NULL, 0);
    PQueue<ProcessedValue> *pqB = (PQueue<ProcessedValue> *)shmat(shmidB, NULL, 0);

    shmctl(KEY_A, IPC_RMID, NULL);
    shmctl(KEY_B, IPC_RMID, NULL);

    shmctl(SKEY_A, IPC_RMID, NULL);
    shmctl(SKEY_B, IPC_RMID, NULL);

    semctl(pqA->getSemid(), BIN, IPC_RMID);
    semctl(pqA->getSemid(), EMPTY, IPC_RMID);
    semctl(pqA->getSemid(), FULL, IPC_RMID);

    semctl(pqB->getSemid(), BIN, IPC_RMID);
    semctl(pqB->getSemid(), EMPTY, IPC_RMID);
    semctl(pqB->getSemid(), FULL, IPC_RMID);

    return 0;
}
