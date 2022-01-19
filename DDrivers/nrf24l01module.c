#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/init.h>
#include <asm/io.h>
#include <linux/timer.h>
#include <linux/err.h>
#include <linux/mm.h>
#include <linux/spi/spi.h>

#include <linux/io.h>
//#include <mach/platform.h>

#include "utils.h"


#define DEVICE_NAME "nrf24"
#define CLASS_NAME "nrf24Class"
#define NRF_CE 17

// static const int spiCSPin = 8;
// static const int spiMISOPin = 9;
// static const int spiMOSIPin = 10;
// static const int spiSCLKPin = 11;


/* Device variables */
static struct class* nrf24Device_class = NULL;
static struct device* nrf24Device_device = NULL;
static dev_t nrf24Device_majorminor;
static struct cdev c_dev;  // Character device structure

struct GpioRegisters *s_pGpioRegisters;
static struct class *s_pDeviceClass;
static struct device *s_pDeviceObject;

static struct spi_device *my_spi_device;


void spi_write( uint8_t data ) //for configuration purposes
{
  int     ret = -1;
  uint8_t rx  = 0x00;
  
  if( my_spi_device )
  {    
    struct spi_transfer tr = 
    {
      .tx_buf  = &data,
      .rx_buf = &rx,
      .len    = 1,
    };
    spi_sync_transfer(my_spi_device, &tr, 1 );
  }
  
  //pr_info("Received = 0x%02X \n", rx);
}



static int reg_spi_device(void)
{

	int retval = 0;
	
	struct spi_board_info spi_device_info = {
		.modalias = "nrf24l01",
		.max_speed_hz = 1000000,
		.bus_num = 0,
		.chip_select = 1,
		.mode = 0,
	};

	struct spi_master *master;
	
	master = spi_busnum_to_master(spi_device_info.bus_num);
	if(!master){
		printk(KERN_ALERT "getting master device is failed!!\n");	
		retval = -ENODEV;
		return retval;
	}
	
	my_spi_device = spi_new_device(master,&spi_device_info);
	if(!my_spi_device){
		printk(KERN_ALERT "registering spi device is failed!!\n");	
		retval = -ENODEV;
		return retval;
	}
	
	my_spi_device->bits_per_word = 8;

	retval = spi_setup(my_spi_device);
	if(retval){
		spi_unregister_device(my_spi_device);
		return retval;
	}

	return 0;
	
}

static int reg_dev(void)
{

	if ((ret = alloc_chrdev_region(&nrf24Device_majorminor, 0, 1, DEVICE_NAME)) < 0) {
		return ret;
	}

	if (IS_ERR(nrf24Device_class = class_create(THIS_MODULE, CLASS_NAME))) {
		unregister_chrdev_region(nrf24Device_majorminor, 1);
		return PTR_ERR(nrf24Device_class);
	}
	if (IS_ERR(dev_ret = device_create(nrf24Device_class, NULL, nrf24Device_majorminor, NULL, DEVICE_NAME))) {
		class_destroy(nrf24Device_class);
		unregister_chrdev_region(nrf24Device_majorminor, 1);
		return PTR_ERR(dev_ret);
	}

	cdev_init(&c_dev, &nrf24_fops);
	c_dev.owner = THIS_MODULE;
	if ((ret = cdev_add(&c_dev, nrf24Device_majorminor, 1)) < 0) {
		printk(KERN_NOTICE "Error %d adding device", ret);
		device_destroy(nrf24Device_class, nrf24Device_majorminor);
		class_destroy(nrf24Device_class);
		unregister_chrdev_region(nrf24Device_majorminor, 1);
		return ret;
	}
	printk(KERN_INFO "device is registered!!\n");

	return 0;
}

static void __exit nrf_exit(void){
	printk(KERN_ALERT "Bye from module!!\n");
	nrf_power_down();
	iounmap(s_pGpioRegisters);
	spi_unregister_device(my_spi_device);
	device_destroy(nrf24Device_class,nrf24Device_majorminor);
	class_unregister(nrf24Device_class);
	class_destroy(nrf24Device_class);
	cdev_del(&c_dev);
	unregister_chrdev_region(nrf24Device_majorminor;1);
}

	

