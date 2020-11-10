#include "pqueue.hpp"

int main() {
    PQueue<ImageRaw> *pqA = setSHM<ImageRaw>(PQ_A);
    PQueue<ProcessedValue> *pqB = setSHM<ProcessedValue>(PQ_B);

    setSemaphores();

    return 0;
}
