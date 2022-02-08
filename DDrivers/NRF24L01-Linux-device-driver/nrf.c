#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/spi/spi.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/io.h>
//#include <mach/platform.h>
#include "nRF24L01.h"
#include "gpio.h"
#include "radio.h"


//  Macros like functions bitwize operations
      #ifndef _BIT_WIZE_OPERATIONS_ //so para ter a certeza
        #define _BIT_WIZE_OPERATIONS_
        #define setbit(x,n)     x|=(1<<n)
        #define clearbit(x,n)   x&=~(1<<n)
        #define togglebit(x,n)  x^=(1<<n)
        #define isbitset(x,n)   ((x>>n) & 0x1)
        #define isbitclear(x,n) (!((x>>n) & 0x1))
        #define setbit_ifx(x,n,l) x^= ((-l ^ x) & (1UL << n))
      #endif //_BIT_WIZE_OPERATIONS_

        #define ORop(y,x1,x2)     y=x1|x2
        #define ANDop(y,x1,x2)    y=x1&x2
  

#define NRF_CE 25 //module chip enable pin

/* NRF registers*/
static const uint8_t  nrf_reg[]={
	CONFIG,
	EN_AA,
	EN_RXADDR,
	SETUP_AW,
	SETUP_RETR,
	RF_CH,
	RF_SETUP,
	STATUS,
	OBSERVE_TX,
	RPD,
	FIFO_STATUS
};

static char *nrf_reg_name[]={
	"CONFIG",
	"EN_AA",
	"EN_RXADDR",
	"SETUP_AW",
	"SETUP_RETR",
	"RF_CH",
	"RF_SETUP",
	"STATUS",
	"OBSERVE_TX",
	"RPD",
	"FIFO_STATUS"
};


unsigned int address[5]={0x00,0x00,0x00,0x00,0x00};

static dev_t dev;

static struct cdev *nrf_cdev;
static struct class* nrf_class = NULL;
static struct device* nrf_device = NULL;
struct spi_device *spi_device;


ssize_t print_registers(char* buf, int* count, loff_t* offset);

/******************************
 nrf module file operations
******************************/

static int nrf_open(struct inode *inode, struct file *fp)
{
	
	return 0;
}

static int nrf_release(struct inode *inode,struct file *fp)
{
	printk(KERN_INFO "device successfully closed\n");
	return 0;
}

static ssize_t nrf_write(struct file *fp, const char *data, size_t len, loff_t *offset)
{
	printk(KERN_INFO "%d bytes written!!\n",len);
	return len;
}


/* Displays NRF module register info*/
static ssize_t nrf_read(struct file *fp, char *buf, size_t len, loff_t *offset){
	
	uint8_t *ret;
	char s[64];
	// int loop;
	
	uint8_t arg_val[5];
	int count=0;
	
	uint8_t recv_buff[32];
	uint8_t recv_len;		//uint8_t len = spiRead(RH_NRF24_COMMAND_R_RX_PL_WID);
	int ind;



	/*avoid repeated read*/
	if(*offset > 0)
		goto out;
	
	// ------------------------- set mode RX ------------------------------------------------------------
	SetGPIOOutputValue(NRF_CE, 1);
	mdelay(100);
	
	// ------------------- read RX payload len ----------------------------------------------------------
	ret = nrf_xfer(R_RX_PL_WID, 1, NULL, R);
	recv_len = ret[0];
	mdelay(10);

	// -------------------------- Clear read interrupt --------------------------------------------------
	// nrf_interrupt_clear();

	// -------------------------- read RX buffer --------------------------------------------------------
	ret = nrf_xfer(R_RX_PAYLOAD, recv_len, NULL, R);
	ret[31] = 0;	//string terminator char (just to be sure)
	
	//--------------------------- send message to user space --------------------------------------------		
	sprintf(s,"NRF %s", &ret[4]);	//Payload starts at 4
	if(copy_to_user(buf+count,s,strlen(s))){
		return -EFAULT;
	} 

	*offset += strlen(s);	
	count+= strlen(s);
				
	// ------------------------- RX flush ----------------------------------------------------------------
	//nrf_xfer(FLUSH_RX, 0, NULL, R);


	return count;
out:
return 0;
}

struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = nrf_open,
	.release = nrf_release,
	.read = nrf_read,
	.write = nrf_write,
};

