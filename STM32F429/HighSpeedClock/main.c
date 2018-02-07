/*
 * STM32 Projects
 *
 * Copyright (c) 2018 - Terence M. Darwen - tmdarwen.com
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

#define PWR_BASE_ADDRESS            0x40007000
#define PWR_CR                      PWR_BASE_ADDRESS + 0x00  // PWR power control register
#define PWR_CSR                     PWR_BASE_ADDRESS + 0x04  // PWR power control register

#define RCC_BASE_ADDRESS     0x40023800
#define RCC_CR               RCC_BASE_ADDRESS + 0x00  // RCC clock control register
#define RCC_PLLCFGR          RCC_BASE_ADDRESS + 0x04  // RCC PLL configuration register
#define RCC_CFGR             RCC_BASE_ADDRESS + 0x08  // RCC clock configuration register
#define RCC_AHB1ENR          RCC_BASE_ADDRESS + 0x30  // RCC AHB1 peripheral clock enable register (pg 116)
#define RCC_APB1ENR          RCC_BASE_ADDRESS + 0x40  // RCC APB1 peripheral clock enable register (pg 117)

#define GPIOA_BASE_ADDRESS          0x40020000
#define GPIOA_MODER                 GPIOA_BASE_ADDRESS + 0x00 // GPIO port mode register
#define GPIOA_OSPEEDR               GPIOA_BASE_ADDRESS + 0x08 // GPIO port output speed register
#define GPIOA_ODR                   GPIOA_BASE_ADDRESS + 0x14 // GPIO port output data register

#define FLASH_BASE_ADDRESS   0x40023C00
#define FLASH_ACR            FLASH_BASE_ADDRESS + 0x00  // Flash access control register (pg 58)

#define ACCESS(address)      *((volatile unsigned int*)(address))

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

void SetupPinA0()
{
	ACCESS(RCC_AHB1ENR) |= 1; // Give a clock to port A

	ACCESS(GPIOA_MODER) |= 1; // Set GPIO pins to output

	ACCESS(GPIOA_OSPEEDR) |= 0x3; // Set GPIO A0 pin to high speed output
}

int main(void)
{
	ConfigureClockSpeed();

	SetupPinA0();

	while(1)
	{
		ACCESS(GPIOA_ODR) ^= 1; // Toggle the A0 pin
	}
}

