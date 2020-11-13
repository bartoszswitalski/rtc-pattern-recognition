#pragma once

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

#include <iostream>

static struct sembuf buf;

void up(int semid, int semnum);

void down(int semid, int semnum);