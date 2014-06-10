processor_cache_C
=================

Reproduce some example of Gallery of Processor Cache Effects in C (see http://igoro.com/archive/gallery-of-processor-cache-effects/)

Note: On an OsX system, one can get the cache sizes by running:

```sysctl -a | grep cache```

For instance on my machine I get:

    hw.cachelinesize = 64

    hw.l1icachesize = 32768

    hw.l1dcachesize = 32768

    hw.l2cachesize = 262144

    hw.l3cachesize = 3145728

So L1 cache is 32K, L2 256K and L3 3M


#Compilation

Cache sizes:

    gcc -Wall -o cache_size cache_size.c -lm

False sharing:

    gcc -Wall -o false_sharing false_sharing.c -lm



