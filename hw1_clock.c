#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

#define BILLION 1e9

volatile int x = 0;

int main()
{
  struct timespec start, end;
  int y, i;
  float tot_time;
  unsigned long mask = 1;

  sched_setaffinity(0, sizeof(mask), &mask);
  setpriority(PRIO_PROCESS, 0, -20);

  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  
  for(y = 0; y < 1234567890; y++)
    ++x;
  
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  
  tot_time = (end.tv_sec-start.tv_sec) * BILLION + (end.tv_nsec - start.tv_nsec);
  printf("\n%d Loop = %-10.2f ns", y, tot_time);
  
  printf("\n");
  return 0;
}
