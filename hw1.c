#undef __KERNEL__
#define __KERNEL__

#undef MODULE
#define MODULE

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/preempt.h>

static int __init timer_init(void)
{
  unsigned long timer_high_start, timer_high_end, timer_low_start, timer_low_end;
  unsigned long tot_start, tot_end;//, flags;
  unsigned long cfq_low_end, cfq_low_start, cfq_high_end, cfq_high_start;
  unsigned long cfq_tot_start, cfq_tot_end;
  double clock_freq;
  volatile int x = 0;
  int y;

  preempt_disable();

  __asm__ __volatile("cli \n\t"
		     "cpuid \n\t"
		     "rdtsc \n\t"
		     "mov %%rdx, %0\n\t"
		     "mov %%rax, %1\n\t"
		     : "=r"(cfq_high_start), "=r"(cfq_low_start)
		     :: "%rax", "%rbx", "%rcx", "%rdx");
  __asm__ __volatile("cpuid \n\t"
		     "rdtsc \n\t"
		     "mov %%rdx, %0\n\t"
		     "mov %%rax, %1\n\t"
		     "sti \n\t"
		     : "=r"(cfq_high_end), "=r"(cfq_low_end)
		     :: "%rax", "%rbx", "%rcx", "%rdx");

  cfq_tot_start = (cfq_high_start << 32) | cfq_low_start;
  cfq_tot_end = (cfq_high_end << 32) | cfq_low_end;

  clock_freq = cfq_tot_end / cfq_tot_start;

  __asm__ __volatile("cli \n\t"
		     "cpuid \n\t"
		     "rdtsc \n\t"
		     "mov %%rdx, %0\n\t"
		     "mov %%rax, %1\n\t"
		     : "=r"(timer_high_start), "=r"(timer_low_start)
		     :: "%rax", "%rbx", "%rcx", "%rdx");

  for(y = 0; y < 1234567890; y++)
    ++x;

  __asm__ __volatile("cpuid \n\t"
		     "rdtsc \n\t"
		     "mov %%rdx, %0\n\t"
		     "mov %%rax, %1\n\t"
		     "sti \n\t"
		     : "=r"(timer_high_end), "=r"(timer_low_end)
		     :: "%rax", "%rbx", "%rcx", "%rdx");

  preempt_enable();

  tot_start = (timer_high_start << 32) | timer_low_start;
  tot_end = (timer_high_end << 32) | timer_low_end;

  printk (KERN_ALERT "Starting timer module");
  printk (KERN_ALERT "Clock frequency = %f", clock_freq);
  printk (KERN_ALERT "Total time spent on for loop: %11lu", (tot_end - tot_start));

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
