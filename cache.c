#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define PAGE_SIZE 4096
#define TOTAL_MEM_SIZE (4096 * 1024)
#define L1_CACHE_LINE_SIZE 64
#define L1_CACHE 64 * 1024
#define BILLION 1E9
#define KB 1024

struct Cache
{
  int level;
  int blk_size;
  int num_sets;
  int assoc;
  int size;
};

void run_cpuid(int level, int *reg_ebx, int *reg_ecx)
{
  int res[2];
  int func_num = 4, temp;

  __asm __volatile("cpuid \n\t"					\
		   "movl %%ebx, %0 \n\t"			\
		   "movl %%ecx, %1 \n\t"			\
		   : "=r"(res[0]), "=r"(res[1])			\
		   : "c"(level), "a"(func_num));		\

  *reg_ebx = res[0];
  *reg_ecx = res[1];

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
  struct Cache L1, L2, L3;
  int res[2], parts;

  L1.level = 1;
  L2.level = 2;
  L3.level = 3;

  run_cpuid(L1.level, &res[0], &res[1]);

  L1.blk_size = (res[0] & 0xFFF) + 1;
  L1.num_sets = res[1] + 1;
  L1.assoc = (res[0] >> 22) + 1;
  parts = ((res[0] >> 12) & 0x3FF) + 1;

  L1.size = L1.blk_size * L1.num_sets * L1.assoc * parts;

  run_cpuid(L2.level, &res[0], &res[1]);

  L2.blk_size = (res[0] & 0xFFF) + 1;
  L2.num_sets = res[1] + 1;
  L2.assoc = (res[0] >> 22) + 1;
  parts = ((res[0] >> 12) & 0x3FF) + 1;

  L2.size = L2.blk_size * L2.num_sets * L2.assoc * parts;

  run_cpuid(L3.level, &res[0], &res[1]);

  L3.blk_size = (res[0] & 0xFFF) + 1;
  L3.num_sets = res[1] + 1;
  L3.assoc = (res[0] >> 22) + 1;
  parts = ((res[0] >> 12) & 0x3FF) + 1;

  L3.size = L3.blk_size * L3.num_sets * L3.assoc * parts;

  printf("\nCaches: ");
  printf("%d/%dX%d ", L1.blk_size, L1.num_sets, L1.assoc);
  print(L1.size);
  printf("%d/%dX%d ", L2.blk_size, L2.num_sets, L2.assoc);
  print(L2.size);
  printf("%d/%dX%d ", L3.blk_size, L3.num_sets, L3.assoc);
  print(L3.size);
  printf("\n");

}

int main()
{
  struct timespec start, end;
  int num_accesses;
  register int *a, *b,i, num_iter = 1024, k, l;
  float tot_time;

  cache_sizes();
  
  b = a = mmap(NULL, 2 * L1_CACHE, PROT_READ | PROT_WRITE, MAP_ANON, -1, 0);

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
  printf("L1 cache latency: %f ns\n", (tot_time / num_accesses));

  printf("\n");
  return 0;
}
