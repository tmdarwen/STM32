//
//	EXAMPLE OF USING CS42L22 on STM32F4-Discovery
//
//	This code is based on A.Finkelmeyer's original code posted at:
//	http://www.mind-dump.net/configuring-the-stm32f4-discovery-for-audio
//	However, the code base has been heavily modified by Terence
//	Darwen - tmdarwen.com - to directly interact with the registers of the
//	STM32F4 instead of using the Standard Peripheral Library.
//
//	I'll frequently refer to page numbers in the documentation below.  This
//	is in reference to ST's "RM0383 Reference manual" which covers the
//	technical details of the STM32F411xC/E Advanced Arm-based 32-bit MCUs

#include "RegisterAddresses.h"
#include "AudioSample.h"
#include "Types.h"

#define ACCESS_8_BITS(address)  *((volatile uint8_t*)(address))
#define ACCESS_16_BITS(address) *((volatile uint16_t*)(address))
//#define ACCESS_16_BITS(address) *((volatile short*)(address))
#define ACCESS(address)         *((volatile uint32_t*)(address))

void InitializeCommunicationToDAC();
void WaitForTransmissionToFinish(uint32_t transmissionBits);
void SendMessageToDAC(uint8_t dacAddress, uint8_t setting);
uint8_t ReadMessageFromDAC(uint8_t mapbyte);
void InitializeDAC();
void StartAudioPlayback();

int main(void)
{
	uint32_t sampleCounter = 0;

	InitializeCommunicationToDAC();

	InitializeDAC();

	StartAudioPlayback();

	while(1)
	{
		// Left channel
		while((ACCESS_16_BITS(SPI3_I2S3_SR) & (1 << 1)) != (1 << 1));  // Wait until transfer buffer is empty
		ACCESS_16_BITS(SPI3_I2S3_DR) = audioSample[sampleCounter];     // Write audio sample to the data register

		// Right channel
		while((ACCESS_16_BITS(SPI3_I2S3_SR) & (1 << 1)) != (1 << 1));
		ACCESS_16_BITS(SPI3_I2S3_DR) = audioSample[sampleCounter];

		++sampleCounter;
		if(sampleCounter == audioSampleLength) sampleCounter = 0;
	}
}

