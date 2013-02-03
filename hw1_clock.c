#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#define BILLION 1e9

volatile int x = 0;

int main()
{
  /* clock_t start, end; */
  struct timespec start, end;
  int y;

  /* start = clock(); */
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);

  for(y = 0; y < 1234567890; y++)
    ++x;

  // end = clock();
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);

  printf("\nTime taken = %11.2f seconds: ", (end.tv_sec-start.tv_sec) + ((end.tv_nsec - start.tv_nsec)/BILLION));
  
  printf("\n");
  return 0;
}
