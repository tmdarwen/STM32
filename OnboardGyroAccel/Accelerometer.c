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

// See page 21 of the LSM303DLHC datasheet for more info about these values
#define ACCELEROMETER_READ  0x33
#define ACCELEROMETER_WRITE 0x32

void I2CStartRestart()
{
	// See page 493 of ST's RM0383.  We're in master mode, this will start/restart
	// I2C communication.
	ACCESS(I2C1_CR1) |= (1 << 8);
}

void I2CStop()
{
	// See page 493 of ST's RM0383.  We're in master mode, so setting this bit will
	// "stop generation after the current byte transfer or after the current Start
	// condition is sent".
	ACCESS(I2C1_CR1) |= (1 << 9);
}

void I2CEnableAcknowledge()
{
	// See page 493 of ST's RM0383.  Setting this bit will "acknowledge returned
	// after a byte is received".  The accelerometer will acknowledge when a byte
	// is received.
	ACCESS(I2C1_CR1) |= (1 << 10);
}

void I2CDisableAcknowledge()
{
	// See page 493 of ST's RM0383.  We turn acknowledge off here.
	ACCESS(I2C1_CR1) &= ~(1 << 10);
}

void I2CSendSlaveAddress(unsigned short address)
{
	// See page 500.  We wait for the start bit to be generated.
	while((ACCESS(I2C1_SR1) & 1) == 0);

	// Write the address into the I2C data register.
	ACCESS(I2C1_DR) = address;

	// See page 500.  Wait until the end of transmission.
	while((ACCESS(I2C1_SR1) & (1 << 1)) == 0);

	// See page 500 of the datasheet, under bit 1 ADDR: "This bit is cleared by software
	// reading SR1 register followed reading SR2"
	ACCESS(I2C1_SR1);
	ACCESS(I2C1_SR2);
}

void I2CSendRegister(unsigned short registerAddress)
{
	// See page 499. We wait until the Tx data register is empty.
	while((ACCESS(I2C1_SR1) & (1 << 7)) == 0);

	// Put the register address into the data register
	ACCESS(I2C1_DR) = registerAddress;

	// Wait until the transfer is complete.
	while((ACCESS(I2C1_SR1) & (1 << 7)) == 0);
}

void I2CWaitIfBusy()
{
	// See page 502 of the datasheet.  Bit 1 of SR2 will be set when the I2C bus is busy.
	while((ACCESS(I2C1_SR2) & (1 << 1)) == (1 << 1));
}

void I2CWriteByte(unsigned char data)
{
	// Write the data to the data register
	ACCESS(I2C1_DR) = data;

	// See page 500 of the datasheet.  Bit 2 will be set when the data transfer has succeeded.
	while((ACCESS(I2C1_SR1) & (1 << 2)) == 0);
}

unsigned char I2CGetData()
{
	// See page 499 of the datasheet.  Bit 6 of SR1 will be set when receiver data exist the
	// data register.
	while((ACCESS(I2C1_SR1) & (1 << 6)) == 0) { }

	// Return the data
	return ACCESS(I2C1_DR);
}

unsigned char ReadFromAccelerometer(unsigned short registerAddress)
{
	I2CWaitIfBusy();

	I2CEnableAcknowledge();

	I2CStartRestart();

	// This address of the device we want to read from
	I2CSendSlaveAddress(ACCELEROMETER_WRITE);

	// The address of the register we want to read from
	I2CSendRegister(registerAddress);

	I2CStartRestart();

	// Request a read from the accelerometer
	I2CSendSlaveAddress(ACCELEROMETER_READ);

	I2CDisableAcknowledge();

	I2CStop();

	return I2CGetData();
}

void WriteToAccelerometer(unsigned short registerAddress, unsigned char data)
{
	I2CWaitIfBusy();

	I2CStartRestart();

	// This address of the device we want to write to
	I2CSendSlaveAddress(ACCELEROMETER_WRITE);

	// The address of the register we want to write to
	I2CSendRegister(registerAddress);

	// The data we want to write
	I2CWriteByte(data);

	I2CStop();
}

