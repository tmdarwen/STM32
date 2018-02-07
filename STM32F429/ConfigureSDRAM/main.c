#define PWR_BASE_ADDRESS            0x40007000
#define PWR_CR                      PWR_BASE_ADDRESS + 0x00  // PWR power control register
#define PWR_CSR                     PWR_BASE_ADDRESS + 0x04  // PWR power control register

#define RCC_BASE_ADDRESS            0x40023800
#define RCC_CR                      RCC_BASE_ADDRESS + 0x00  // RCC clock control register
#define RCC_PLLCFGR                 RCC_BASE_ADDRESS + 0x04  // RCC PLL configuration register
#define RCC_CFGR                    RCC_BASE_ADDRESS + 0x08  // RCC clock configuration register
#define RCC_AHB1ENR                 RCC_BASE_ADDRESS + 0x30  // RCC AHB1 peripheral clock enable (datasheet pg 242)
#define RCC_AHB3ENR                 RCC_BASE_ADDRESS + 0x38  // RCC AHB3 peripheral clock enable (datasheet pg 245)
#define RCC_APB1ENR                 RCC_BASE_ADDRESS + 0x40  // RCC APB1 peripheral clock enable register (pg 117)

#define GPIOB_BASE_ADDRESS          0x40020400
#define GPIOB_MODER                 GPIOB_BASE_ADDRESS + 0x00 // GPIO port mode register
#define GPIOB_OSPEEDR               GPIOB_BASE_ADDRESS + 0x08 // GPIO port output speed register
#define GPIOB_PUPR                  GPIOB_BASE_ADDRESS + 0x0C // GPIO port pull-up/pull-down register
#define GPIOB_IDR                   GPIOB_BASE_ADDRESS + 0x10 // GPIO port input data register
#define GPIOB_ODR                   GPIOB_BASE_ADDRESS + 0x14 // GPIO port output data register
#define GPIOB_AFRL                  GPIOB_BASE_ADDRESS + 0x20 // GPIO alternate function low register

#define GPIOC_BASE_ADDRESS          0x40020800
#define GPIOC_MODER                 GPIOC_BASE_ADDRESS + 0x00 // GPIO port mode register
#define GPIOC_OSPEEDR               GPIOC_BASE_ADDRESS + 0x08 // GPIO port output speed register
#define GPIOC_PUPR                  GPIOC_BASE_ADDRESS + 0x0C // GPIO port pull-up/pull-down register
#define GPIOC_ODR                   GPIOC_BASE_ADDRESS + 0x14 // GPIO port output data register
#define GPIOC_AFRL                  GPIOC_BASE_ADDRESS + 0x20 // GPIO alternate function low register

#define GPIOD_BASE_ADDRESS          0x40020C00
#define GPIOD_MODER                 GPIOD_BASE_ADDRESS + 0x00 // GPIO port mode register
#define GPIOD_OSPEEDR               GPIOD_BASE_ADDRESS + 0x08 // GPIO port output speed register
#define GPIOD_PUPR                  GPIOD_BASE_ADDRESS + 0x0C // GPIO port pull-up/pull-down register
#define GPIOD_ODR                   GPIOD_BASE_ADDRESS + 0x14 // GPIO port output data register
#define GPIOD_AFRL                  GPIOD_BASE_ADDRESS + 0x20 // GPIO alternate function low register
#define GPIOD_AFRH                  GPIOD_BASE_ADDRESS + 0x24 // GPIO alternate function high register

#define GPIOE_BASE_ADDRESS          0x40021000
#define GPIOE_MODER                 GPIOE_BASE_ADDRESS + 0x00 // GPIO port mode register
#define GPIOE_OSPEEDR               GPIOE_BASE_ADDRESS + 0x08 // GPIO port output speed register
#define GPIOE_PUPR                  GPIOE_BASE_ADDRESS + 0x0C // GPIO port pull-up/pull-down register
#define GPIOE_ODR                   GPIOE_BASE_ADDRESS + 0x14 // GPIO port output data register
#define GPIOE_AFRL                  GPIOE_BASE_ADDRESS + 0x20 // GPIO alternate function low register
#define GPIOE_AFRH                  GPIOE_BASE_ADDRESS + 0x24 // GPIO alternate function high register

