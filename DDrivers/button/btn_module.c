#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/module.h>
#include <asm/io.h>
#include <linux/timer.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/mm.h>
#include <linux/gpio.h>     //GPIO


#include <linux/io.h>
//#include <mach/platform.h>

#include "utils.h"

#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/sched/signal.h>
#include <asm/siginfo.h>
#include <linux/rcupdate.h>
#include <linux/timer.h>

#define DEVICE_NAME "button"
#define CLASS_NAME "buttonclass"


#define SIG 44

MODULE_LICENSE("GPL");

/* Device variables */
static struct class* buttonDevice_class = NULL;
static dev_t buttonDevice_majorminor;
static struct cdev c_dev;  // Character device structure



struct GpioRegisters *s_pGpioRegisters;


static unsigned int count = 0;

uint8_t backup = 0;
static struct GpioRegisters *pdev;

static const int buttonGpioPin = 17;


ssize_t button_device_write(struct file *pfile, const char __user *pbuff, size_t len, loff_t *off) {
	pr_alert("%s: calbutton (%u)\n",__FUNCTION__,len);
	return EINVAL;
}

ssize_t button_device_read(struct file *pfile, char __user *p_buff,size_t len, loff_t *poffset){
	
	uint8_t gpio_state = 0;
	
	pr_alert("%s: calbutton (%u)\n",__FUNCTION__,len);

	
	if(unlikely(pfile->private_data == NULL))
		return -EFAULT;
  
	  //reading GPIO value
	  gpio_state = GetGPIOInputValue(pdev, buttonGpioPin);
	  
	  //write to user
	  len = 1;
	  if( copy_to_user(p_buff, &gpio_state, len) > 0) {
	    pr_err("ERROR: could not \n");
	  }
	
	
	return 0;
}

int button_device_close(struct inode *p_inode, struct file * pfile){
	
	pr_alert("%s: calbutton\n",__FUNCTION__);
	pdev = NULL;
	pfile->private_data = NULL;
	return 0;
}


int button_device_open(struct inode* p_indode, struct file *p_file){

	pr_alert("%s: calbutton\n",__FUNCTION__);

	p_file->private_data = (struct GpioRegisters *) s_pGpioRegisters;
	pdev = (struct GpioRegisters *)p_file->private_data;

	return 0;
	
}


static struct file_operations buttonDevice_fops = {
	.owner = THIS_MODULE,	//holds the address of the module's function that performs that operation.
	.write = button_device_write,
	.read = button_device_read,
	.release = button_device_close,
	.open = button_device_open,
};

static int __init buttonModule_init(void) {
	int ret;
	struct device *dev_ret;

	pr_alert("%s: calbutton\n",__FUNCTION__);

	if ((ret = alloc_chrdev_region(&buttonDevice_majorminor, 0, 1, DEVICE_NAME)) < 0) {
		return ret;
	}

	if (IS_ERR(buttonDevice_class = class_create(THIS_MODULE, CLASS_NAME))) {
		unregister_chrdev_region(buttonDevice_majorminor, 1);
		return PTR_ERR(buttonDevice_class);
	}
	if (IS_ERR(dev_ret = device_create(buttonDevice_class, NULL, buttonDevice_majorminor, NULL, DEVICE_NAME))) {
		class_destroy(buttonDevice_class);
		unregister_chrdev_region(buttonDevice_majorminor, 1);
		return PTR_ERR(dev_ret);
	}

	cdev_init(&c_dev, &buttonDevice_fops);
	c_dev.owner = THIS_MODULE;
	if ((ret = cdev_add(&c_dev, buttonDevice_majorminor, 1)) < 0) {
		printk(KERN_NOTICE "Error %d adding device", ret);
		device_destroy(buttonDevice_class, buttonDevice_majorminor);
		class_destroy(buttonDevice_class);
		unregister_chrdev_region(buttonDevice_majorminor, 1);
		return ret;
	}


	s_pGpioRegisters = (struct GpioRegisters *)ioremap(GPIO_BASE, sizeof(struct GpioRegisters));
	//s_pGpioRegisters = (struct GpioRegisters *)ioremap_nocache(GPIO_BASE, sizeof(struct GpioRegisters));
	
	pr_alert("map to virtual adresse: 0x%x\n", (unsigned)s_pGpioRegisters);
	
	SetGPIOFunction(s_pGpioRegisters, buttonGpioPin, 0); //INPUT
	
	return 0;
}

static void __exit buttonModule_exit(void) {
	
	pr_alert("%s: calbutton\n",__FUNCTION__);
	
	SetGPIOFunction(s_pGpioRegisters, buttonGpioPin, 0); //Configure the pin as input
	iounmap(s_pGpioRegisters);
	cdev_del(&c_dev);
	device_destroy(buttonDevice_class, buttonDevice_majorminor);
	class_destroy(buttonDevice_class);
	unregister_chrdev_region(buttonDevice_majorminor, 1);
}

module_init(buttonModule_init);
module_exit(buttonModule_exit);
