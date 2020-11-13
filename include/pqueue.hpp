#pragma once

#include <sys/shm.h>

#include "message.hpp"
#include "semaphoreop.hpp"

#define CAP 20
#define SEM_NUM 3 /* semaphores per queue */
#define PQ_A 'A'
#define PQ_B 'B'
#define KEY_A 45281
#define KEY_B 45282
#define SKEY_A 45283
#define SKEY_B 45284

/* semaphores indexes */

#define EMPTY 0
#define FULL 1
#define BIN 2

template <typename T>
class PQueue {
private:
    int semid;
    char name;
    int bufSize;

    T buf[CAP];

public:
    PQueue() {};
    ~PQueue() {};

    bool push(T *m) {
        this->buf[this->bufSize] = *m;
        (this->bufSize)++;

        return true;
    }

    T pop() {
        T m;

        if (this->bufSize == 0) {
            // TODO
        } else if (this->bufSize == 1) {
            m = this->buf[0];
            this->bufSize = 0;
        } else {
            m = this->buf[0];

            for (int index = 0; index < this->bufSize - 1; ++index) {
                this->buf[index] = this->buf[index + 1];
            }

            --this->bufSize;
        }

        return m;
    }

    int getSemid() {
        return this->semid;
    }

    char getName() {
        return this->name;
    }

    int getSize() {
        return this->bufSize;
    }

    void setSemid(int semid) {
        this->semid = semid;
    }

    void setName(char name) {
        this->name = name;
    }

    void setSize(int bufSize) {
        this->bufSize = bufSize;
    }
};

template <typename T>
PQueue<T> *setSHM(char group) {
    PQueue<T> *pq = NULL;

    int shmid = 0;
    int semid = 0;
    int GROUP_KEY = 0;
    int SEM_KEY = 0;

    if (PQ_A == group) {
        GROUP_KEY = KEY_A;
        SEM_KEY = SKEY_A;
    } else if (PQ_B == group) {
        GROUP_KEY = KEY_B;
        SEM_KEY = SKEY_B;
    } else {
        std::cout << "Wrong group name!\n";
        exit(1);
    }

    semid = semget(SEM_KEY, SEM_NUM, IPC_CREAT | 0600);
    shmid = shmget(GROUP_KEY, sizeof(PQueue<T>), IPC_CREAT | 0600);

    pq = (PQueue<T> *)shmat(shmid, NULL, 0);

    pq->setSemid(semid);
    pq->setName(group);
    pq->setSize(0);

    return pq;
}

void setSemaphores();
