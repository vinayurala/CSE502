#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

#define RUN_COUNT 10
#define BILLION 1E9

int main(void)
{
  unsigned long high_start[RUN_COUNT], low_start[RUN_COUNT], high_end[RUN_COUNT], low_end[RUN_COUNT];
  unsigned long tot_start[RUN_COUNT], tot_end[RUN_COUNT];
  unsigned long cfq_high_start, cfq_high_end, cfq_low_start, cfq_low_end;
  float tot_time[RUN_COUNT];
  float cpu_freq = 1.728938;
  unsigned long mask = 0;
  int i = 0, rc = RUN_COUNT;
  int y;
  volatile int x = 0;

  sched_setaffinity(0, sizeof(mask), &mask);
  setpriority(PRIO_PROCESS, 0, -20);

  while(rc > 0)
    {

      __asm__ __volatile("cpuid \n\t"
			 "rdtsc \n\t"
			 "mov %%rdx, %0\n\t"
			 "mov %%rax, %1\n\t"
			 : "=r"(high_start[i]), "=r"(low_start[i])
			 :: "%rax", "%rbx", "%rcx", "%rdx");
      
      for(y = 0; y < 1234567890; ++y)
	++x;
      
      __asm__ __volatile("cpuid \n\t"
			 "rdtsc \n\t"
			 "mov %%rdx, %0\n\t"
			 "mov %%rax, %1\n\t"
			 : "=r"(high_end[i]), "=r"(low_end[i])
			 :: "%rax", "%rbx", "%rcx", "%rdx");

      i++; rc--;
    }
  for(i = 0; i < RUN_COUNT; i++)  
    {

      tot_start[i] = (high_start[i] << 32) | low_start[i];
      tot_end[i] = (high_end[i] << 32) | low_end[i];

      tot_time[i] = (tot_end[i] - tot_start[i])/cpu_freq;
      
      printf("\nTotal time = %f ns", tot_time[i]);
    }

  printf("\n");
  return 0;

}