void InitializeCommunicationToDAC()
{
	///////////////////////////////////////////////////////////////////////////////
	// Review ST UM1842 User Manual titled "Discovery kit with STM32F411VE MCU"
	// This shows schematics for how the STM32F411 microcontroller interfaces with
	// peripherals on the STM32F411 development board.  In figure nine you'll see
	// that various port A, B and D pins are used for audio.

	// Enable AHB port A, B and D
	// Bit 0 = Port A clock
	// Bit 1 = Port B clock
	// Bit 2 = Port C clock
	// Bit 3 = Port D clock
	ACCESS(RCC_AHB1ENR) |= (1 | (1 << 1) | (1 << 2) | (1 << 3));


	///////////////////////////////////////////////////////////////////////////////
	// Note the figure 12 schematic on pg 31 of UM1842.  It shows PD4 is tied to
	// the audio reset.

	// Set pin D4 to output (pg 156)
	ACCESS(GPIOD_MODER) &= ~((1 << 9) | (1 << 8));
	ACCESS(GPIOD_MODER) |= (1 << 8);

	// Set pin D4 to "fast" speed (pg 157)
	ACCESS(GPIOD_OSPEEDR) &= ~((1 << 9) | (1 << 8));
	ACCESS(GPIOD_OSPEEDR) |= (1 << 9);

	// Set pin D4 to pulldown (pg 158)
	ACCESS(GPIOD_PUPDR) &= ~((1 << 9) | (1 << 8));
	ACCESS(GPIOD_PUPDR) |= (1 << 9);


	///////////////////////////////////////////////////////////////////////////////
	// The CS43L22 DAC uses I2C.  Note the figure 12 schematic on pg 31 of UM1842.
	// It shows PB6 is the I2C SCL (serial clock line) and PB9 is the SDA (serial
	// data line).  In the following lines we configure these pins as such.

	// Set pins B6 and B9 to alternate mode (pg 156)
	ACCESS(GPIOB_MODER) &= ~((1 << 13) | (1 << 12) | (1 << 19) | (1 << 18));
	ACCESS(GPIOB_MODER) |= ((1 << 13) | (1 << 19));

	// Set pins B6 and B9 to "fast" speed (pg 157)
	ACCESS(GPIOB_OSPEEDR) &= ~((1 << 13) | (1 << 12) | (1 << 19) | (1 << 18));
	ACCESS(GPIOB_OSPEEDR) |= ((1 << 13) | (1 << 19));

	// Set B6 and B9 output type to "open drain" (pg 156)
	ACCESS(GPIOB_OTYPER) |= ((1 << 9) | (1 << 6));

	// Set pin B6 and B9 to pulldown (pg 158)
	ACCESS(GPIOB_PUPDR) &= ~((1 << 13) | (1 << 12) | (1 << 19) | (1 << 18));
	ACCESS(GPIOB_PUPDR) |= ((1 << 13) | (1 << 19));

	// See figure 17 on page 149 for the alternate functions.  I2C is AF4.  The
	// alternate function low register (AFLR) covers pins 0 to 7.  The alternate
	// function high register (AFHR) covers pins 8 to 15.
	ACCESS(GPIOB_AFLR) &= ~(0xF << 24);  // Clear pin 6
	ACCESS(GPIOB_AFLR) |= (0x4 << 24);   // Set pin 6 to 4
	ACCESS(GPIOB_AFLH) &= ~(0xF << 4);   // Clear pin 9
	ACCESS(GPIOB_AFLH) |= (0x4 << 4);    // Set pin 9 to 4


	///////////////////////////////////////////////////////////////////////////////
	// Enable the clocks and PLL for I2S communication to the DAC

	// Enable I2S (SPI3 - bit 15) and I2C clocks (I2C1 - bit21) (pg 117)
	ACCESS(RCC_APB1ENR) |= ((1 << 21) | (1 << 15));

	// Enable the PLL for I2S (pg 101)
	ACCESS(RCC_CR) |= (1 << 26);


	///////////////////////////////////////////////////////////////////////////////
	// Note the figure 9 schematic on pg 28 of UM1842.  Pins A4, C7, C10 and C12
	// are used to communicate with the DAC.  We configure these pins in the
	// following lines of code.

	// Set Port C pins 7, 10 and 12 to alternate function mode (pg 156)
	ACCESS(GPIOC_MODER) &= ~((1 << 25) | (1 << 24) | (1 << 21) | (1 << 20) | (1 << 15) | (1 << 14));
	ACCESS(GPIOC_MODER) |= ((1 << 25) | (1 << 21) | (1 << 15));

	// Set Port C pins 7, 10 and 12 to "fast" speed (pg 157)
	ACCESS(GPIOC_OSPEEDR) &= ~((1 << 25) | (1 << 24) | (1 << 21) | (1 << 20) | (1 << 15) | (1 << 14));
	ACCESS(GPIOC_OSPEEDR) |= ((1 << 25) | (1 << 21) | (1 << 15));

	// Set Port A pin 4 to alternate function mode (pg 156)
	ACCESS(GPIOA_MODER) &= ~((1 << 9) | (1 << 8));
	ACCESS(GPIOA_MODER) |= (1 << 9);

	// Set Port A pin 4 to "fast" speed (pg 157)
	ACCESS(GPIOA_OSPEEDR) &= ~((1 << 9) | (1 << 8));
	ACCESS(GPIOA_OSPEEDR) |= (1 << 9);

	// See figure 17 on page 149 for the alternate functions.  SPI3 is AF6.  The
	// alternate function low register (AFLR) covers pins 0 to 7.  The alternate
	// function high register (AFHR) covers pins 8 to 15.  We set the SPI3
	// alternate function for A4, C7, C10, C12:
	ACCESS(GPIOA_AFLR) &= ~(0xF << 16);  // Clear A4
	ACCESS(GPIOA_AFLR) |= (6 << 16);   // Set A4 to "6"
	ACCESS(GPIOC_AFLR) &= ~(0xF << 28);   // Clear C7
	ACCESS(GPIOC_AFLR) |= (6 << 28);    // Set C7 to "6"
	ACCESS(GPIOC_AFLH) &= ~(0xF << 8);   // Clear C10
	ACCESS(GPIOC_AFLH) |= (6 << 8);    // Set C10 to "6"
	ACCESS(GPIOC_AFLH) &= ~(0xF << 16);   // Clear C12
	ACCESS(GPIOC_AFLH) |= (6 << 16);    // Set C12 to "6"


	///////////////////////////////////////////////////////////////////////////////
	// See table 5 on pg 24 of UM1842.  It shows that PD4 is connected to the
	// reset pin of the CS43L22 DAC chip.  Then on pg 31, section 4.9, of the
	// CS32L22 datasheet it explains to hold the reset high while initializing.

	ACCESS(GPIOD_BSRR) |= (1 << 4);


	///////////////////////////////////////////////////////////////////////////////
	// Reset SPI3 (I2S3) and I2C1 (pg 113)

	ACCESS(RCC_APB1RSTR) |= (1 << 15); // Enable SPI3 reset state
	ACCESS(RCC_APB1RSTR) &= ~(1 << 15); // Release SPI3 from reset state


	ACCESS(RCC_APB1RSTR) |= (1 << 21); // Enable I2C1 reset state
	ACCESS(RCC_APB1RSTR) &= ~(1 << 21); // Release I2C1 from reset state

	///////////////////////////////////////////////////////////////////////////////
	// Configure SPI3 (I2S3)

	// Clear the configuration register settings for I2S3 by zeroing out all bits
	// except for the reserved bits which are bits 12-15 and bit 6. (pg 608)
	// 1111.0000.0100.0000 = 0xF040
	ACCESS_16_BITS(SPI3_I2S3_CFGR) &= 0xF040;

	// Reset the prescaler register using the reset value of 0x0002 (pg 609)
	ACCESS_16_BITS(SPI3_I2S3_I2SPR) = 0x0002;

	// Enable master clock output for I2S3 (pg 610)
	ACCESS_16_BITS(SPI3_I2S3_I2SPR) |= (1 << 9);

	// Set the I2S linear prescaler value to 4 (pg 610)
	ACCESS_16_BITS(SPI3_I2S3_I2SPR) &= ~0xFF;
	ACCESS_16_BITS(SPI3_I2S3_I2SPR) |= 4;

	// Set the I2S mode to "master transmit" (i.e. we're transmitting data from the MCU
	// to the DAC) (pg 608)
	ACCESS_16_BITS(SPI3_I2S3_CFGR) &= ~(3 << 8);
	ACCESS_16_BITS(SPI3_I2S3_CFGR) |= (1 << 9);

	// Set to I2S mode (pg 608)
	ACCESS_16_BITS(SPI3_I2S3_CFGR) |= (1 << 11);


	///////////////////////////////////////////////////////////////////////////////
	// Configure I2C1

	// Enable I2C1 (pg 494)
	ACCESS_16_BITS(I2C1_CR1) |= 0x01;

	// Set the I2C1 clock frequency to 58 MHz (pg 495)
	ACCESS_16_BITS(I2C1_CR2) &= ~(0x3F);  // Clear bits 0-to-5  0x3F = 11.1111
	ACCESS_16_BITS(I2C1_CR2) |= (0x3A);  //  0x3A = 58

	// Disable the I2C1 peripheral while we configure it (pg 494)
	ACCESS_16_BITS(I2C1_CR1) &= ~(0x01);

	// Set the maximum rise time for the SCL feedback loop (pg 503)
	ACCESS_16_BITS(I2C1_TRISE) &= ~(0x3F);  // First clear the bits (0-5)
	ACCESS_16_BITS(I2C1_TRISE) |= 0x01;             // Then set the value

	// Set the clock control value to 0x28 (pg 503)
	ACCESS_16_BITS(I2C1_CCR) &= ~(0xFFF);
	ACCESS_16_BITS(I2C1_CCR) |= 0x28;

	// Enable I2C1 (pg 494)
	ACCESS_16_BITS(I2C1_CR1) |= 0x01;

	// Set the receive acknowledge bit (pg 493)
	ACCESS_16_BITS(I2C1_CR1) |= (1 << 10);
}