/******************************
 creates device class and device node
******************************/
static int reg_dev(void)
{
	int retval=0;

	retval = alloc_chrdev_region(&dev,0,1,"nrf");
	if(retval != 0){
		printk(KERN_ALERT "device registration failed!!\n");
		goto out;
	}else{
		printk(KERN_INFO "device registration is successful!!\n");	
	}
	
	nrf_class = class_create(THIS_MODULE,"radioClass");
	if(IS_ERR(nrf_class)){
		unregister_chrdev_region(dev, 1);
		printk(KERN_ALERT "adding to class is failed!!\n");	
		retval = -1;
		goto out;
	}
	printk(KERN_INFO "device class is registerd!!\n");	

	nrf_device = device_create(nrf_class,NULL,MKDEV(MAJOR(dev),0),NULL,"nrf");
	if(IS_ERR(nrf_device)){
		class_destroy(nrf_class);
		unregister_chrdev_region(dev, 1);
		printk(KERN_ALERT "registering device is failed!!\n");	
		retval = -ENODEV;
		goto out;
	}

	nrf_cdev = cdev_alloc();
	cdev_init(nrf_cdev,&fops);
	nrf_cdev->owner = THIS_MODULE;

	retval = cdev_add(nrf_cdev,MKDEV(MAJOR(dev),0),1);
	if(retval < 0){
		class_destroy(nrf_class);
		unregister_chrdev_region(dev, 1);
		device_destroy(nrf_class, dev);
		printk(KERN_ALERT "adding to cdev is failed!!\n");
		goto out;
	}

	

	printk(KERN_INFO "device is registerd!!\n");	
	
	return 0;

	out:
	return retval;
}

/******************************
 register spi device and attach it to Master driver
******************************/
static int reg_spi_device(void)
{
	int retval = 0;
	
	struct spi_board_info spi_device_info = {
		.modalias = "nrf24l01+",
		.max_speed_hz = 1000000,
		.bus_num = 1,
		.chip_select = 0,
		.mode = 0,
	};

	struct spi_master *master;
	
	master = spi_busnum_to_master(spi_device_info.bus_num);
	if(!master){
		printk(KERN_ALERT "getting master device is failed!!\n");	
		retval = -ENODEV;
		goto out;
	}
	
	spi_device = spi_new_device(master,&spi_device_info);
	if(!spi_device){
		printk(KERN_ALERT "registering spi device is failed!!\n");	
		retval = -ENODEV;
		goto out;
	}
	
	spi_device->bits_per_word = 8;

	retval = spi_setup(spi_device);
	if(retval){
		spi_unregister_device(spi_device);
		goto out;
	}

	return 0;

	out:
	return retval;
}

/******************************
 Module initialization function
******************************/
static int __init nrf_init(void)
{
	int retval = 0;

	printk(KERN_INFO "hello from module!!\n");
	
	retval = reg_dev();
	if(retval != 0)
		goto out;
	
	retval = reg_spi_device();
	if(retval != 0)
		goto out;


	radio_init();

	return 0;
	
	out:
	return retval;
}

/******************************
 Module exit function
******************************/
static void __exit nrf_exit(void)
{
	printk(KERN_ALERT "Bye from module!!\n");
	nrf_power_down();
	spi_unregister_device(spi_device);
	device_destroy(nrf_class,MKDEV(MAJOR(dev),0));
	class_destroy(nrf_class);
	class_unregister(nrf_class);
	cdev_del(nrf_cdev);
	unregister_chrdev_region(MKDEV(MAJOR(dev),0),1);	
}

