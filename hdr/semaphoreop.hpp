#pragma once

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <cstdio>

static struct sembuf buf;

void up( int semid, int semnum ){

	buf.sem_num = semnum;
	buf.sem_op  = 1;
	buf.sem_flg = 0;

	if( semop( semid, &buf, 1 ) == -1 ){

		std::cerr << "Semaphore up\n";
		exit( 1 );
	
	}

}

void down( int semid, int semnum ){

	buf.sem_num = semnum;
	buf.sem_op  = -1;
	buf.sem_flg = 0;
	
	if( semop( semid, &buf, 1 ) == -1 ){

		std::cerr << "Semaphore down\n";
		exit( 1 );

	}

}