void WaitForTransmissionToFinish(uint32_t transmissionBits)
{
	// Using a bitshift (of 16) we combine both of the status registers (SR1 and SR2)
	// of I2C1 so we can easily check them together.
	while(((ACCESS(I2C1_SR1) | (ACCESS(I2C1_SR2) << 16)) & transmissionBits) != transmissionBits);
}

void SendMessageToDAC(uint8_t dacAddress, uint8_t setting)
{
	// Make sure the I2C bus is not busy. Bit 1 of the SR2 register
	// is set if the bus is busy (pg 502)
	while(ACCESS_16_BITS(I2C1_SR2) &= (1 << 1));

	// Starting I2C1 (pg 493)
	ACCESS_16_BITS(I2C1_CR1) |= (1 << 8);

	// Wait until the status shows it's started (pg 500)
	while((ACCESS_16_BITS(I2C1_SR1) &= 0x01) == 0);

	// See figure 12 on pg 31 of the UM1842.  The CS43L22 I2C address is 0x94.
	ACCESS_8_BITS(I2C1_DR) = 0x94;

	// WaitForTransmission puts SR2 in the upper 16 bits of a 32 bit value
	// and SR1 in the lower 16 bits.  So, checking for 0x70082
	// (111.0000.0000.1000.0010) results in checking the following:
	// SR1 Bit 1 = End of address transmission
	// SR1 Bit 7 = Transmission data register empty
	// SR2 Bit 0 = Master mode
	// SR2 Bit 1 = Bus is busy
	// SR2 Bit 2 = Data bytes transmitted
	WaitForTransmissionToFinish(0x70082);

	// Write the address of the DAC register
	ACCESS_8_BITS(I2C1_DR) = dacAddress;

	// WaitForTransmission puts SR2 in the upper 16 bits of a 32 bit value
	// and SR1 in the lower 16 bits.  So, checking for 0x70080
	// (111.0000.0000.1000.0000) results in checking the following:
	// SR1 Bit 7 = Transmission data register empty
	// SR2 Bit 0 = Master mode
	// SR2 Bit 1 = Bus is busy
	// SR2 Bit 2 = Data bytes transmitted
	WaitForTransmissionToFinish(0x70080);

	// Write the setting value into the address
	ACCESS_8_BITS(I2C1_DR) = setting;
	WaitForTransmissionToFinish(0x70080);

	// Bit 2 of SR1 is set when a data byte transfer has succeeded (pg 500)
	while((ACCESS(I2C1_SR1) & (0x1 << 2)) == 0);

	// Setting bit 9 of the CR1 register while in master mode stops I2C transmission (pg 493)
	ACCESS(I2C1_CR1) |= (1 << 9);
}

