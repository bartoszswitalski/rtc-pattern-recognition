#pragma once

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

#include <iostream>

void up(short unsigned int semid, short unsigned int semnum);

<<<<<<< HEAD
void up(int semid, int semnum);

void down(int semid, int semnum);
=======
void down(short unsigned int semid, short unsigned int semnum);
>>>>>>> a35f22044aa4e9bac9e2913d09673b42bdf2d6bd