static int __init nrf_init(void)
{
	int retval = 0;

	uint8_t addr[5] = {0x12,0x12,0x12,0x12,0x12};

	s_pGpioRegisters = (struct GpioRegisters *)ioremap(GPIO_BASE, sizeof(struct GpioRegisters));

	SetGPIOFunction(s_pGpioRegisters,NRF_CE,1);
	SetGPIOOutputValue(s_pGpioRegisters,NRF_CE,0);

	printk(KERN_INFO "hello from module!!\n");
	
	retval = reg_dev();
	if(retval != 0)
		return retval;
	
	retval = reg_spi_device();
	if(retval != 0)
		return retval;


	nrf_enable_pipes(DATA_PIPE_0);
	retval = nrf_set_addr_width(5);
	if(retval){
		printk(KERN_ALERT "Error: setting addr width failed!\n");
		return retval;
	}

	retval = nrf_set_channel(1);
	if(retval){
		printk(KERN_ALERT "Error: setting RF channel freq!\n");
		return retval;
	}

	retval = nrf_set_speed(SPEED_1Mbps);
	if(retval){
		printk(KERN_ALERT "Error: setting transmission speed!\n");
		return retval;
	}

	retval = nrf_set_power(POWER_0DB);
	if(retval){
		printk(KERN_ALERT "Error: setting radio power!\n");
		return retval;
	}

	retval = nrf_set_rx_addr(addr,0);
	if(retval){
		printk(KERN_ALERT "Error: setting rx address!\n");
		return retval;
	}

	nrf_set_tx_addr(addr);

	retval = nrf_set_rx_width(1,0);
	if(retval){
		printk(KERN_ALERT "Error: setting pipe width!\n");
		return retval;
	}

	nrf_power_up();
	nrf_set_as_recv();
	return 0;
}

static struct file_operations nrf24_fops = {
.owner = THIS_MODULE,
.write = nrf_write,
.read = nrf_read,
.release = nrf_close,
.open = nrf_open,
};


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
	int loop;
	int count=0;
	
	/*avoid repeated read*/
	if(*offset > 0)
	return 0;	
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
	return count;
	
}


//NRF operations


/******************************
 Set module in transmitter mode
******************************/
void nrf_set_as_trans(void)
{
	uint8_t *val;
	uint8_t temp;

	val = nrf_xfer(CONFIG,1,NULL,R);
	temp = val[0];

	temp &= ~(1<<PRIM_RX);

	nrf_xfer(CONFIG,1,&temp,W);
}


/******************************
 Set module in receiver mode
******************************/
void nrf_set_as_recv(void)
{
	uint8_t *val;
	uint8_t temp;

	val = nrf_xfer(CONFIG,1,NULL,R);
	temp = val[0];

	temp |= (1<<PRIM_RX);

	nrf_xfer(CONFIG,1,&temp,W);
}


/******************************
 Power down nrf module
******************************/
void nrf_power_down(void)
{
	uint8_t *val;
	uint8_t temp;

	val = nrf_xfer(CONFIG,1,NULL,R);
	temp = val[0];

	temp &= ~(1<<PWR_UP);

	nrf_xfer(CONFIG,1,&temp,W);

}

/******************************
 Power up nrf module
******************************/
void nrf_power_up(void)
{
	uint8_t *val;
	uint8_t temp;

	val = nrf_xfer(CONFIG,1,NULL,R);
	temp = val[0];

	temp |= (1<<PWR_UP);

	nrf_xfer(CONFIG,1,&temp,W);

}


/******************************
 Enables Dynamic payload length on data pipes.
 e.g :
 nrf_enable_dynpd(DATA_PIPE_0 | DATA_PIPE_1);
 turns on data AA on pipe 0 & pipe 1
******************************/
void nrf_enable_dynpd(uint8_t pipe)
{
	nrf_xfer(DYNPD,1,&pipe,W);
}

