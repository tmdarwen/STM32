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

// We configure the clock speed to 180 MHz
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
	// See Table 6 on pg 21 of ST's UM1670 document.  It shows all of the pins on ports
	// B-thru-G that are used to communicate with the SDRAM peripheral.  Example code 
	// from STM also includes this nice table below:
	// +-------------------+--------------------+--------------------+--------------------+
	// +                       SDRAM pins assignment                                      +
	// +-------------------+--------------------+--------------------+--------------------+
	// | PD0  <-> FMC_D2   | PE0  <-> FMC_NBL0  | PF0  <-> FMC_A0    | PG0  <-> FMC_A10   |
	// | PD1  <-> FMC_D3   | PE1  <-> FMC_NBL1  | PF1  <-> FMC_A1    | PG1  <-> FMC_A11   |
	// | PD8  <-> FMC_D13  | PE7  <-> FMC_D4    | PF2  <-> FMC_A2    | PG4  <-> FMC_BA0   |
	// | PD9  <-> FMC_D14  | PE8  <-> FMC_D5    | PF3  <-> FMC_A3    | PG5  <-> FMC_BA1   |
	// | PD10 <-> FMC_D15  | PE9  <-> FMC_D6    | PF4  <-> FMC_A4    | PG8  <-> FMC_SDCLK |
	// | PD14 <-> FMC_D0   | PE10 <-> FMC_D7    | PF5  <-> FMC_A5    | PG15 <-> FMC_NCAS  |
	// | PD15 <-> FMC_D1   | PE11 <-> FMC_D8    | PF11 <-> FMC_NRAS  |--------------------+
	// +-------------------| PE12 <-> FMC_D9    | PF12 <-> FMC_A6    |
	//                     | PE13 <-> FMC_D10   | PF13 <-> FMC_A7    |
	//                     | PE14 <-> FMC_D11   | PF14 <-> FMC_A8    |
	//                     | PE15 <-> FMC_D12   | PF15 <-> FMC_A9    |
	// +-------------------+--------------------+--------------------+
	// | PB5 <-> FMC_SDCKE1|
	// | PB6 <-> FMC_SDNE1 |
	// | PC0 <-> FMC_SDNWE |
	// +-------------------+

	// See pg 1661 (section 37.7.3) of ST's RM0090 document.  It shows the steps for SDRAM initialization.

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

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Step 1. "Program the memory device features into the FMC_SDCRx register. The SDRAM clock frequency, RBURST and RPIPE must
	// be programmed in the FMC_SDCR1 register"

	// Initialize SDRAM control interface.  After the next two lines of code, the values for the SDCR1 register:
	// See pg 1671 for the details of the FMC_SDCR register.  We set it up as follows:
	// Bits   1-0: Number of column address bits = 00 (8 bits)
	// Bits   3-2: Number of row address bits = 00 (11 bits)
	// Bits   5-4: Memory data bus width = 01 (16 bits)
	// Bit      6: Number of internal banks = 1
	// Bits   7-8: CAS Latency (See below for definition) = 01 (1 cycle)
	// Bit       9: Write protection = 1 (Write accesses ignored)
	// Bits 11-10: SDRAM clock configuration = 11 (SDCLK period = 3 x HCLK periods)
	// Bit     12: Burst read = 0 (single read requests are not managed as bursts)
	// Bit  13-14: Read pipe = 01 (One HCLK clock cycle delay)
	// Wikipedia tells me "Column Access Strobe (CAS) latency, or CL, is the delay time between the moment a memory controller tells
	// the memory module to access a particular memory column on a RAM module, and the moment the data from the given array location
	// is available on the module's output pins".
	ACCESS(FMC_SDCR1) &= ~((3 << 10) | (1 << 12) | (0x3 << 13)); // Clear bits 10-14
	ACCESS(FMC_SDCR1) |= ((3 << 10) | (1 << 13));


	// Initialize SDRAM control interface.  After the next two lines of code, the values for the SDCR2 register:
	// See pg 1671 for the details of the FMC_SDCR register.  We set it up as follows:
	// Bits   1-0: Number of column address bits = 00 (8 bits)
	// Bits   3-2: Number of row address bits = 01 (12 bits)
	// Bits   5-4: Memory data bus width = 01 (16 bits)
	// Bit      6: Number of internal banks = 1
	// Bits   7-8: CAS Latency (See below for definition) = 11 (3 cycle)
	// Bit       9: Write protection = 0 (Write accesses allowed)
	// Bits 11-10: SDRAM clock configuration = 00 (SDCLK clock disabled)
	// Bit     12: Burst read = 0 (single read requests are not managed as bursts)
	// Bit  13-14: Read pipe = 00 (No HCLK clock cycle delay)
	ACCESS(FMC_SDCR2) &= ~(0x7FFF); // Clear bits 0-14
	ACCESS(FMC_SDCR2) |= ((1 << 2) | (1 << 4) | (1 << 6) | (3 << 7));

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Step 2. "Program the memory device timing into the FMC_SDTRx register. The TRP and TRC timings must be programmed in
	// the FMC_SDTR1 register".  Note TRP = "Row precharge delay" (bits 20-23) and TRC = "Row cycle delay" (bits 12-15).

	// SDRAM Timing register 1 (See pg 1672).  After the next two lines of code, the values for the SDTR1 register:
	// Bits   3-0: Load Mode Register to Active = 1111 (16 cycles)
	// Bits   7-4: Exit Self-refresh delay = 1111 (16 cycles)
	// Bits  8-11: Self refresh time = 1111 (16 cycles)
	// Bits 12-15: Row cycle delay = 0110 (7 cycles)
	// Bits 16-19: Recovery delay = 1111 (16 cycles)
	// Bits 20-23: Row precharge delay = 0001 (2 cycles)
	// Bits 24-27: Row to column delay = 1111 (16 cycles)
	ACCESS(FMC_SDTR1) &= ((unsigned int)~(0xFU << 12 | 0xFU << 20));  // Clear out TRC and TRP
	ACCESS(FMC_SDTR1) |= (unsigned int)((((7)-1U) << 12U) | (((2)-1U) << 20U));


	// SDRAM Timing register 2 (See pg 1672).  After the next two lines of code, the values for the SDTR2 register:
	// Bits   3-0: Load Mode Register to Active = 0001 (2 cycles)
	// Bits   7-4: Exit Self-refresh delay = 0110 (5 cycles)
	// Bits  8-11: Self refresh time = 0011 (2 cycles)
	// Bits 12-15: Row cycle delay = 0000 (1 cycle)
	// Bits 16-19: Recovery delay = 0001 (2 cycles)
	// Bits 20-23: Row precharge delay = 0000 (1 cycle)
	// Bits 24-27: Row to column delay = 0001 (2 cycles)
	ACCESS(FMC_SDTR2) &= ~(0xFFFFFFF);  // Clear all of the settings
	ACCESS(FMC_SDTR2) |= (unsigned int)((((2)-1U) | (((7)-1U) << 4U) | (((4)-1U) << 8U) | (((2)-1U) <<16U) | (((2)-1U) << 24U)));

	// Step 3: "Set MODE bits to '001' and configure the Target Bank bits (CTB1 and/or CTB2) in the FMC_SDCMR register to start
	// delivering the clock to the memory (SDCKE is driven high)"
	// Bits  2-0: Command mode = 001 (Clock Configuration Enable)
	// Bit     3: Command Target Bank 2 = 1 (Command issued to SDRAM Bank 2)
	// Bit     4: Command Target Bank 1 = 0 (Command not issued to SDRAM Bank 1)
	// Bits  5-8: Number of Auto-refresh = 0000 (1 Auto-refresh cycle)
	// Bits 9-21: Mode Register definition = All zeros (no content)
	ACCESS(FMC_SDCMR) = (1 | (1 << 3));
	while((ACCESS(FMC_SDSR) & (1 << 5))); // See pg 1676 - Block until the SDRAM controller is ready to accept a new request

	// Step 4: "Wait during the prescribed delay period. Typical delay is around 100us (refer to the
	// SDRAM datasheet for the required delay after power-up)"
	// Totally unscientific here by just spinning 100,000 counts
	volatile unsigned int counter = 100000;
	while(counter) { --counter; }

	// Step 5: "Set MODE bits to '010' and configure the Target Bank bits (CTB1 and/or CTB2) in the FMC_SDCMR register to
	// issue a 'Precharge All' command"
	// Bits  2-0: Command mode = 010 (PALL (“All Bank Precharge”) command)
	// Bit     3: Command Target Bank 2 = 1 (Command issued to SDRAM Bank 2)
	// Bit     4: Command Target Bank 1 = 0 (Command not issued to SDRAM Bank 1)
	// Bits  5-8: Number of Auto-refresh = 0000 (1 Auto-refresh cycle)
	// Bits 9-21: Mode Register definition = All zeros (no content)
	ACCESS(FMC_SDCMR) = ((1 << 1) | (1 << 3));
	while((ACCESS(FMC_SDSR) & (1 << 5))); // See pg 1676 - Block until the SDRAM controller is ready to accept a new request
 
	// Step 6: "Set MODE bits to '011', and configure the Target Bank bits (CTB1 and/or CTB2) as well as the number of
	// consecutive Auto-refresh commands (NRFS) in the FMC_SDCMR register. Refer to the SDRAM datasheet for the number
	// of Auto-refresh commands that should be issued. Typical number is 8."
	// Bits  2-0: Command mode = 011 (Auto-refresh command)
	// Bit     3: Command Target Bank 2 = 1 (Command issued to SDRAM Bank 2)
	// Bit     4: Command Target Bank 1 = 0 (Command not issued to SDRAM Bank 1)
	// Bits  5-8: Number of Auto-refresh = 0011 (4 Auto-refresh cycles)
	// Bits 9-21: Mode Register definition = All zeros (no content)
	ACCESS(FMC_SDCMR) = (3 | (1 << 3) | (3 << 5));
	while((ACCESS(FMC_SDSR) & (1 << 5))); // See pg 1676 - Block until the SDRAM controller is ready to accept a new request

	// Step 7: Configure the MRD field according to your SDRAM device, set the MODE bits to '100', and configure the Target
	// Bank bits (CTB1 and/or CTB2) in the FMC_SDCMR register to issue a "Load Mode Register" command in order to program
	// the SDRAM. In particular:
	// a) The CAS latency must be selected following configured value in FMC_SDCR1/2 registers
	// b) The Burst Length (BL) of 1 must be selected by configuring the M[2:0] bits to 000 in the mode register (refer
	// to the SDRAM datasheet). If the Mode Register is not the same for both SDRAM banks, this step has to be repeated twice,
	// once for each bank, and the Target Bank bits set accordingly."
	// Bits  2-0: Command mode = 100 (Load Mode Register)
	// Bit     3: Command Target Bank 2 = 1 (Command issued to SDRAM Bank 2)
	// Bit     4: Command Target Bank 1 = 0 (Command not issued to SDRAM Bank 1)
	// Bits  5-8: Number of Auto-refresh = 0000 (1 Auto-refresh cycle)
	// Bits 9-21: Mode Register definition = 0x231 = 0010.0011.0001
	ACCESS(FMC_SDCMR) = ((1 << 2) | (1 << 3) | (0x231 << 9));
	while((ACCESS(FMC_SDSR) & (1 << 5))); // See pg 1676 - Block until the SDRAM controller is ready to accept a new request

	// Step 8: "Program the refresh rate in the FMC_SDRTR register The refresh rate corresponds to the delay between refresh
	// cycles. Its value must be adapted to SDRAM devices."
	// Comment from the STM example code: (15.62 us x Freq) - 20
	// This is also on pg 1676:
	//     COUNT = (SDRAM refresh rate x SDRAM clock frequency) - 20
	//     SDRAM refresh rate = SDRAM refresh period / Number of rows
	// See page 1675- the SDRAM Refresh Timer register
	// Bit     0: Clear Refresh error flag = 0
	// Bits 13-1: Refresh Timer Count = 01010110101 (693 decimal)
	// Bit    14: RES Interrupt Enable = 0 (Interrupt is disabled)
	// Okay, so if SDRAM Clock Frequency = 90 we have:
	// 693 = (x * 90) - 20 => 713 = 90x => x = 7.92
	ACCESS(FMC_SDRTR) |= (0x056A << 1U);
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

