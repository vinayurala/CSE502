#undef __KERNEL__
#define __KERNEL__

#undef MODULE
#define MODULE

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/preempt.h>
#include <linux/hardirq.h>

#define RUN_COUNT 7

static int __init timer_init(void)
{
  unsigned long long timer_high_start[5], timer_high_end[5], timer_low_start[5], timer_low_end[5];
  unsigned long long tot_start[5], tot_end[5];
  unsigned long long cfq_low_end, cfq_low_start, cfq_high_end, cfq_high_start;
  unsigned long long cfq_tot_start, cfq_tot_end;
  float clock_freq;
  volatile int x = 0;
  int y, rc = RUN_COUNT, i = 0;

  printk (KERN_ALERT "Starting timer module");

  preempt_disable();

  __asm__ __volatile("cpuid \n\t"
		     "rdtsc \n\t"
		     "mov %%rdx, %0\n\t"
		     "mov %%rax, %1\n\t"
		     : "=r"(cfq_high_start), "=r"(cfq_low_start)
		     :: "%rax", "%rbx", "%rcx", "%rdx");
  __asm__ __volatile("cpuid \n\t"
		     "rdtsc \n\t"
		     "mov %%rdx, %0\n\t"
		     "mov %%rax, %1\n\t"
		     : "=r"(cfq_high_end), "=r"(cfq_low_end)
		     :: "%rax", "%rbx", "%rcx", "%rdx");

  cfq_tot_start = (cfq_high_start << 32) | cfq_low_start;
  cfq_tot_end = (cfq_high_end << 32) | cfq_low_end;

  clock_freq = 1.728932;

  __asm__ __volatile__("cli \n\t");

  while(rc > 0)
    {
      __asm__ __volatile("cpuid \n\t"
			 "xor %%rax, %%rax \n\t"
			 "rdtsc \n\t"
			 "mov %%rdx, %0\n\t"
			 "mov %%rax, %1\n\t"
			 : "=r"(timer_high_start[i]), "=r"(timer_low_start[i])
			 :: "%rax", "%rbx", "%rcx", "%rdx");

      for(y = 0; y < 1234567890; y++)
	++x;
      
      __asm__ __volatile("cpuid \n\t"
			 "xor %%rax, %%rax\n\t"		    
			 "rdtsc \n\t"
			 "mov %%rdx, %0\n\t"
			 "mov %%rax, %1\n\t"
			 : "=r"(timer_high_end[i]), "=r"(timer_low_end[i])
			 :: "%rax", "%rbx", "%rcx", "%rdx");
      
      i++; rc--;
    }

  __asm__ __volatile("sti \n\t");

  preempt_enable();

  printk (KERN_ALERT "Clock frequency = %lf", clock_freq);
  for(i = 0; i < RUN_COUNT; i++)
    {
      tot_start[i] = (timer_high_start[i] << 32) | timer_low_start[i];
      tot_end[i] = (timer_high_end[i] << 32) | timer_low_end[i];
      
      printk (KERN_ALERT "Total time spent on for loop: %-11d", (tot_end[i] - tot_start[i])/clock_freq);
    }


  return 0;
}

static void __exit timer_exit(void)
{
  printk(KERN_INFO "Exiting and cleaning up module\n");
}

module_init(timer_init);
module_exit(timer_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kernel module to measure time spent on a loop");
