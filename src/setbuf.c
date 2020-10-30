#include "pqueue.hpp"

int main(){

    PQueue<ImageRaw>*	     pqA = setSHM<ImageRaw>( 'A' );
    PQueue<ProcessedValue>*  pqB = setSHM<ProcessedValue>( 'B' );

    setSemaphores();

    return 0;

}
