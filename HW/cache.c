#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/resource.h>

#define BILLION 1E9
#define KB 1024
#define MAX_ARRAY_SIZE 12 * KB * KB
#define TIMES 6
#define REPS 1024 * KB * KB

struct Cache
{
  int level;
  int blk_size;
  int num_sets;
  int assoc;
  int size;
};

struct Cache L1, L2, L3;

void run_cpuid(int level, int *reg_ebx, int *reg_ecx)
{
  int res[2];

  __asm __volatile("cpuid \n\t"					\
		   : "=b"(res[0]), "=c"(res[1])			\
		   : "c"(level), "a"(4));		

  *reg_ebx = res[0];
  *reg_ecx = res[1];
}

void populate_cache_struct(struct Cache *cstruct, int res[2])
{
  int parts;

  cstruct->blk_size = (res[0] & 0xFFF) + 1;
  cstruct->num_sets = res[1] + 1;
  cstruct->assoc = (res[0] >> 22) + 1;
  parts = ((res[0] >> 12) & 0x3FF) + 1;
  
  cstruct->size = cstruct->blk_size * cstruct->num_sets * cstruct->assoc * parts;
}

void print(int size)
{
  int temp;
  char label[2][3] = {"KB", "MB"};
  int idx = -1;

  while(size > 0)
    {
      temp = size;
      idx++;
      size /= KB;
    }

  if(idx > -1)
    printf("(%d%s) ", temp, label[idx - 1]);
  else
    printf("(%dB) ", temp);
}

void cache_sizes()
{
  int res[2];
  int level = 1, flag = 1;

  printf("\nCaches: ");
  
  run_cpuid(level, &res[0], &res[1]);
  if(!(res[0] & res[1]))
    goto end;

  L1.level = level;
  populate_cache_struct(&L1, res);
  printf("%d/%dX%d", L1.blk_size, L1.num_sets, L1.assoc);
  print(L1.size);
  level++;      
  
  run_cpuid(level, &res[0], &res[1]);
  if(!(res[0] & res[1]))
    goto end;

  L2.level = level;
  populate_cache_struct(&L2, res);
  printf("%d/%dX%d", L2.blk_size, L2.num_sets, L2.assoc);
  print(L2.size);
  level++;
  
  run_cpuid(level, &res[0], &res[1]);
  if(!(res[0] & res[1]))
    goto end;

  L3.level = level;
  populate_cache_struct(&L3, res);
  printf("%d/%dX%d", L3.blk_size, L3.num_sets, L3.assoc);
  print(L3.size);

 end:
  printf("\n");
}

void calc_latencies()
{
  float tot_time;
  struct timespec start, end;
  int lengthmod = (KB * KB) - 1;
  int i,j;
  unsigned int k;
  int sizes[3] = {L1.size, L2.size, L3.size};
  int *arr = (int *)malloc(L1.size/sizeof(int));
  unsigned long high_start, low_start, high_end, low_end;
  float cpu_freq = 1.728938;
  unsigned long dry_run_time;

  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);

  dry_run_time = end.tv_nsec - start.tv_nsec;
  printf("\n%lu", dry_run_time);

  // Flush the cache, and fill cache with arr
  memset((void *)arr, 1, sizeof(arr));

  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  arr[(L1.size -1) / sizeof(int)]++;
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);

  tot_time = end.tv_nsec - start.tv_nsec;
  printf("\nRaw run time: %.0f", tot_time);
  tot_time -= dry_run_time;

  printf("\nTime taken = %.0f ns", tot_time);
 
}

int main()
{
  struct timespec start, end;
  int num_accesses;
  register int *a, *b,i, num_iter = 1024, k, l;
  float tot_time;
  unsigned long mask = 2;

  sched_setaffinity(0, sizeof(mask), &mask);
  setpriority(PRIO_PROCESS, 0, -20);

  cache_sizes();
  
  calc_latencies();

  printf("\n");
  return 0;
}
