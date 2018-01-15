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

#define MAX_BUFFER_SIZE 2000
unsigned char dmaBuffer[MAX_BUFFER_SIZE];

volatile int uartBusy = 0;

void DMA1_Stream6_IRQHandler(void)
{
	// See pg 187.  Bit 21 is the "Stream 6 transfer complete interrupt flag".  This bit
	// will be set when the DMA transfer is complete.
	if((ACCESS(DMA1_HISR) & (1 << 21)) != 0)
	{
		// See pg 188.  Here we clear the transfer complete interrupt.
		ACCESS(DMA1_HIFCR) |= (1 << 21);

		// See pg 552.  Here we specify that we want an interrupt generated once the
		// USART transmission is complete.
		ACCESS(USART2_CR1) |= (1 << 6);
	}
}

void USART2_IRQHandler(void)
{
	// See pg 549.  Bit 6 of the status register will be set when the UART
	// transmission has completed.
	if((ACCESS(USART2_SR) & (1 << 6)) != 0)
	{
		// Clear the interrupt. (...So that it doesn't continually trigger)
		ACCESS(USART2_CR1) &= ~(1 << 6);

		// Clear the busy flag to allow the next transmission.
		uartBusy = 0;
	}
}

void UartGpioInit()
{
	// Give a clock to port A as we'll be using one of its pins for transfer of data.
	ACCESS(RCC_AHB1ENR) |= 1;

	// See pg 19 of the ST UM1842 document.  We'll be using USART2.  USART2 TX occurs on
	// PA2 and USART2 RX occurs on PA3 so we set this pin to alternate mode.
	ACCESS(GPIOA_MODER) |= ((1 << 5) | (1 << 7));

	// See pg 149 of ST RM0383 document.  USART2 is AF7.  And pg 160 of the same document
	// shows alternate function for pins 2 and 3 are set using alternate function low register
	// bits 8-thru-11.
	ACCESS(GPIOA_AFRL) |= ((7 << 8) | (7 << 12));

	// Set PA2 and PA3 to high speed
	ACCESS(GPIOA_OSPEEDR) |= ((3 << 4) | (3 << 6));
}

void UartDmaInit()
{
	// Enable a clock for DMA1
	ACCESS(RCC_AHB1ENR) |= (1 << 21);

	// See pg 189 for details of the DMA stream configuration register
	// Setting bit 6 specifies memory-to-peripheral communication.
	// Setting bit 10 specifies to increment the memory pointer after each data transfer.  This
	// allows the DMA device to progressively step through the dmaBuffer array.
	// Setting bit 27 specifies to use channel 4 of stream 6.
	ACCESS(DMA1_S6CR) |= ((1 << 6) | (1 << 10) | (1 << 27));

	// Enable interrupt for DMA1_Stream6
	ACCESS(NVIC_ISER0) |= (1 << 17);
}

void UartInit()
{
	UartGpioInit();

	UartDmaInit();

	// Give a clock USART2.  See pg 117.
	ACCESS(RCC_APB1ENR) |= (1 << 17);

	// Here we set the baud rate.  This is explained on 519 of ST RM0383.  The peripheral
	// clock is 16 MHz by default.  So, the calculation for the USARTDIV is:
	// DesiredBaudRate = 16MHz / 16*USARTDIV
	// Note that the fractional part of USARTDIV is represented with only 4 bits.  So
	// if we use 9600 this will result in a small error of 0.02% (see pg 522).  Therefore
	// the baud rate is actually 9,598.  Again, see pg 522.
	ACCESS(USART2_BRR) |= 0x683;

	// Enable USART2 for transmitting data.
	ACCESS(USART2_CR1) |= ((1 << 3) | (1 << 13));

	// See pg 200 of RM0383 ("STM32F411xC/E Reference Manual") for the interrupt
	// vector table.  You'll see TIM3 is interrupt 29.
	// See pg 209 of PM0214 ("STM32F4 Series Programming Manual") for info on "ISER"
	// which is one of the "interrupt set-enable registers".  We enable interrupt
	// number 29.
	ACCESS(NVIC_ISER1) |= (1 << (38 - 32));
}

void SendString(char* string)
{
	// Here we block until the previous transfer completes.
	while(uartBusy == 1);
	uartBusy = 1;

	// Copy the string into the DMA buffer and also calculate its length.
	int lengthOfString = 0;
	while(lengthOfString < MAX_BUFFER_SIZE && string[lengthOfString])
	{
		dmaBuffer[lengthOfString] = string[lengthOfString];
		++lengthOfString;
	}

	// See pg 192.  This register holds the number of data items to transfer.
	ACCESS(DMA1_S6NDTR) = lengthOfString;

	// See pg 193.  This register holds the peripheral data register.  Since we're
	// using USART2 we set it to its data register.
	ACCESS(DMA1_S6PAR) = USART2_DR;

	// See pg 193.  This register holds the memory address of the data we want to transfer.
	ACCESS(DMA1_S6M0AR) = (unsigned int)dmaBuffer;

	// Enable interrupt to occur upon completion of transfer
	ACCESS(DMA1_S6CR) |= (1 << 4);

	// Enable the stream
	ACCESS(DMA1_S6CR) |= 1;

	// Clear the transfer complete flag in the UART SR
	ACCESS(USART2_SR) &= ~(1 << 6);

	// Enable DMA transmission
	ACCESS(USART2_CR3) |= (1 << 7);
}
