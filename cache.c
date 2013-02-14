#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

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
		   "movl %%ebx, %0 \n\t"			\
		   "movl %%ecx, %1 \n\t"			\
		   : "=r"(res[0]), "=r"(res[1])			\
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

  int arr[KB * KB];
  int steps[3] = {L1.size, L2.size, L3.size};

  for(i = 0; i < 3; i++)
    {
      clock_gettime(CLOCK_MONOTONIC_RAW, &start);
      for(j = 0; j < steps[i]; j++)
	arr[(j * 16) & lengthmod]++;
      clock_gettime(CLOCK_MONOTONIC_RAW, &end);
      
      tot_time = (end.tv_nsec - start.tv_nsec);
      printf("\nTime taken = %lu ns", (unsigned long long)tot_time);
    }
 
}

int main()
{
  struct timespec start, end;
  int num_accesses;
  register int *a, *b,i, num_iter = 1024, k, l;
  float tot_time;

  cache_sizes();
  
  calc_latencies();

  printf("\n");
  return 0;
}