// See page 33 of UM1842.  It shows the LSM303DLHC (the accelerometer) is connected to the STM32F411 using
// the following pins for I2C communication:
// SCL  --> PB6
// SDA  --> PB9
void AccelerometerInit()
{
	// Give a clock to port B as pins PB6 and PB9 are connected to the accelerometer (pg 33 of UM1842) and
	// page 116 of RM0383 for the RCC AHB register info.
	ACCESS(RCC_AHB1ENR) |= (1 << 1);

	// See page 156 of the datasheet.  We configure PB6 and PB9 to alternate function.
	ACCESS(GPIOB_MODER) |= ((1 << 13) | (1 << 19));

	// See pages 21 and 22 of the ST UM1842 document.  It shows the LSM303DLHC uses I2C1.  Then, looking at
	// page 149 of ST RM0383 shows I2C1 is alternate function 4.  Then looking at pages 160 and 161 shows
	// which bits to set of the AFRL and AFRH registers: Pin 6 = bits 24-27 of AFRL and pin 9 = bits 4-7 of
	// AFRH.
	ACCESS(GPIOB_AFRL) |= (4 << 24);
	ACCESS(GPIOB_AFRH) |= (4 << 4);

	// Set the pins to fast speed.  See pg 157 for more info on the register.  Pin 6 corresponds to
	// bits 12/13, 9=18/19.
	ACCESS(GPIOB_OSPEEDR) |= ((2 << 12) | (2 << 18));

	// See page 117.  We give a clock to I2C1 by setting bit 21 of the RCC APB1 peripheral clock enable register.
	ACCESS(RCC_APB1ENR) |= (1 << 21);

	// See page 495 of the datasheet for info on CR2 peripheral clock frequency.  We set the clock to 2 MHz.
	ACCESS(I2C1_CR2) &= ~(0x3F);
	ACCESS(I2C1_CR2) |= (0x02);

	// So, breaking and inspecting the RCC registers, I see we have the following clock values:
	//    PLLM = 16
	//    PLLN = 192
	//    PLLP = 2
	//    AHB Prescaler = 1
	//    APB1 Prescaler = 1
	//    APB2 Prescaler = 1
	// ...using STM32CubeMX with these values shows a clock speed of 16 MHz.
	// See page 503 of the datasheet for info on the CCR (clock control register).  We're just using Sm mode.
	// Note the example:
	//    "For instance: in Sm mode, to generate a 100 kHz SCL frequency:
	//     If FREQR = 08, TPCLK1 = 125 ns so CCR must be programmed with 0x28
	//     (0x28 <=> 40d x 125 ns = 5000 ns.)"
	// So, 125 ns = 8 MHz clock.  We have a 16 MHz clock, so if I just substitute in 62.5 for 125 we can
	// compensate by doubling 40d to 80d which = 0x50.
	ACCESS(I2C1_CCR) &= ~(0xFFF);
	ACCESS(I2C1_CCR) |= 0x50;

	// See page 503 for info on the TRISE (rise time) register.  It shows the following example:
	//    "In Sm mode, the maximum allowed SCL rise time is 1000 ns.  If, in the I2C_CR2 register, the
	//     value of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns therefore the TRISE[5:0] bits
	//     must be programmed with 09h. (1000 ns / 125 ns = 8 + 1)"
	// We have FREQ set to 0x02.  So this should give us:
	// 1000 ns / 500 ns = 2 + 1
	// So we should be able to set this to 3.
	ACCESS(I2C1_TRISE) &= ~(0x3F);
	ACCESS(I2C1_TRISE) |= 0x03;

	// See page 496 for info on OAR1 (I2C Own address register 1).  We set the following:
	//   Bit 1-7: Interface Address: 100001 = 0x21
	//   Bit 14: b/c the datasheet says "bit 14 Should always be kept at 1 by software"
	// Note that we're using 7 bit addressing mode so we leave bit 15 as zero
	ACCESS(I2C1_OAR1) |= ((0x21 << 1) | (1 << 14));

	// Enable I2C1.  See page 494 of the datasheet.
	ACCESS(I2C1_CR1) |= 1;

	// The device on the STM32F411E-DISCO board is apparently the LSM303DLHC, this has its
	// own datasheet if you go search for it.  But there is also a LSM303D and it has its own
	// datasheet as well which shows a register (0xF) not documented in the LSM303DLHC.  This
	// register is labeled as WHO_AM_I and returns an 8 bit constant.  Looking through various
	// STM32 code I found that this also exists for the LSM303DLHC and returns a constant of
	// 0x33.  So that's what I'm checking here.  It's good to do as a sanity check just to make
	// sure everything is working ok and we can communicate with the accelerometer.
	unsigned char accelerometerID = ReadFromAccelerometer(0xF);
	if(accelerometerID != 0x33)
	{
		// Acceloremeter is not what we expect it to be
	}

	// See page 25 of the LSM303DLHC datasheet.  Register 0x20 is CTRL_REG1_A.  We set this
	// register to 0x47 (0100.0111) to configure the accelerometer as follows:
	// 1) Normal / low-power mode (50 Hz)
	// 2) Enable X, Y and Z axes
	WriteToAccelerometer(0x20, 0x47);
}

void GetAccelerometerValues(short* x, short* y, short* z)
{
	*x = ((ReadFromAccelerometer(0x29) << 8) | ReadFromAccelerometer(0x28));
	*y = ((ReadFromAccelerometer(0x2B) << 8) | ReadFromAccelerometer(0x2A));
	*z = ((ReadFromAccelerometer(0x2D) << 8) | ReadFromAccelerometer(0x2C));
}
