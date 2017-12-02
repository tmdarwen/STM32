/*
 * STM32 Projects
 *
 * Copyright (c) 2017 - Terence M. Darwen - tmdarwen.com
 *
 * The MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "RegisterAddresses.h"

void WaitForSPI1RXReady()
{
	// See page 605 of the datasheet for info on the SPI status register
	// If Bit0 == 0 then SPI RX is empty
	// If Bit7 == 1 then SPI is busy
	while((ACCESS(SPI1_SR) & 1) == 0 || (ACCESS(SPI1_SR) & (1 << 7)) == 1) { }
}

void WaitForSPI1TXReady()
{
	// See page 605 of the datasheet for info on the SPI status register
	// If Bit1 == 0 then SPI TX buffer is not empty
	// If Bit7 == 1 then SPI is busy
	while((ACCESS(SPI1_SR) & (1 << 1)) == 0 || (ACCESS(SPI1_SR) & (1 << 7)) == 1) { }
}

// See page 25 of the L3GD20 datasheet for details on how we send commands to, and make
// queries of, the gyro.  If you look at figure 14 of UM1842 on page 33 you'll see how
// the L3GD20 pins are connected to the STM32F411:
//    CS  --> PE3   // Chip Select
//    SPC --> PA5   // Clock
//    SDI --> PA7   // Data In
//    SDO --> PA6   // Data Out
// As shown on page 25 of the L3GD20 communication with the gyro takes the following steps:
// 1) The chip select must go from high to low to indicate we're doing a read or write.
// 2) The first byte we send is the register of the gyro (combined with 0x80 if we're going
//    to do a read operation).
// 3) Do a read from SDO
// 4) Write the next byte
// 5) Read a result
// 6) Set CS back to high

unsigned char ReadFromGyro(unsigned char gyroRegister)
{
	ACCESS(GPIOE_BSRR) |= (1 << 19);
	WaitForSPI1TXReady();
	ACCESS(SPI1_DR) = (gyroRegister | 0x80); // 0x80 indicates we're doing a read
	WaitForSPI1RXReady();
	ACCESS(SPI1_DR);  // I believe we need this simply because a read must follow a write
	WaitForSPI1TXReady();
	ACCESS(SPI1_DR) = 0xFF;
	WaitForSPI1RXReady();
	volatile unsigned char readValue = (unsigned char)ACCESS(SPI1_DR);
	ACCESS(GPIOE_BSRR) |= (1 << 3);

	return readValue;
}

void WriteToGyro(unsigned char gyroRegister, unsigned char value)
{
	ACCESS(GPIOE_BSRR) |= (1 << 19);
	WaitForSPI1TXReady();
	ACCESS(SPI1_DR) = gyroRegister;
	WaitForSPI1RXReady();
	ACCESS(SPI1_DR);  // I believe we need this simply because a read must follow a write
	WaitForSPI1TXReady();
	ACCESS(SPI1_DR) = value;
	WaitForSPI1RXReady();
	ACCESS(SPI1_DR);  // Don't care what valley the device put into the data register
	ACCESS(GPIOE_BSRR) |= (1 << 3);
}

void GyroInit()
{
	// Give a clock to port A as pins PA5-thru-PA7 are connected to the gyro (pg 20 of UM1842) and
	// page 116 of RM0383 for the RCC AHB register info.
	ACCESS(RCC_AHB1ENR) |= 1;

	// Give a clock to port E as pin PE3 is connected to the chip select of the gyro (pg 20 of
	// UM1842) and page 116 of RM0383 for the RCC AHB register info.
	ACCESS(RCC_AHB1ENR) |= (1 << 4);

	// See pg 20 of the ST UM1842 document.  We'll be using SPI1 to communicate with the gyro.
	// See pg 149 of RM0383.  It shows SPI1 to be alternate function 5.
	// See pg 156 of RM0383 for documentation on the GPIO mode register.  It shows how to set
	// pins to alternate mode.  We do this for pins PA5, PA6, PA7.
	ACCESS(GPIOA_MODER) |= ((1 << 11) | (1 << 13) | (1 << 15));
	ACCESS(GPIOE_MODER) |= (1 << 6);

	// See pg 149 of ST RM0383 document.  SPI1 is AF5.  And pg 160 of the same document shows
	// alternate function for pin 5 = bits 20-23, pin 6 = bits 24-27, pin 7 = bits 28-31.
	// We set these to 5.
	ACCESS(GPIOA_AFRL) |= ((5 << 20) | (5 << 24) | (5 << 28));

	// Set the pins to fast speed.  See pg 157 for more info on the register.  Pin 5 corresponds to
	// bits 10/11, 6=12/13, and 7=14,15.  And for port E pin 3 corresponds to bits 6/7.
	ACCESS(GPIOA_OSPEEDR) |= ((2 << 10) | (2 << 12) | (2 << 14));
	ACCESS(GPIOE_OSPEEDR) |= (2 << 6);

	// Enable clock for SPI1
	ACCESS(RCC_APB2ENR) |= (1 << 12);

	// See page 602 for details of configuring SPI1 Control Register
	// Set Bit 0: The second clock transition is the first data capture edge
	// Set Bit 1: CK to 1 when idle
	// Set Bit 2: The STM32 is the master, the gyro is the slave
	// Set Bits 3-5 to 010 for a baud rate of fPCLK/8
	// Set Bits 8-9: Software slave management enabled, Internal slave select to 1
	ACCESS(SPI1_CR1) |= (1 | (1 << 1) | (1 << 2) | (2 << 3) | (1 << 8) | (1 << 9));

	// Set Bit 6: Enable SPI.  See page 603.
	ACCESS(SPI1_CR1) |= (1 << 6);

	// Set the CS high on the gyro as setting it low indicates communication.  See
	// 25 of the L3GD20 datasheet and page 159 of RM0383 for more info on BSRR.
	ACCESS(GPIOE_BSRR) |= (1 << 3);

	// See page 31 of the L3GD20 datasheet.  If communication to the gyro is properly
	// setup, reading from register 0x0F will give us b11010100 (0xD4).
	if(ReadFromGyro(0x0F) != 0xD4)
	{
		// Initializing Gyro Device Failed
	}

	// See page 31 of the L3GD20 datasheet.  Writing 0x0F to register 0x20 will power up
	// the gyro and enables the X, Y, Z axes.
	WriteToGyro(0x20, 0x0F);
}

short GetAxisValue(unsigned char lowRegister, unsigned char highRegister)
{
	// See page 9 of L3GD20.  It shows the mechanical characteristics of the gyro.  Note
	// that we leave the sensitivity as is (i.e. 0) so that it's 250 dps.  So, we read
	// the value from the gyro and convert it to a +/- 360 degree value.
	float scaler = 8.75 * 0.001;
	short temp = (ReadFromGyro(lowRegister) | (ReadFromGyro(highRegister) << 8));
	return (short)((float)temp * scaler);
}

void GetGyroValues(short* x, short* y, short* z)
{
	// See page 36 of the L3GD20 datasheet.  It shows the hi/lo addresses of each of the axes.
	*x = GetAxisValue(0x28, 0x29);
	*y = GetAxisValue(0x2A, 0x2B);
	*z = GetAxisValue(0x2C, 0x2D);
}