uint8_t ReadMessageFromDAC(uint8_t mapbyte)
{
	uint8_t receivedByte = 0;

	// Make sure the I2C bus is not busy. Bit 1 of the SR2 register
	// is set if the bus is busy (pg 502)
	while(ACCESS_16_BITS(I2C1_SR2) &= (1 << 1));

	// Starting I2C1 (pg 493)
	ACCESS_16_BITS(I2C1_CR1) |= (1 << 8);

	// Wait until the status shows it's started (pg 500)
	while((ACCESS_16_BITS(I2C1_SR1) &= 0x01) == 0);

	// See figure 12 on pg 31 of the UM1842.  The CS43L22 I2C address is 0x94.
	ACCESS_8_BITS(I2C1_DR) = 0x94;

	WaitForTransmissionToFinish(0x70082);

	// "Sets the transmitter address"
	ACCESS_8_BITS(I2C1_DR) = mapbyte;

	WaitForTransmissionToFinish(0x70080);

	// Setting bit 9 of the CR1 register while in master mode stops I2C transmission (pg 493)
	ACCESS_16_BITS(I2C1_CR1) |= (1 << 9);

	// Make sure the I2C bus is not busy. (pg 502)
	while(ACCESS_16_BITS(I2C1_SR2) &= (1 << 1));

	// Disable acknowledgment that a byte is received (pg 493)
	ACCESS_16_BITS(I2C1_CR1) &= (uint16_t)~((uint16_t)(1 << 10));

	// Starting I2C1 (see pg 493)
	ACCESS_16_BITS(I2C1_CR1) |= (1 << 8);

	// Wait until the status shows it's started (pg 500)
	while((ACCESS_16_BITS(I2C1_SR1) &= 0x01) == 0);

	// The CS43L22 I2C address is 0x94.  We have to set bit 0 to specify a read from the address.
	ACCESS_8_BITS(I2C1_DR) = (0x94 + 0x01);

	// WaitForTransmission puts SR2 in the upper 16 bits of a 32 bit value
	// and SR1 in the lower 16 bits.  So, checking for 0x30020
	// (11.0000.0000.0000.0010) results in checking the following:
	// SR1 Bit 1 = End of address transmission
	// SR2 Bit 0 = Master mode
	// SR2 Bit 1 = Bus is busy
	// "Wait until end of transmission"
	WaitForTransmissionToFinish(0x30002);

	// WaitForTransmission puts SR2 in the upper 16 bits of a 32 bit value
	// and SR1 in the lower 16 bits.  So, checking for 0x30040
	// (11.0000.0000.0000.0010) results in checking the following:
	// SR1 Bit 2 = Data byte transer succedded
	// SR2 Bit 0 = Master mode
	// SR2 Bit 1 = Bus is busy
	// "Wait until byte arrived"
	WaitForTransmissionToFinish(0x30040);

	// Read the byte from the data register
	receivedByte = ACCESS_8_BITS(I2C1_DR);

	// Setting bit 9 of the CR1 register while in master mode stops I2C transmission (pg 493)
	ACCESS_16_BITS(I2C1_CR1) |= (1 << 9);

	return receivedByte;
}

