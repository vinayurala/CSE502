#undef __KERNEL__
#define __KERNEL__

#undef MODULE
#define MODULE

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init hello_init(void)
{
  
  printk(KERN_INFO "Hello, world!\n");

  return 0;
}

static void __exit hello_exit(void)
{
  printk(KERN_INFO "Exiting and cleaning up module\n");
}

module_init(hello_init);
module_exit(hello_exit);
