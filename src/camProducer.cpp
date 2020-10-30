#include "pqueue.hpp"

#include <unistd.h>

int randVal( int minVal, int maxVal ){

    return rand() % ( maxVal - minVal + 1 ) + minVal;

}

int main( int argc, char* argv[] ){

    int shmid = 0;

    srand( time( NULL ) );

    shmid = shmget( KEY_A, sizeof( PQueue<ImageRaw> ), 0 );

    PQueue<ImageRaw>* pq = ( PQueue<ImageRaw>* )shmat( shmid, NULL, 0 );
    
    while( 1 ){

	int tmp;
	ImageRaw m;
	
	m.mesTime = clock();

	for( tmp = 0; tmp < IMG_SIZE; ++tmp ){

	    m.c[tmp] = randVal( 0, 255 );

	}
	
	down( pq->getSemid(), EMPTY );
	down( pq->getSemid(), BIN );
	
	puts( "\n SEKCJA KRYT GENERATOR ZDJECIA \n" );
	pq->push( &m );
	pq->catQueue();
	
	up( pq->getSemid(), BIN );
	up( pq->getSemid(), FULL );

	sleep( 1 );

    }

    return 0;

}
