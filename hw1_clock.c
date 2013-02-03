#include <stdio.h>
#include <time.h>

volatile int x = 0;

int main()
{
  clock_t start, end;
  int y;

  start = clock();

  for(y = 0; y < 1234567890; y++)
    ++x;

  end = clock();

  printf("\nTime taken = %11.2f seconds: ", (double)(end-start)/CLOCKS_PER_SEC);
  
  printf("\n");
  return 0;
}
