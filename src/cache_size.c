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
//also, L1 cache is 32K, L2 256K and L3 3M

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
    int N_REP = 4; //number of repetitions

    for (s=0; s<18; s++) {
	int mem_size = (int) pow(2.0, s)*1024; //in bytes
	int *tab = malloc( mem_size );
	
	double tavg = 0.0;	
	for (r=0; r < N_REP; r++) { //repetitions (for time measurement)
	    int64_t t0 = s_clock ();	    
	    for (i=0; i< (100*1024*1024) ; i++){		
		tab[(i * 16) % (mem_size/4) ]++; //an int is 4 bytes so there are only mem_size/4 elements in the array "tab". Also we go by 16 as the cacheline is 64kb (we want to force to change cache lines if needed)
	    }
	    tavg += (double) (s_clock()-t0);
	}
	printf("size: %d kB time: %g ms\n", mem_size/1024, tavg/(double) N_REP);
	free(tab);
    }

    return 0;    
}

