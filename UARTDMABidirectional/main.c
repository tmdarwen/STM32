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

#define RCC_BASE_ADDRESS            0x40023800
#define RCC_AHB1ENR                 RCC_BASE_ADDRESS + 0x30  // RCC AHB1 peripheral clock enable register (pg 116)
#define RCC_APB1ENR                 RCC_BASE_ADDRESS + 0x40  // RCC APB1 peripheral clock enable register (pg 117)

#define GPIOA_BASE_ADDRESS          0x40020000
#define GPIOA_MODER                 GPIOA_BASE_ADDRESS + 0x00 // GPIO port mode register
#define GPIOA_OSPEEDR               GPIOA_BASE_ADDRESS + 0x08 // GPIO port output speed register
#define GPIOA_PUPR                  GPIOA_BASE_ADDRESS + 0x0C // GPIO port pull-up/pull-down register
#define GPIOA_ODR                   GPIOA_BASE_ADDRESS + 0x14 // GPIO port output data register
#define GPIOA_AFRL                  GPIOA_BASE_ADDRESS + 0x20 // GPIO alternate function low register

#define USART2_BASE_ADDRESS         0x40004400
#define USART2_SR                   USART2_BASE_ADDRESS + 0x00 // Status register
#define USART2_DR                   USART2_BASE_ADDRESS + 0x04 // Data register
#define USART2_BRR                  USART2_BASE_ADDRESS + 0x08 // Baud rate register
#define USART2_CR1                  USART2_BASE_ADDRESS + 0x0C // Control register 1
#define USART2_CR3                  USART2_BASE_ADDRESS + 0x14 // Control register 3

#define DMA1_BASE_ADDRESS           0x40026000
#define DMA1_HISR                   DMA1_BASE_ADDRESS + 0x04 // DMA high interrupt status register
#define DMA1_HIFCR                  DMA1_BASE_ADDRESS + 0x0C // DMA high interrupt flag clear register
#define DMA1_S5CR                   DMA1_BASE_ADDRESS + (0x10 + (5 * 0x18)) // DMA stream 5 configuration register
#define DMA1_S5NDTR                 DMA1_BASE_ADDRESS + (0x14 + (5 * 0x18)) // DMA stream 5 number of data register
#define DMA1_S5PAR                  DMA1_BASE_ADDRESS + (0x18 + (5 * 0x18)) // DMA stream 5 peripheral address register
#define DMA1_S5M0AR                 DMA1_BASE_ADDRESS + (0x1C + (5 * 0x18)) // DMA stream 5 memory 0 address register
#define DMA1_S5FCR                  DMA1_BASE_ADDRESS + (0x24 + (5 * 0x24)) // DMA stream 5 FIFO control register
#define DMA1_S6CR                   DMA1_BASE_ADDRESS + (0x10 + (6 * 0x18)) // DMA stream 6 configuration register
#define DMA1_S6NDTR                 DMA1_BASE_ADDRESS + (0x14 + (6 * 0x18)) // DMA stream 6 number of data register
#define DMA1_S6PAR                  DMA1_BASE_ADDRESS + (0x18 + (6 * 0x18)) // DMA stream 6 peripheral address register
#define DMA1_S6M0AR                 DMA1_BASE_ADDRESS + (0x1C + (6 * 0x18)) // DMA stream 6 memory 0 address register
#define DMA1_S6FCR                  DMA1_BASE_ADDRESS + (0x24 + (6 * 0x24)) // DMA stream 6 FIFO control register

#define NVIC_BASE_ADDRESS           0xE000E100  // See pg 218 of PM2014
#define NVIC_ISER0                  NVIC_BASE_ADDRESS + 0x00  // "Interrupt set-enable registers" See pg 209 of PM2014
#define NVIC_ISER1                  NVIC_BASE_ADDRESS + 0x04  // "Interrupt set-enable registers" See pg 209 of PM2014

#define ACCESS(address)             *((volatile unsigned int*)(address))

unsigned char dmaDataBuffer;

// DMA1 Stream5 will be triggered for UART2 DMA RX (i.e. when receiving a character from the terminal)
void DMA1_Stream5_IRQHandler(void)
{
	// See pg 187.  Bit 11 is the "Stream 5 transfer complete interrupt flag".  This bit
	// will be set when the DMA reception is complete.
	if((ACCESS(DMA1_HISR) & (1 << 11)) != 0)
	{
		// Clear the transfer complete interrupt (pg 188)
		ACCESS(DMA1_HIFCR) |= (1 << 11);

		// Enable the DMA transfer stream. (pg 192)
		ACCESS(DMA1_S6CR) |= 1;
	}
}

// DMA1 Stream6 will be triggered for UART2 DMA TX (i.e when sending a character to the terminal)
void DMA1_Stream6_IRQHandler(void)
{
	// See pg 187.  Bit 21 is the "Stream 6 transfer complete interrupt flag".  This bit
	// will be set when the DMA transfer is complete.
	if((ACCESS(DMA1_HISR) & (1 << 21)) != 0)
	{
		// Clear the transfer complete interrupt (pg 188)
		ACCESS(DMA1_HIFCR) |= (1 << 21);

		// Enable the DMA reception stream (pg 192)
		ACCESS(DMA1_S5CR) |= 1;
	}
}