#define GPIOF_BASE_ADDRESS          0x40021400
#define GPIOF_MODER                 GPIOF_BASE_ADDRESS + 0x00 // GPIO port mode register
#define GPIOF_OSPEEDR               GPIOF_BASE_ADDRESS + 0x08 // GPIO port output speed register
#define GPIOF_PUPR                  GPIOF_BASE_ADDRESS + 0x0C // GPIO port pull-up/pull-down register
#define GPIOF_ODR                   GPIOF_BASE_ADDRESS + 0x14 // GPIO port output data register
#define GPIOF_AFRL                  GPIOF_BASE_ADDRESS + 0x20 // GPIO alternate function low register
#define GPIOF_AFRH                  GPIOF_BASE_ADDRESS + 0x24 // GPIO alternate function high register

#define GPIOG_BASE_ADDRESS          0x40021800
#define GPIOG_MODER                 GPIOG_BASE_ADDRESS + 0x00 // GPIO port mode register
#define GPIOG_OSPEEDR               GPIOG_BASE_ADDRESS + 0x08 // GPIO port output speed register
#define GPIOG_PUPR                  GPIOG_BASE_ADDRESS + 0x0C // GPIO port pull-up/pull-down register
#define GPIOG_IDR                   GPIOG_BASE_ADDRESS + 0x10 // GPIO port input data register
#define GPIOG_ODR                   GPIOG_BASE_ADDRESS + 0x14 // GPIO port output data register
#define GPIOG_AFRL                  GPIOG_BASE_ADDRESS + 0x20 // GPIO alternate function low register
#define GPIOG_AFRH                  GPIOG_BASE_ADDRESS + 0x24 // GPIO alternate function high register


  // See pg 64 of STM RM0090.  It shows the memory 0xA000.0000-0xA000.0FFF and refers you to Section 37.8: FMC register
  // map on page 1677.  FMC = "Flexible Memory Controller".
  //
  // See pg 86 of the STM32F427xx/STM32F429xx datasheet (STM filename "en.DM00071990.pdf").  This shows the FMC Control
  // Register ranges from 0xA000.0000-0xA000.0FFF.
  //
  // See pg 1678.  0x148 is the FMC_SDTR1 register.
  //

#define FMC_CONTROL_REGISTER_BASE     0xA0000000
#define FMC_SDCR1                     FMC_CONTROL_REGISTER_BASE + 0x140
#define FMC_SDCR2                     FMC_CONTROL_REGISTER_BASE + 0x144
#define FMC_SDTR1                     FMC_CONTROL_REGISTER_BASE + 0x148
#define FMC_SDTR2                     FMC_CONTROL_REGISTER_BASE + 0x14C
#define FMC_SDCMR                     FMC_CONTROL_REGISTER_BASE + 0x150
#define FMC_SDRTR                     FMC_CONTROL_REGISTER_BASE + 0x154  // SDRAM Refresh Timer register (pg 1675)
#define FMC_SDSR                      FMC_CONTROL_REGISTER_BASE + 0x158

#define FLASH_BASE_ADDRESS   0x40023C00
#define FLASH_ACR            FLASH_BASE_ADDRESS + 0x00  // Flash access control register (pg 58)


#define ACCESS(address)      *((volatile unsigned int*)(address))

#define BUFFER_SIZE         ((unsigned int)0x0100)
#define WRITE_READ_ADDR     ((unsigned int)0x0800)
#define REFRESH_COUNT       ((unsigned int)0x056A)   /* SDRAM refresh counter (90MHz SDRAM clock) */

