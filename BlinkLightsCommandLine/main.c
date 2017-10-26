#define RCC_BASE_ADDRESS            0x40023800
#define RCC_AHB1ENR                 RCC_BASE_ADDRESS + 0x30  // RCC AHB1 peripheral clock enable register (pg 116)

#define GPIOD_BASE_ADDRESS          0x40020C00
#define GPIOD_MODER                 GPIOD_BASE_ADDRESS + 0x00 // GPIO port mode register
#define GPIOD_OSPEEDR               GPIOD_BASE_ADDRESS + 0x08 // GPIO port output speed register
#define GPIOD_ODR                   GPIOD_BASE_ADDRESS + 0x14 // GPIO port output data register

#define ACCESS(address)            *((volatile unsigned int*)(address))

int main(void)
{
	// Give a clock to port D
	ACCESS(RCC_AHB1ENR) |= (1 << 3);

	// Set GPIO pins to output
	ACCESS(GPIOD_MODER) |= ((1 << 24) | (1 << 26) | (1 << 28) | (1 << 30));

	// Set to high speed
	ACCESS(GPIOD_OSPEEDR) |= ((3 << 24) | (3 << 26) | (3 << 28) | (3 << 30));

	while(1)
	{
		// Toggle LEDs
		ACCESS(GPIOD_ODR) ^= ((1 << 12) | (1 << 13) | (1 << 14) | (1 << 15));

		// Waste some time
		for(volatile unsigned int i = 0; i < 500000; i++);
	}
}

