#include <pqueue.hpp>

#include <unistd.h>
#include <stdlib.h>

double randProcessedValue(){

    return (double)( rand() % 101 ) / 100;

}

int main( int argc, char* argv[] ){

    srand( time( NULL ) );

    long tickSum = 0;		/* tick sum of processed messages */ 
    int mesTerm  = 0;		/* number of processed messages */

    PQueue<ImageRaw>* pqA;
    int shmidA = shmget( KEY_A, sizeof( PQueue<ImageRaw> ), 0 );
    pqA = ( PQueue<ImageRaw>* )shmat( shmidA, NULL, 0 );

    PQueue<ProcessedValue>* pqB;
    int shmidB = shmget( KEY_B, sizeof( PQueue<ProcessedValue> ), 0 );
    pqB = ( PQueue<ProcessedValue>* )shmat( shmidB, NULL, 0 );
    

    while( 1 ){

	sleep( 2 );

	ImageRaw tmp = {0}; 

	down( pqA->getSemid(), FULL );
	down( pqA->getSemid(), BIN );

	puts( "\nSekcja krytyczna przetwornika\n" );

	tmp = pqA->pop();
	pqA->catQueue();

	up( pqA->getSemid(), BIN );
	up( pqA->getSemid(), EMPTY );

	std::cout << "Przetworzona wartosc to " << randProcessedValue() << std::endl; 
	
    }

}