void InitializeDAC()
{
	///////////////////////////////////////////////////////////////////////////////////
	// For the following, see section 4.11 "Required Initialization Settings"  in the
	// CS43L22 datasheet for the five initialization steps, I quote these in comments
	// below:

	// 1) Write 0x99 to register 0x00.
	SendMessageToDAC(0x00, 0x99);

	// 2) Write 0x80 to register 0x47.
	SendMessageToDAC(0x47, 0x80);

	// 3) Write ‘1’b to bit 7 in register 0x32.
	SendMessageToDAC(0x32, (ReadMessageFromDAC(0x32) | 0x80));

	// 4) Write ‘0’b to bit 7 in register 0x32.
	SendMessageToDAC(0x32, (ReadMessageFromDAC(0x32) & (~0x80)));

	// 5) Write 0x00 to register 0x00.
	SendMessageToDAC(0x00, 0x00);


	///////////////////////////////////////////////////////////////////////////////////
	// Then various configuration

	// See pg 38 of the CS32L22 datasheet.  We turn the speaker off and the headphone
	// jack on (0xAF = 1010.1111)
	SendMessageToDAC(0x04, 0xAF);

	// See pg 43.  Set ganged volume control (bit 4) and set the gain multiplier to
	// 1.0.  This results in a value of 0x70 = 1101.0000.
	SendMessageToDAC(0x0D, 0xD0);

	// See pg 38.  Auto detect speed and use MCLK DIV2 (0x81 = 1000.0001)
	SendMessageToDAC(0x05, 0x81);

	// See pg 40.  Set audio word length to 16 bit I2S (1011 = 0x7)
	SendMessageToDAC(0x06, 0x07);
}

void StartAudioPlayback()
{
	// See pg 37 of the CS43L22 datasheet.  Power up the CS43L22.
	SendMessageToDAC(0x02, 0x9E);

	// See pg 608 of RM0383. Enable the I2S peripheral.
	ACCESS(SPI3_I2S3_CFGR) |= (1 << 10);
}