#define SDRAM_BANK_ADDR                 ((unsigned int)0xD0000000)

  
/* Read/Write Buffers */
unsigned int writerBuffer[BUFFER_SIZE];
unsigned int readBuffer[BUFFER_SIZE];

unsigned int uwIndex = 0;
volatile unsigned int uwWriteReadStatus = 0;


void ConfigureClockSpeed()
{
	ACCESS(RCC_APB1ENR) |= (1 << 28);  // Enable power to the clock

	ACCESS(RCC_CR) |= (1 << 16);              // Turn the HSE on...
	while((ACCESS(RCC_CR) & (1 << 17)) == 0); // ...Wait until the HSE is on.

	ACCESS(RCC_PLLCFGR) &= ~0x3F;         // Clear PLLM
	ACCESS(RCC_PLLCFGR) |= 8;             // ...then set it to 8.

	ACCESS(RCC_PLLCFGR) &= ~(0x1FF << 6); // Clear PLLN
	ACCESS(RCC_PLLCFGR) |= (360 << 6);    // ...then set it to 200.

	ACCESS(RCC_PLLCFGR) &= ~(3 << 16);    // Clear PLLP (So it's set to 2)

	ACCESS(RCC_PLLCFGR) |= (1 << 22);    // Set the HSE as the source

	ACCESS(RCC_PLLCFGR) &= ~(0xF << 24);    // Clear PLLQ
	ACCESS(RCC_PLLCFGR) |= (7 << 24);     // ...then set it to 7.

	ACCESS(RCC_CR) |= (1 << 24);              // Turn the PLL on...
	while((ACCESS(RCC_CR) & (1 << 25)) == 0); // ...Wait until the PLL is on.

	ACCESS(PWR_CR) |= (1 << 16);              // Enable over-drive...
	while((ACCESS(PWR_CSR) & (1 << 16)) == 0); // ...Wait until over-drive is ready

	ACCESS(PWR_CR) |= (1 << 17);              // Enable over-drive switching...
	while((ACCESS(PWR_CSR) & (1 << 17)) == 0); // ...Wait until over-drive switching is ready

	ACCESS(FLASH_ACR) &= ~0x7;   // Clear the flash latency...
	ACCESS(FLASH_ACR) |= 0x5;    // ...and set it to five wait states.

	ACCESS(RCC_CFGR) |= (0x1 << 1);
	while((ACCESS(RCC_CFGR) & (1 << 1)) == 0); // ...Wait until the SW1 is on.

	ACCESS(RCC_CFGR) |= (0x5 << 10);
	ACCESS(RCC_CFGR) |= (0x4 << 13);
}

void InitLEDs()
{
	ACCESS(RCC_AHB1ENR) |= (1 << 6); // Give a clock to port A

	// See schematics on page 33 of ST document UM1670.  The green LED is connected to 
	// pin G13 and red LED is connected to G14.
	ACCESS(GPIOG_MODER) |= ((1 << 26) | (1 << 28)); // Set pins to output
	ACCESS(GPIOG_OSPEEDR) |= ((0x3 << 26) | (0x3 << 28)); // Set pins to high speed
}