ssize_t print_registers(char* buf, int* count2, loff_t* offset)
{
	uint8_t *ret;
	char s[64];
	int loop;
	int count = *count2;

		for(loop = 0; loop < 11; loop++){

		//ret = spi_w8r8(spi_device,nrf_reg[loop]);
		ret = nrf_xfer(nrf_reg[loop],1,NULL,R);
		mdelay(10);
		sprintf(s,"%s = 0x%02x\n",nrf_reg_name[loop],ret[0]);
		if(copy_to_user(buf+count,s,strlen(s))){
			return -EFAULT;
		}
		*offset += strlen(s);	
		count+= strlen(s);
	}

	ret = nrf_xfer(RX_ADDR_P0 ,5,NULL,R);
	mdelay(10);
	// printk("VALOR LIDO AGORA = 0x%02x\n", *ret);
	sprintf(s,"RX_ADDR_P0 = 0x%02x%02x%02x%02x%02x\n", ret[0], ret[1], ret[2], ret[3], ret[4]);
	//sprintf(s,"Valor = 0x%02x\n", *ret);
	if(copy_to_user(buf+count,s,strlen(s))){
		return -EFAULT;
	} 
	*offset += strlen(s);	
	count+= strlen(s);
//	
	ret = nrf_xfer(RX_ADDR_P1 ,5,NULL,R);
	mdelay(10);
	// printk("VALOR LIDO AGORA = 0x%02x\n", *ret);
	sprintf(s,"RX_ADDR_P1 = 0x%02x%02x%02x%02x%02x\n", ret[0], ret[1], ret[2], ret[3], ret[4]);
	//sprintf(s,"Valor = 0x%02x\n", *ret);
	if(copy_to_user(buf+count,s,strlen(s))){
		return -EFAULT;
	} 
	*offset += strlen(s);	
	count+= strlen(s);
//
	ret = nrf_xfer(RX_ADDR_P2 ,1,NULL,R);
	mdelay(10);
	sprintf(s,"RX_ADDR_P2 = 0x%02x\n", *ret);
	if(copy_to_user(buf+count,s,strlen(s))){
		return -EFAULT;
	} 
	*offset += strlen(s);	
	count+= strlen(s);
//
	ret = nrf_xfer(RX_ADDR_P3 ,1,NULL,R);
	mdelay(10);
	sprintf(s,"RX_ADDR_P3 = 0x%02x\n", *ret);
	if(copy_to_user(buf+count,s,strlen(s))){
		return -EFAULT;
	} 
	*offset += strlen(s);	
	count+= strlen(s);
//
	ret = nrf_xfer(RX_ADDR_P4 ,1,NULL,R);
	mdelay(10);
	sprintf(s,"RX_ADDR_P4 = 0x%02x\n", *ret);
	if(copy_to_user(buf+count,s,strlen(s))){
		return -EFAULT;
	} 
	*offset += strlen(s);	
	count+= strlen(s);
//
	ret = nrf_xfer(RX_ADDR_P5 ,1,NULL,R);
	mdelay(10);
	sprintf(s,"RX_ADDR_P5 = 0x%02x\n", *ret);
	if(copy_to_user(buf+count,s,strlen(s))){
		return -EFAULT;
	} 
	*offset += strlen(s);	
	count+= strlen(s);
//
	ret = nrf_xfer(TX_ADDR ,5,NULL,R);
	mdelay(10);
	// printk("VALOR LIDO AGORA = 0x%02x\n", *ret);
	sprintf(s,"TX_ADDR = 0x%02x%02x%02x%02x%02x\n", ret[0], ret[1], ret[2], ret[3], ret[4]);
	//sprintf(s,"Valor = 0x%02x\n", *ret);
	if(copy_to_user(buf+count,s,strlen(s))){
		return -EFAULT;
	} 
	*offset += strlen(s);	
	count+= strlen(s);


//
	ret = nrf_xfer(RX_PW_P0 ,1,NULL,R);
	mdelay(10);
	sprintf(s,"RX_PW_P0 = 0x%02x\n", *ret);
	if(copy_to_user(buf+count,s,strlen(s))){
		return -EFAULT;
	} 
	*offset += strlen(s);	
	count+= strlen(s);
//
	ret = nrf_xfer(RX_PW_P1 ,1,NULL,R);
	mdelay(10);
	sprintf(s,"RX_PW_P1 = 0x%02x\n", *ret);
	if(copy_to_user(buf+count,s,strlen(s))){
		return -EFAULT;
	} 
	*offset += strlen(s);	
	count+= strlen(s);
//
	ret = nrf_xfer(RX_PW_P2 ,1,NULL,R);
	mdelay(10);
	sprintf(s,"RX_PW_P2 = 0x%02x\n", *ret);
	if(copy_to_user(buf+count,s,strlen(s))){
		return -EFAULT;
	} 
	*offset += strlen(s);	
	count+= strlen(s);
//
	ret = nrf_xfer(RX_PW_P3 ,1,NULL,R);
	mdelay(10);
	sprintf(s,"RX_PW_P3 = 0x%02x\n", *ret);
	if(copy_to_user(buf+count,s,strlen(s))){
		return -EFAULT;
	} 
	*offset += strlen(s);	
	count+= strlen(s);
//
	ret = nrf_xfer(RX_PW_P4 ,1,NULL,R);
	mdelay(10);
	sprintf(s,"RX_PW_P4 = 0x%02x\n", *ret);
	if(copy_to_user(buf+count,s,strlen(s))){
		return -EFAULT;
	} 
	*offset += strlen(s);	
	count+= strlen(s);
//
	ret = nrf_xfer(RX_PW_P5 ,1,NULL,R);
	mdelay(10);
	sprintf(s,"RX_PW_P5 = 0x%02x\n", *ret);
	if(copy_to_user(buf+count,s,strlen(s))){
		return -EFAULT;
	} 
	*offset += strlen(s);	
	count+= strlen(s);

	*count2 = count;
	return 0;
}

module_init(nrf_init);
module_exit(nrf_exit);
module_param_array(address,uint,NULL,0);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nisarg Patel");
MODULE_VERSION("v0.1");
MODULE_DESCRIPTION("Driver for 2.4 Ghz RF module nrf24L01+");
