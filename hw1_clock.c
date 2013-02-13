#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

#define BILLION 1e9
#define RUNCOUNT 10

volatile int x = 0;

int main()
{
  /* clock_t start, end; */
  struct timespec start, end;
  int y, i, rc = RUNCOUNT;
  float tot_time;
  unsigned long mask = 1;

  /* start = clock(); */
  i = 0;

  sched_setaffinity(0, sizeof(mask), &mask);
  setpriority(PRIO_PROCESS, 0, -20);

  while(rc > 0)
    {
      clock_gettime(CLOCK_MONOTONIC_RAW, &start);
      
      for(y = 0; y < 1234567890; y++)
	++x;
      
      // end = clock();
      clock_gettime(CLOCK_MONOTONIC_RAW, &end);

      i++; rc--;
    }

  for(i = 0; i < RUNCOUNT; i++)
    {
      tot_time = (end.tv_sec-start.tv_sec) * BILLION + (end.tv_nsec - start.tv_nsec);
      printf("\nTime taken = %-10.2f ns: ", tot_time);
    }
  
  printf("\n");
  return 0;
}
