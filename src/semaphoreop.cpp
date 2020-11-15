#include "semaphoreop.hpp"

void up(short unsigned int semid, short unsigned int semnum) {
    sembuf buf = {
        .sem_num = semnum,
        .sem_op = 1,
        .sem_flg = 0,
    };

    if (semop(semid, &buf, 1) == -1) {
        exit(1);
    }
}

void down(short unsigned int semid, short unsigned int semnum) {
    sembuf buf = {
        .sem_num = semnum,
        .sem_op = -1,
        .sem_flg = 0,
    };

    if (semop(semid, &buf, 1) == -1) {
        exit(1);
    }
}
