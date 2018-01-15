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

#define GPIOD_BASE_ADDRESS          0x40020C00
#define GPIOD_MODER                 GPIOD_BASE_ADDRESS + 0x00 // GPIO port mode register
#define GPIOD_OSPEEDR               GPIOD_BASE_ADDRESS + 0x08 // GPIO port output speed register
#define GPIOD_ODR                   GPIOD_BASE_ADDRESS + 0x14 // GPIO port output data register

#define USART2_BASE_ADDRESS          0x40004400
#define USART2_SR                    USART2_BASE_ADDRESS + 0x00 // Status register
#define USART2_DR                    USART2_BASE_ADDRESS + 0x04 // Data register
#define USART2_BRR                   USART2_BASE_ADDRESS + 0x08 // Baud rate register
#define USART2_CR1                   USART2_BASE_ADDRESS + 0x0C // Control register 1

#define ACCESS(address)            *((volatile unsigned int*)(address))

void SendString(char* string)
{
	while(*string)
	{
		// See pg 548 of the ST RM0383 document for more info on the USART registers.
		while((ACCESS(USART2_SR) & (1 << 6)) == 0 || (ACCESS(USART2_SR) & (1 << 7)) == 0);  // Wait until transmission is complete
		ACCESS(USART2_DR) &= ~(0xFF); // Clear the data register
		ACCESS(USART2_DR) = *string; // Write the next character
		string++;  // Advance the pointer to the next character
	}
}

char ReadChar()
{
	while((ACCESS(USART2_SR) & (1 << 5)) == 0);  // Block until data is received
	return (ACCESS(USART2_DR) & 0xFF);  // Return the key that was pressed
}

void InitUART()
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

	// Give a clock USART2.  See pg 117.
	ACCESS(RCC_APB1ENR) |= (1 << 17);

	// Here we set the baud rate.  This is explained on 519 of ST RM0383.  The peripheral
	// clock is 16 MHz by default.  So, the calculation for the USARTDIV is:
	// DesiredBaudRate = 16MHz / 16*USARTDIV
	// Note that the fractional part of USARTDIV is represented with only 4 bits.  So
	// if we use 9600 this will result in a small error of 0.02% (see pg 522).  Therefore
	// the baud rate is actually 9,598.  Again, see pg 522.
	ACCESS(USART2_BRR) |= 0x683;

	// Enable USART2 for transmitting and receiving data
	ACCESS(USART2_CR1) |= ((1 << 2) | (1 << 3) | (1 << 13));
}

void InitLEDs()
{
	// Give a clock to port D
	ACCESS(RCC_AHB1ENR) |= (1 << 3);

	// Set GPIO pins to output
	ACCESS(GPIOD_MODER) |= ((1 << 24) | (1 << 26) | (1 << 28) | (1 << 30));

	// Set to high speed
	ACCESS(GPIOD_OSPEEDR) |= ((3 << 24) | (3 << 26) | (3 << 28) | (3 << 30));
}

int main(void)
{
	InitUART();

	InitLEDs();

	while(1)
	{
		SendString("Press key to toggle LED: r=red, g=green, b=blue");
		char keyPress = ReadChar();
		if(keyPress == 'r')
		{
			ACCESS(GPIOD_ODR) ^= (1 << 14);
		}
		else if(keyPress == 'g')
		{
			ACCESS(GPIOD_ODR) ^= (1 << 12);
		}
		else if(keyPress == 'b')
		{
			ACCESS(GPIOD_ODR) ^= (1 << 15);
		}
		SendString("\r\n");
	}
}
