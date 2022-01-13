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

// static const int spiCSPin = 8;
// static const int spiMISOPin = 9;
// static const int spiMOSIPin = 10;
// static const int spiSCLKPin = 11;


/* Device variables */
static struct class* nrf24Device_class = NULL;
static struct device* nrf24Device_device = NULL;
static dev_t nrf24Device_majorminor;
static struct cdev c_dev;  // Character device structure


static struct class *s_pDeviceClass;
static struct device *s_pDeviceObject;

static struct spi_device *my_spi_device;


static int register_spi(void){

    struct spi_board_info spi_device_info = 
    {
    .modalias     = "spi-nrf24l01-driver",
    .max_speed_hz = 2500000,              // slave frequency 
    .bus_num      = 0,          // SPI 1
    .chip_select  = 0,  // Use 0 Chip select (GPIO 18)
    .mode         = 0            // SPI mode 0
    };

}


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

static int __init spi_init(void)
{
  int     ret;
  struct  spi_master *master;
  
  master = spi_busnum_to_master(spi_device_info.bus_num);
  if( master == NULL )
  {
    pr_err("SPI Master not found.\n");
    return -ENODEV;
  }
   
  // create a new slave device, given the master and device info
  my_spi_device = spi_new_device( master, &spi_device_info );
  if( spi_device == NULL ) 
  {
    pr_err("FAILED to create slave.\n");
    return -ENODEV;
  }
  
  // 8-bits in a word
  my_spi_device->bits_per_word = 8;
  // setup the SPI slave device
  ret = spi_setup( my_spi_device );
  if( ret )
  {
    pr_err("FAILED to setup slave.\n");
    spi_unregister_device( etx_spi_device );
    return -ENODEV;
  }



  static struct file_operations nrf24_fops = {
	.owner = THIS_MODULE,
	.write = spi_write,
	.read = spi_read,
	.release = spi_close,
	.open = spi_open,
};



MODULE_LICENSE("GPL");