void UartGpioInit()
{
	// Give a clock to port A as we'll be using one of its pins for transfer of data (pg 117)
	ACCESS(RCC_AHB1ENR) |= 1;

	// See pg 19 of the ST UM1842 document.  We'll be using USART2.  USART2 TX occurs on
	// PA2 and USART2 RX occurs on PA3 so we set these pins to alternate mode.
	ACCESS(GPIOA_MODER) |= ((1 << 5) | (1 << 7));

	// See pg 149 of ST RM0383 document.  USART2 is AF7.  And pg 160 of the same document
	// shows the alternate function for pin 2 is set using alternate function low register
	// bits 8-thru-11, and pin 3 is set using through bits 12-thru-15.
	ACCESS(GPIOA_AFRL) |= ((7 << 8) | (7 << 12));

	// Set PA2 and PA3 to high speed (pg 157)
	ACCESS(GPIOA_OSPEEDR) |= ((3 << 4) | (3 << 6));
}

void UartDmaInit()
{
	// Enable a clock for DMA1 (pg 116)
	ACCESS(RCC_AHB1ENR) |= (1 << 21);

	// Here we configure the DMA stream.  Page 189 has details of the register and page 168 shows
	// the channel/stream information.  Channel4/Stream5 is responsible for RX (i.e. getting a
	// keypress from the terminal) and Channel4/Stream6 is responsible for TX (i.e. sending the
	// character to the terminal).  We set the following bits:
	// Bit 6-7: 00 = Peripheral-to-memory   01 = Memory-to-peripheral
	// Bit 25-27: Channel selection (channel 4)
	ACCESS(DMA1_S5CR) |= ((1 << 27));
	ACCESS(DMA1_S6CR) |= ((1 << 6) | (1 << 27));

	// Enable interrupts for DMA1_Stream5 and DMA1_Stream6.  See page 209 of ST's PM2014 document
	// for info on this register and pg 202 of RM0383 for the position in the NVIC for these
	// interrupts.
	ACCESS(NVIC_ISER0) |= ((1 << 16) | (1 << 17));

	// The DMAx_SyNDTR register holds the number of data items to transfer (pg 192).  We're doing
	// one character at a time.  Note that bits 11-12 of the DMA configuration register (pg 190)
	// allows us to configure how large each "data item" is (8, 16 or 32 bits).  Since we're doing
	// 8 bit characters, and this corresponds to a setting of "00", we don't need to set this.
	ACCESS(DMA1_S5NDTR) = 1;
	ACCESS(DMA1_S6NDTR) = 1;

	// See pg 193.  This register holds the peripheral data register.  Since we're using USART2
	// we set it to its data register.
	ACCESS(DMA1_S5PAR) = USART2_DR;
	ACCESS(DMA1_S6PAR) = USART2_DR;

	// See pg 193.  This register holds the memory address of the data we want to transfer.  Since
	// we transfer only one character at a time the "buffer" only needs to be one character in size.
	// Also, since the data received is the data we then want to immediately transfer, we just use
	// the same buffer for both receiving and transfer.
	ACCESS(DMA1_S5M0AR) = (unsigned int)(&dmaDataBuffer);
	ACCESS(DMA1_S6M0AR) = (unsigned int)(&dmaDataBuffer);

	// Enable an interrupt to occur when the DMA operations complete (pg 192)
	ACCESS(DMA1_S5CR) |= (1 << 4);
	ACCESS(DMA1_S6CR) |= (1 << 4);

	// Enable the DMA reception stream (pg 192)
	ACCESS(DMA1_S5CR) |= 1;
}

void UartInit()
{
	// Give a clock to USART2 (pg 117)
	ACCESS(RCC_APB1ENR) |= (1 << 17);

	// Here we set the baud rate.  This is explained on page 519 of ST RM0383.  The peripheral
	// clock is 16 MHz by default.  So, the calculation for the USARTDIV is:
	// DesiredBaudRate = 16MHz / (16 * USARTDIV)
	// Note that the fractional part of USARTDIV is represented with only 4 bits.  So
	// if we use 9600 this will result in a small error of 0.02% (see pg 522).  Therefore
	// the baud rate is actually 9,598.  See pages 519-to-522 it explains this well.
	ACCESS(USART2_BRR) |= 0x683;

	// Enable USART2 for transmitting data.  See page 552.
	// Bit 2 = Receiver enabled
	// Bit 3 = Transmitter enabled
	// Bit 13 = Enable the UART
	ACCESS(USART2_CR1) |= ((1 << 2) | (1 << 3) | (1 << 13));

	// Enable UART2 DMA for receiving/transferring data
	ACCESS(USART2_CR3) |= ((1 << 6) | (1 << 7));
}

int main(void)
{
	UartGpioInit();
	UartDmaInit();
	UartInit();

	while(1);
}