/******************************
 checks whether RX FIFO is empty or not
******************************/
int is_rx_empty(void)
{
	if(nrf_xfer(FIFO_STATUS,1,NULL,R) && RX_EMPTY)
		return 1;
	else
		return 0;
}

/******************************
 checks whether RX FIFO is full or not
******************************/
int is_rx_full(void)
{
	if(nrf_xfer(FIFO_STATUS,1,NULL,R) && RX_FULL)
		return 1;
	else
		return 0;
}


/******************************
 checks whether TX FIFO is empty or not
******************************/
int is_tx_empty(void)
{
	if(nrf_xfer(FIFO_STATUS,1,NULL,R) && TX_EMPTY)
		return 1;
	else
		return 0;
}


/******************************
 checks whether TX FIFO is full or not
******************************/
int is_tx_full(void)
{
	if(nrf_xfer(FIFO_STATUS,1,NULL,R) && TX_FULL)
		return 1;
	else
		return 0;
}

/******************************
 sets RX payload width
******************************/
int nrf_set_rx_width(uint8_t width, uint8_t pipe)
{
	uint8_t cmd;

	if(width > 32)
		return -1;
	if(pipe > 5)
		return -1;

	cmd = RX_PW_P0 + pipe;

	switch(pipe){

		case 0:
			nrf_xfer(cmd, 1, &width, W);
			break;
		case 1:
			nrf_xfer(cmd, 1, &width, W);
			break;
		case 2:
			nrf_xfer(cmd, 1, &width, W);
			break;
		case 3:
			nrf_xfer(cmd, 1, &width, W);
			break;
		case 4:
			nrf_xfer(cmd, 1, &width, W);
			break;
		case 5:
			nrf_xfer(cmd, 1, &width, W);
			break;
	}
	return 0;
}

/******************************
 sets TX address (5 bytes)
******************************/
void nrf_set_tx_addr(uint8_t *val)
{
	nrf_xfer(TX_ADDR, 5, val, W);

}


/******************************
 sets address of different RX pipes
******************************/

int nrf_set_rx_addr(uint8_t *val, uint8_t pipe)
{
	uint8_t cmd;
	
	if(pipe > 5)
		return -1;

	cmd = RX_ADDR_P0 + pipe;

	switch(pipe){
		
		case 0:
			nrf_xfer(cmd, 5, val, W);
			break;
		case 1:
			nrf_xfer(cmd, 5, val, W);
			break;
		case 2:
			nrf_xfer(cmd, 1, val, W);
			break;
		case 3:
			nrf_xfer(cmd, 1, val, W);
			break;
		case 4:
			nrf_xfer(cmd, 1, val, W);
			break;
		case 5:
			nrf_xfer(cmd, 1, val, W);
			break;
	}
	return 0;
}


/******************************
 sets RF output power
 Note:- value range (0-3)
******************************/

int nrf_set_power(uint8_t power)
{
	
	uint8_t *val;
	uint8_t temp;

	if(power > 3)
		return -1;
	
	val = nrf_xfer(RF_SETUP, 1, NULL, R);
	temp = val[0];
	
	switch(power){

	case 0:
		temp &= ~((1<<1)+(1<<2));
		break;
	case 1:
		temp |= (1<<1);
		temp &= ~(1<<2);
		break;
	case 2:
		temp &= ~(1<<1);
		temp |= (1<<2);
		break;
	case 3:
		temp |= (1<<1) + (1<<2);
		break;
	default:
		break;

	}


	nrf_xfer(RF_SETUP, 1, &temp, W);

	return 0;
}


/******************************
 Sets communication speed
 Note:- 0----> 1Mbps
 	1----> 2Mbps
	2----> 250Kbps
******************************/

int nrf_set_speed(uint8_t speed)
{
	
	uint8_t *val;
	uint8_t temp;

	if(speed > 2)
		return -1;
	
	val = nrf_xfer(RF_SETUP, 1, NULL, R);
	temp = val[0];

	switch(speed){

	case 0:
		temp &= ~((1<<5)+(1<<3));
		break;
	case 1:
		temp &= ~(1<<5);
		temp |= (1<<3);
		break;
	case 2:
		temp |= (1<<5);
		temp &= ~(1<<3);
		break;
	default:
		break;
	}


	nrf_xfer(RF_SETUP, 1, &temp, W);

	return 0;
}