void InitSDRAM()
{
	// Give a clock to ports B-thru-G
	ACCESS(RCC_AHB1ENR) |= ((1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6));

	// Give a clock to the FMC (Flexible Memory Controller)
	ACCESS(RCC_AHB3ENR) |= 1;

	ACCESS(GPIOB_MODER) |= ((0x2 << 10) | (0x2 << 12));
	ACCESS(GPIOB_OSPEEDR) |= ((0x3 << 10) | (0x3 << 12));
	ACCESS(GPIOB_IDR) &= ~(0x1 << 5);
	ACCESS(GPIOB_AFRL) |= ((0xC << 20) | (0xC << 24));

	ACCESS(GPIOC_MODER) |= 0x2;
	ACCESS(GPIOC_OSPEEDR) |= 0x3;
	ACCESS(GPIOC_AFRL) |= 0xC;

	ACCESS(GPIOD_MODER) |= (0x2 | (0x2 << 2) | (0x2 << 16) | (0x2 << 18) | (0x2 << 20) | (0x2 << 28) | (0x2 << 30));
	ACCESS(GPIOD_OSPEEDR) |= (0x3 | (0x3 << 2) | (0x3 << 16) | (0x3 << 18) | (0x3 << 20) | (0x3 << 28) | (0x3 << 30));
	ACCESS(GPIOD_AFRL) |= (0xC | (0xC << 4));
	ACCESS(GPIOD_AFRH) |= (0xC | (0xC << 4) | (0xC << 8) | (0xC << 24) | (0xC << 28));

	ACCESS(GPIOE_MODER) |= (0x2 | (0x2 << 2) | (0x2 << 14) | (0x2 << 16) | (0x2 << 18) | (0x2 << 20) | (0x2 << 22) | (0x2 << 24) | (0x2 << 26) | (0x2 << 28) | (0x2 << 30));
	ACCESS(GPIOE_OSPEEDR) |= (0x3 | (0x3 << 2) | (0x3 << 14) | (0x3 << 16) | (0x3 << 18) | (0x3 << 20) | (0x3 << 22) | (0x3 << 24) | (0x3 << 26) | (0x3 << 28) | (0x3 << 30));
	ACCESS(GPIOE_AFRL) |= (0xC | (0xC << 4) | (0xC << 28));
	ACCESS(GPIOE_AFRH) |= (0xC | (0xC << 4) | (0xC << 8) | (0xC << 12) | (0xC << 16) | (0xC << 20) | (0xC << 24) | (0xC << 28));

	ACCESS(GPIOF_MODER) |= (0x2 | (0x2 << 2) | (0x2 << 4) | (0x2 << 6) | (0x2 << 8) | (0x2 << 10) | (0x2 << 22) | (0x2 << 24) | (0x2 << 26) | (0x2 << 28) | (0x2 << 30));
	ACCESS(GPIOF_OSPEEDR) |= (0x3 | (0x3 << 2) | (0x3 << 4) | (0x3 << 6) | (0x3 << 8) | (0x3 << 10) | (0x3 << 22) | (0x3 << 24) | (0x3 << 26) | (0x3 << 28) | (0x3 << 30));
	ACCESS(GPIOF_AFRL) |= (0xC | (0xC << 4) | (0xC << 8) | (0xC << 12) | (0xC << 16) | (0xC << 20));
	ACCESS(GPIOF_AFRH) |= ((0xC << 12) | (0xC << 16) | (0xC << 20) | (0xC << 24) | (0xC << 28));

	ACCESS(GPIOG_MODER) |= (0x2 | (0x2 << 2) | (0x2 << 8) | (0x2 << 10) | (0x2 << 16) | (0x2 << 30));
	ACCESS(GPIOG_OSPEEDR) |= (0x3 | (0x3 << 2) | (0x3 << 8) | (0x3 << 10) | (0x3 << 16) | (0x3 << 30));
	ACCESS(GPIOG_IDR) &= (1 | (1 << 1) | (1 << 4) | (1 << 5) | (1 << 8));
	ACCESS(GPIOG_AFRL) |= (0xC | (0xC << 4) | (0xC << 16) | (0xC << 20));
	ACCESS(GPIOG_AFRH) |= (0xC | (0xC << 28));


	// Initialize SDRAM control Interface
	ACCESS(FMC_SDCR1) &= ((unsigned int)~(0x3 << 10 | 0x1 << 12 | 0x3 << 13));
	ACCESS(FMC_SDCR1) |= (0xc00 | 0x2000);

	ACCESS(FMC_SDCR2) &= ~(0x7FFF);
	ACCESS(FMC_SDCR2) |= (0x4 | 0x10 | 0x40 | 0x180);


	// Initialize SDRAM timing Interface
	ACCESS(FMC_SDTR1) &= ((unsigned int)~(0xFU << 12 | 0xFU << 20));  // Clear out TRC and TRP
	ACCESS(FMC_SDTR1) |= (unsigned int)((((7)-1U) << 12U) | (((2)-1U) << 20U));


	// Set SDRAM Timing register 2 to the following:
	// Load Module Register Delay: 2 cycles
	// Exit Self-Refresh Delay: 7 cycles
	// Self Refresh Time: 4 cycles
	// Row Cycle Delay: 1 cycle
	// Recovery Delay: 2 cycles
	// Row Precharge Delay: 1 cycle
	// Row to Column Delay: 2 cycles
	ACCESS(FMC_SDTR2) &= ~(0xFFFFFFF);  // Clear all of the settings
	ACCESS(FMC_SDTR2) |= (unsigned int)((((2)-1U) | (((7)-1U) << 4U) | (((4)-1U) << 8U) | (((2)-1U) <<16U) | (((2)-1U) << 24U)));

	// Step 3:  Configure a clock configuration enable command
	ACCESS(FMC_SDCMR) = (1 | (0x1U << (3U)));
	while((ACCESS(FMC_SDSR) & (1 << 5))); // See pg 1676 - Block until the SDRAM controller is ready to accept a new request

	// Wait 100ms
	volatile unsigned int counter = 100000;
	while(counter) { --counter; }

	// Step 5: Configure a PALL (precharge all) command
	ACCESS(FMC_SDCMR) = ((1 << 1) | (1 << 3));
	while((ACCESS(FMC_SDSR) & (1 << 5))); // See pg 1676 - Block until the SDRAM controller is ready to accept a new request
 
	// Step 6 : Configure a Auto-Refresh comman
	ACCESS(FMC_SDCMR) = (3 | (1 << 3) | (3 << 5));
	while((ACCESS(FMC_SDSR) & (1 << 5))); // See pg 1676 - Block until the SDRAM controller is ready to accept a new request

	// Step 7: Program the external memory mode register 
	ACCESS(FMC_SDCMR) = ((1 << 2) | (1 << 3) | ((1 | 0x30 | 0x200) << 9));
	while((ACCESS(FMC_SDSR) & (1 << 5))); // See pg 1676 - Block until the SDRAM controller is ready to accept a new request

	/* Step 8: Set the refresh rate counter */
	/* (15.62 us x Freq) - 20 */
	/* Set the device refresh counter */
	//myHAL_SDRAM_ProgramRefreshRate(hsdram, REFRESH_COUNT);
	ACCESS(FMC_SDRTR) |= (REFRESH_COUNT << 1U);
}

