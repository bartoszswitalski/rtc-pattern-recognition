#include "pqueue.hpp"

int main() {
    int shmidB = shmget(KEY_B, sizeof(PQueue<ProcessedValue>), 0);
    PQueue<ProcessedValue> *pqB = (PQueue<ProcessedValue> *)shmat(shmidB, NULL, 0);

    while(true) {
        ProcessedValue v;

        down(pqB->getSemid(), FULL);
        down(pqB->getSemid(), BIN);

        v = pqB->pop();
        std::cout << "[DISP] got value: " << v.data << std::endl;

        up(pqB->getSemid(), BIN);
        up(pqB->getSemid(), EMPTY);

    }
}