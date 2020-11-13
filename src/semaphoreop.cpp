#include "semaphoreop.hpp"

void up(int semid, int semnum) {
    buf.sem_num = semnum;
    buf.sem_op = 1;
    buf.sem_flg = 0;

    if (semop(semid, &buf, 1) == -1) {
        std::cout << "Semaphore up" << std::endl;
        exit(1);
    }
}

void down(int semid, int semnum) {
    buf.sem_num = semnum;
    buf.sem_op = -1;
    buf.sem_flg = 0;

    if (semop(semid, &buf, 1) == -1) {
        std::cout << "Semaphore down" << std::endl;
        exit(1);
    }
}
