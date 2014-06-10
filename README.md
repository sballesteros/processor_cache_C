processor_cache_C
=================

Reproduce some example of Gallery of Processor Cache Effects in C (see http://igoro.com/archive/gallery-of-processor-cache-effects/)

Note: On an OSX/Ubuntu system, one can get the cache sizes by running:

```sysctl -a | grep cache```

For instance on my machine I get:

    hw.cachelinesize = 64

    hw.l1icachesize = 32768

    hw.l1dcachesize = 32768

    hw.l2cachesize = 262144

    hw.l3cachesize = 3145728

So, L1 cache is 32K, L2 cache is 256K, and L3 cache is 3M

#Compilation

Cache sizes:

    gcc -Wall -o cache_size cache_size.c -lm

False sharing:

    gcc -Wall -o false_sharing false_sharing.c -lm

#Examples:

    ./cache_size 
        sizeof(int) = 4
        size: 1 kB time:        793 ms
        size: 2 kB time:        847.75 ms
        size: 4 kB time:        849.75 ms
        size: 8 kB time:        918.5 ms
        size: 16 kB time:       794 ms
        size: 32 kB time:       839.5 ms
        size: 64 kB time:       894.75 ms
        size: 128 kB time:      834.5 ms
        size: 256 kB time:      785.5 ms
        size: 512 kB time:      1138 ms
        size: 1024 kB time:     1301.75 ms
        size: 2048 kB time:     816 ms
        size: 4096 kB time:     1163 ms
        size: 8192 kB time:     1175.5 ms
        size: 16384 kB time:    1152.5 ms
        size: 32768 kB time:    910.25 ms
        size: 65536 kB time:    902.75 ms
        size: 131072 kB time:   903.5 ms
    
    ./false_sharing 
        thread 0 started
        thread 1 started
        thread 2 started
        thread 3 started
        thread 0 done
        thread 1 done
        thread 3 done
        thread 2 done
        offset: 0 time: 1250ms
        thread 0 started
        thread 1 started
        thread 2 started
        thread 3 started
        thread 3 done
        thread 0 done
        thread 1 done
        thread 2 done
        offset: 16 time: 379ms
