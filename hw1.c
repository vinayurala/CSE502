#undef __KERNEL__
#define __KERNEL__

#undef MODULE
#define MODULE

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/preempt.h>
#include <linux/hardirq.h>

#define RUN_COUNT 9
#define BILLION 1E9

static int __init timer_init(void)
{
  unsigned long long timer_high_start[5], timer_high_end[5], timer_low_start[5], timer_low_end[5];
  unsigned long long tot_start[5], tot_end[5];
  unsigned long mask = 1;
  float clock_freq;
  double tot_time[5];
  volatile int x = 0;
  int y, rc = RUN_COUNT, i = 0;

  printk (KERN_ALERT "Loading timer module");

  preempt_disable();

  /* __asm__ __volatile("cpuid \n\t" */
  /* 		     "rdtsc \n\t" */
  /* 		     "mov %%rdx, %0\n\t" */
  /* 		     "mov %%rax, %1\n\t" */
  /* 		     : "=r"(cfq_high_start), "=r"(cfq_low_start) */
  /* 		     :: "%rax", "%rbx", "%rcx", "%rdx"); */
  /* __asm__ __volatile("cpuid \n\t" */
  /* 		     "rdtsc \n\t" */
  /* 		     "mov %%rdx, %0\n\t" */
  /* 		     "mov %%rax, %1\n\t" */
  /* 		     : "=r"(cfq_high_end), "=r"(cfq_low_end) */
  /* 		     :: "%rax", "%rbx", "%rcx", "%rdx"); */

  /* cfq_tot_start = (cfq_high_start << 32) | cfq_low_start; */
  /* cfq_tot_end = (cfq_high_end << 32) | cfq_low_end; */

  clock_freq = 1.728932;

  __asm__ __volatile__("cli \n\t");

  while(rc > 0)
    {
      __asm__ __volatile("xor %%rax, %%rax \n\t"
			 "cpuid \n\t"
			 "rdtsc \n\t"
			 "mov %%rdx, %0\n\t"
			 "mov %%rax, %1\n\t"
			 : "=r"(timer_high_start[i]), "=r"(timer_low_start[i])
			 :: "%rax", "%rbx", "%rcx", "%rdx");

      for(y = 0; y < 1234567890; y++)
	++x;
      
      __asm__ __volatile("cpuid \n\t"
			 "rdtsc \n\t"
			 "mov %%rdx, %0\n\t"
			 "mov %%rax, %1\n\t"
			 : "=r"(timer_high_end[i]), "=r"(timer_low_end[i])
			 :: "%rax", "%rbx", "%rcx", "%rdx");
      
      i++; rc--;
    }

  __asm__ __volatile("sti \n\t");

  preempt_enable();

  for(i = 0; i < RUN_COUNT; i++)
    {
      tot_start[i] = (timer_high_start[i] << 32) | timer_low_start[i];
      tot_end[i] = (timer_high_end[i] << 32) | timer_low_end[i];
      tot_time[i] = ((tot_end[i] - tot_start[i])/clock_freq);
      tot_time[i] /= BILLION;
      
      printk (KERN_ALERT "Total time spent on for loop: %-11lu", (unsigned long)tot_time[i]);
    }


  return 0;
}

static void __exit timer_exit(void)
{
  printk(KERN_INFO "Unloading timer module\n");
}

module_init(timer_init);
module_exit(timer_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kernel module to measure time spent on a loop");
