#define RCC_BASE_ADDRESS            0x40023800
#define RCC_AHB1ENR                 RCC_BASE_ADDRESS + 0x30  // RCC AHB1 peripheral clock enable register (pg 116)

#define GPIOD_BASE_ADDRESS          0x40020C00
#define GPIOD_MODER                 GPIOD_BASE_ADDRESS + 0x00 // GPIO port mode register
#define GPIOD_OSPEEDR               GPIOD_BASE_ADDRESS + 0x08 // GPIO port output speed register
#define GPIOD_ODR                   GPIOD_BASE_ADDRESS + 0x14 // GPIO port output data register

#define SYSTICK_BASE_ADDRESS        0xE000E000
#define SYSTICK_CTRL                SYSTICK_BASE_ADDRESS + 0x10 // SysTick control and status register (pg 246 of DM00046982)
#define SYSTICK_LOAD                SYSTICK_BASE_ADDRESS + 0x14 // SysTick reload value register (pg 247 of DM00046982)
#define SYSTICK_VAL                 SYSTICK_BASE_ADDRESS + 0x18 // SysTick current value register (pg 248 of DM00046982)

#define ACCESS(address)            *((volatile unsigned int*)(address))

// This function is called when the systick interrupt occurs
void SysTick_Handler()
{
	// Toggle LEDs
	ACCESS(GPIOD_ODR) ^= ((1 << 12) | (1 << 13) | (1 << 14) | (1 << 15));
}

int main(void)
{
	// Give a clock to port D
	ACCESS(RCC_AHB1ENR) |= (1 << 3);

	// Set GPIO pins to output
	ACCESS(GPIOD_MODER) |= ((1 << 24) | (1 << 26) | (1 << 28) | (1 << 30));

	// Set to high speed
	ACCESS(GPIOD_OSPEEDR) |= ((3 << 24) | (3 << 26) | (3 << 28) | (3 << 30));

	// Set the systick interrupt timer to it's max value to create max delay
	ACCESS(SYSTICK_LOAD) |= 0xFFFFFF;

	// Set the systick inital value to zero
	ACCESS(SYSTICK_VAL) &= ~(0xFFFFFF);

	// Set the systick clock source to the processsor clock, enable the interrupt 
	// request and activate the the systick timer.
	ACCESS(SYSTICK_CTRL) |= ((1 << 2) | (1 << 1) | 1);

	while(1);
}

