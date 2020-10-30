#pragma once

#include <sys/shm.h>
#include <cstdio>
#include "message.hpp"
#include "semaphoreop.hpp"

#define CAP	20
#define SEM_NUM	3	    /* semaphores per queue */
#define PQ_A	'A'
#define PQ_B	'B'
#define KEY_A	45281
#define KEY_B	45282
#define SKEY_A  45283
#define SKEY_B	45284

/* semaphores indexes */

#define EMPTY 0
#define FULL  1
#define BIN   2

template< typename T >
class PQueue{

private:

    int semid;
    char name;
    T buf[CAP];
    int bufSize;

public:

    PQueue()  {};
    ~PQueue() {};

    bool push( T* m ){

	this->buf[this->bufSize] = *m;
	( this->bufSize )++;

	return true;

    }

    T pop(){

	T retVal = {0};

	if( this->bufSize == 0 ) puts( "PQueue is empty!\n" );
	else if( this->bufSize == 1 ){

	    retVal = this->buf[0];
	    this->bufSize = 0;

	}
	else{
	
	    retVal = this->buf[0];

	    for( int index = 0; index < this->bufSize - 1; ++index ){

		this->buf[index] = this->buf[index+1];

	    }

	    --( this->bufSize );	

	}

	return retVal;

    }

    int getSemid() { return this->semid; }
    char getName() { return this->name; }
    int getSize()  { return this->bufSize; }

    void setSemid( int semid )  { this->semid = semid; }
    void setName( char name )   { this->name = name ; }
    void setSize( int bufSize ) { this->bufSize = bufSize; }

    void catQueue() { 
   
	std::cout<< "There are " << this->bufSize << " elements in the priority queue!\n";

    }

};

template< typename T >
PQueue<T>* setSHM( char group ){

    PQueue<T>* pq = NULL;

    int shmid = 0;
    int semid = 0;
    int GROUP_KEY = 0;
    int SEM_KEY   = 0;
    
    if( PQ_A == group ){

        GROUP_KEY = KEY_A;
        SEM_KEY   = SKEY_A;

    }
    else if( PQ_B == group ){

	GROUP_KEY = KEY_B;
        SEM_KEY   = SKEY_B;

    }
    else{ 

	std::cerr << "Wrong group name!\n" ;
	exit( 1 ); 

    }
    
    semid = semget( SEM_KEY, SEM_NUM, IPC_CREAT|0600 );
    shmid = shmget( GROUP_KEY, sizeof( PQueue<T> ), IPC_CREAT|0600 );

    pq = ( PQueue<T>* )shmat( shmid, NULL, 0 );

    pq->setSemid( semid );
    pq->setName( group );
    pq->setSize( 0 );

    return pq;

}

void setSemaphores(){

	int semid_A, semid_B;

	semid_A = semget( SKEY_A, SEM_NUM, IPC_CREAT|0600 );
	semid_B = semget( SKEY_B, SEM_NUM, IPC_CREAT|0600 );
	
	semctl( semid_A, FULL, SETVAL, ( int )0 );
	semctl( semid_B, FULL, SETVAL, ( int )0 );

	semctl( semid_A, EMPTY, SETVAL, ( int )CAP );
	semctl( semid_B, EMPTY, SETVAL, ( int )CAP );

	semctl( semid_A, BIN, SETVAL, ( int )1 );
	semctl( semid_B, BIN, SETVAL, ( int )1 );

}

