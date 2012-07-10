#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h> 

////////////////////////////////////////////
//cache sizes 
////////////////////////////////////////////
//NOTE: cache line is 64 bytes (obtained by running sysctl -a | grep cache) and an int is 4 byte => 16 int to fill cache line


int64_t s_clock (void)
{
    /*Return current system clock as milliseconds*/
    struct timeval tv;
    gettimeofday (&tv, NULL);
    return (int64_t) (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}


int main(int argc, char *argv[])
{

    //print size of data type
    printf("sizeof(int) = %lu\n", sizeof(int));

    int r, s, i;
    int N_REP = 1; //number of repetitions
    for (s=0; s<18; s++){
	int mysize = (int) pow(2.0, s)*1024;
	int *tab = malloc( (mysize/4) *sizeof(int));

	double tavg = 0;	
	for (r=0; r < N_REP; r++) { //repetitions (for time measurement)
	    int64_t t0 = s_clock ();	    
	    for (i=0; i< (100*1024*1024) ; i++){		
		tab[(i * 16) % (mysize/4)]++;
	    }
	    tavg += (double) (s_clock()-t0);
	}
	printf("size: %d kB time: %g ms\n", mysize/1024, tavg/(double) N_REP);
	free(tab);
    }


    return 0;    
    
}

