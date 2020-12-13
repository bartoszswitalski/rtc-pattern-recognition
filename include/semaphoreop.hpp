#pragma once

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

#include <iostream>

void up(short unsigned int semid, short unsigned int semnum);

void down(short unsigned int semid, short unsigned int semnum);