/******************************
 Sets nrf channel frequency
 note:- total channels 0 to 127
******************************/

int nrf_set_channel(uint8_t channel)
{
	if(channel > 127)
		return -1;

	nrf_xfer(RF_CH, 1, &channel, W);
	return 0;
}


/******************************
 Sets retransmission counts
 Note:- 0 = disabled, max value = 15
******************************/
int nrf_set_retrans_count(uint8_t count)
{
	uint8_t *val;

	if(count > 15)
		return -1;
	
	val = nrf_xfer(SETUP_RETR, 1, NULL, R);
	
	count = count | val[0];

	nrf_xfer(SETUP_RETR, 1, &count, W);
	return 0;
}


/******************************
 Sets retransmission delay
 Note:- value is between 0 to 15. each level adds 250us delay
 0 -----> 250us
 1 -----> 500us
 2 -----> 750us
 .         .
 .         .
******************************/

int nrf_set_retrans_delay(uint8_t delay)
{
	uint8_t *val;

	if(delay > 15)
		return -1;
	
	delay = delay << 4;
	val = nrf_xfer(SETUP_RETR,1,NULL,R);
	
	delay = delay | val[0];

	nrf_xfer(SETUP_RETR,1,&delay,W);
	return 0;
}


/******************************
 Sets RX/TX address width
 Note:- max value is 5 bytes and 0 bytes not allowed. If provided greater than that,
 function will return immediate and won't write to register
******************************/

int nrf_set_addr_width(uint8_t width)
{
	if(!(width > 2 || width < 6))
		return -1;
	width = width - 2;
	nrf_xfer(SETUP_AW, 1, &width, W);
	return 0;
}


/******************************
 Enables RX data pipes 
 
 e.g :
 nrf_enable_pipes(DATA_PIPE_0 | DATA_PIPE_1);
 turns on data AA on pipe 0 & pipe 1
******************************/

void nrf_enable_pipes(uint8_t pipe)
{
	nrf_xfer(EN_RXADDR, 1, &pipe, W);
}


/******************************
 Sets auto acknowledgement to given pipe numbers
 e.g :
 nrf_set_AA(DATA_PIPE_0 | DATA_PIPE_1);
 turns on data AA on pipe 0 & pipe 1
******************************/

void nrf_enable_AA(uint8_t pipe)
{
	nrf_xfer(EN_AA, 1, &pipe, W);
}


/******************************
 This function performs Read/Write to nrf chip.
 For write function:- 
 spi_write() is used and total number of bytes to be written 
 will be total number + 1.buffer will include command first and 
 data after that. command writing and data writing
 should be done in one function because of internal chip
 select handling in Linux.
 For read function:-
 For read, it is obvious to use spi_write_then_read() because
 we want to write command first and then read data. Due to internal
 chip select handling of Linux this function is suitable for nrf chip.
******************************/

uint8_t *nrf_xfer(uint8_t reg, size_t count, uint8_t *val, bool op)
{
	int retval;
	int loop;
	static uint8_t retarr[32];
	uint8_t len;
	
	len = count + 1;

	if(op == W){
		if(reg != W_TX_PAYLOAD)
			reg = reg + W_REGISTER;
	
		retarr[0] = reg;
		for(loop=1;loop < len;loop++){
			retarr[loop] = val[loop-1];
		}
		retval = spi_write(spi_device,retarr,len);
		if(retval != 0)
			printk(KERN_INFO "failed to write register to device\n");
		
	}

	if(op == R){

		retval = spi_write_then_read(spi_device,&reg,1,retarr,count);
		if(retval != 0)
			printk(KERN_INFO "failed to read from device\n");
	}

	return retarr;
}

module_init(nrf_init);
module_exit(nrf_exit);
MODULE_LICENSE("GPL");