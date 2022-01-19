#include <linux/types.h>

#define BCM2835_PERI_BASE       0x7E000000
#define GPIO_BASE (BCM2835_PERI_BASE + 0x200000) // GPIO controller


struct GpioRegisters
{
	uint32_t GPFSEL[6];
	uint32_t Reserved1;
	uint32_t GPSET[2];
	uint32_t Reserved2;
	uint32_t GPCLR[2];
};

void SetGPIOFunction(struct GpioRegisters *s_pGpioRegisters, int GPIO, int functionCode);
void SetGPIOOutputValue(struct GpioRegisters *s_pGpioRegisters, int GPIO, bool outputValue);