void WriteReadTest()
{
	for(unsigned int i = 0; i < BUFFER_SIZE; ++i)
	{
		writerBuffer[i] = 0xDEADBEEF + i;
	}

	// Write data to the SDRAM memory
	unsigned int* sdram = (unsigned int*)(SDRAM_BANK_ADDR + WRITE_READ_ADDR);
	for(unsigned int i = 0; i < BUFFER_SIZE; i++)
	{
		sdram[i] = writerBuffer[i];
	}
	
	// Read back data from the SDRAM memory
	for(unsigned int i = 0; i < BUFFER_SIZE; i++)
	{
		readBuffer[i] = sdram[i];
	} 

	// Confirm the SDRAM has the correct data
	for(unsigned int i = 0; i < BUFFER_SIZE; i++)
	{
		if(readBuffer[i] != writerBuffer[i])
		{
			// If the data does not match, light up the red LED on the board signifying failure
			ACCESS(GPIOG_ODR) |= (1 << 14);
			return;
		}
	}	

	// If all data macthes, we're good.  Light up the green LED to show this is true.
	ACCESS(GPIOG_ODR) |= (1 << 13);
}

int main()
{
	InitLEDs();

	ConfigureClockSpeed();

	InitSDRAM();

	WriteReadTest();

	while(1);
}

