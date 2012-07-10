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
//false sharing
////////////////////////////////////////////
//We start N_THREADS and each of them are going to access "res".
//if they access res on the same cache line (offset=0) => slow and false sharing 
//if the access res on different cache line (offset=16 (as res contains int and cache line = 64kB) => faster

int64_t s_clock (void)
{
    /*Return current system clock as milliseconds*/
    struct timeval tv;
    gettimeofday (&tv, NULL);
    return (int64_t) (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}


struct s_thread_params
{
    /*used to demonstrate false sharing (see main) */

    int thread_id;
    int pos;    
    int *res;    
};

void *worker_routine (void *params) {
    /*used to demonstrate false sharing (see main) */

    int i;    

    struct s_thread_params *p = (struct s_thread_params *) params;    

    for (i = 0; i < 100000000; i++) {	
	p->res[p->pos] += 1;    
    }

    printf("thread %d done\n", p->thread_id);

    return NULL;
}




int main(int argc, char *argv[])
{
    int nt;    
    int N_THREADS = 4;
    int *res = malloc(N_THREADS*16*sizeof(int));
    int offset;    

    struct s_thread_params *p_thread_params = malloc(N_THREADS*sizeof(struct s_thread_params));
    pthread_t *worker = malloc(N_THREADS*sizeof(pthread_t));	

    for (offset = 0; offset<=16; offset+=16){
	
	for (nt = 0; nt < N_THREADS; nt++) {

	    p_thread_params[nt].thread_id = nt;
	    p_thread_params[nt].res = res;
	    p_thread_params[nt].pos = nt*offset;	

	    pthread_create (&worker[nt], NULL, worker_routine, (void*) &p_thread_params[nt]);
	    printf("thread %d started\n", nt);      
	}

	int64_t t0 = s_clock();    
	for(nt = 0; nt < N_THREADS; nt++){
	    pthread_join(worker[nt], NULL);
	}
	printf("offset: %d time: %" PRId64 "ms\n", offset, s_clock()-t0);
    }
    
    free(worker);
    free(p_thread_params);
    free(res);    

    return 0;    
}

