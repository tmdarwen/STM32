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

#define PWR_BASE_ADDRESS     0x40007000
#define PWR_CR               PWR_BASE_ADDRESS + 0x00  // PWR power control register

#define RCC_BASE_ADDRESS     0x40023800
#define RCC_CR               RCC_BASE_ADDRESS + 0x00  // RCC clock control register
#define RCC_PLLCFGR          RCC_BASE_ADDRESS + 0x04  // RCC PLL configuration register
#define RCC_CFGR             RCC_BASE_ADDRESS + 0x08  // RCC clock configuration register
#define RCC_AHB1ENR          RCC_BASE_ADDRESS + 0x30  // RCC AHB1 peripheral clock enable register (pg 116)
#define RCC_APB1ENR          RCC_BASE_ADDRESS + 0x40  // RCC APB1 peripheral clock enable register (pg 117)

#define GPIOD_BASE_ADDRESS   0x40020C00
#define GPIOD_MODER          GPIOD_BASE_ADDRESS + 0x00 // GPIO port mode register
#define GPIOD_OSPEEDR        GPIOD_BASE_ADDRESS + 0x08 // GPIO port output speed register
#define GPIOD_ODR            GPIOD_BASE_ADDRESS + 0x14 // GPIO port output data register

#define FLASH_BASE_ADDRESS   0x40023C00
#define FLASH_ACR            FLASH_BASE_ADDRESS + 0x00  // Flash access control register (pg 58)

#define ACCESS(address)      *((volatile unsigned int*)(address))

int main(void)
{
	ACCESS(FLASH_ACR) |= (1 << 9);  // Enable instruction cache
	ACCESS(FLASH_ACR) |= (1 << 10); // Enable data cache
	ACCESS(FLASH_ACR) |= (1 << 8);  // Enable prefetch

	// The following comment comes from generated code when using Cube MX to 
	// configure with the highest clock speed for the STM32F411 (100 MHz):
	// "Increasing the number of wait states because of higher CPU frequency.
	//  To correctly read data from FLASH memory, the number of wait states (LATENCY)
	//  must be correctly programmed according to the frequency of the CPU clock
	//  (HCLK) and the supply voltage of the device".
	ACCESS(FLASH_ACR) &= ~0xF;
	ACCESS(FLASH_ACR) |= 0x3;

	ACCESS(RCC_APB1ENR) |= (1 << 28);  // Enable power to the clock 

 	// See pg 85 of the datasheet: We set scale 1 mode since we're setting speed to 100 MHz
	ACCESS(PWR_CR) |= (0x3 << 14);

	ACCESS(RCC_PLLCFGR) &= ~0x3F;         // Clear PLLM
	ACCESS(RCC_PLLCFGR) |= 8;             // ...then set it to 8.

	ACCESS(RCC_PLLCFGR) &= ~(0x1FF << 6); // Clear PLLN
	ACCESS(RCC_PLLCFGR) |= (200 << 6);    // ...then set it to 200.

	ACCESS(RCC_PLLCFGR) &= ~(3 << 16);    // Clear PLLP
	ACCESS(RCC_PLLCFGR) |= (1 << 16);     // ...then set it to 4.

	ACCESS(RCC_PLLCFGR) &= ~(1 << 22);    // Set the HSI as the source

	ACCESS(RCC_PLLCFGR) &= ~(3 << 24);    // Clear PLLQ
	ACCESS(RCC_PLLCFGR) |= (8 << 24);     // ...then set it to 8.

	ACCESS(RCC_CR) |= (1 << 24);              // Turn the PLL on...
	while((ACCESS(RCC_CR) & (1 << 25)) == 0); // ...Wait until the PLL is on.

	ACCESS(RCC_CFGR) &= ~(0xF << 4); // Set the AHB prescaler to zero (no divider)

	ACCESS(RCC_CFGR) |= 0x2;                   // Use the PLL as the system clock
	while((ACCESS(RCC_CFGR) & (1 << 3)) == 0); // Wait until the PLL is used as the system clock

	ACCESS(RCC_CFGR) |= (0x4 << 10); // Set the APB Low speed prescaler (APB1) to 2

	ACCESS(RCC_AHB1ENR) |= (1 << 3); // Give a clock to port D

	ACCESS(GPIOD_MODER) |= (1 << 20); // Set GPIO pins to output

	ACCESS(GPIOD_OSPEEDR) |= (0x3 << 20); // Set GPIO D10 pin to high speed output

	while(1)
	{
		// Toggle a pin.  I then use a logic analyzer to view the speed at which it changes (i.e. frequency)
		ACCESS(GPIOD_ODR) ^= (1 << 10);
	}
}
