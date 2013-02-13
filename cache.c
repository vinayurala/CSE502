#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#define PAGE_SIZE 4096
#define TOTAL_MEM_SIZE (4096 * 1024)
#define L1_CACHE_LINE_SIZE 64
#define L1_CACHE 64 * 1024
#define BILLION 1E9

int main()
{
  struct timespec start, end;
  int num_accesses;
  register int *a, *b,i, num_iter = 1024, k, l;
  float tot_time;
  
  b = a = (void *)sbrk(2 * L1_CACHE);

  for(k = 0; k < 2 * L1_CACHE / PAGE_SIZE; k++, a+= 2048)
    i = *a;

  clock_gettime(CLOCK_MONOTONIC_RAW, &start);

  for(a = b, k = 0; k < num_iter; k++, a = b)
    {
      for(l = 0; l < L1_CACHE / L1_CACHE_LINE_SIZE; l++, a+=8)
	i = *a;

      for(l = 0; l < L1_CACHE / L1_CACHE_LINE_SIZE; l++, a+=8)
	i = *a;
    }

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);

  tot_time = (end.tv_sec - start.tv_sec) * BILLION + (end.tv_nsec - start.tv_nsec);
  num_accesses = num_iter * (L1_CACHE / L1_CACHE_LINE_SIZE) * 2;
  printf("L1 cache latency: %f ns\n", tot_time / num_accesses);

  printf("\n");
  return 0;
}
