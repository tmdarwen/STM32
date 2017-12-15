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

// Note that I refer to two STM documents here:
// 1) UM1842 = User Manual for Discovery kit with STM32F411VE MCU
// 2) RM0383 = Reference Manual for STM32F411xC/E Advanced Arm-based 32-bit MCUs
// You should be able to easily find these documents by searching the interwebs.

#define RCC_BASE_ADDRESS            0x40023800                // See pg 37 of RM0383
#define RCC_AHB1ENR                 RCC_BASE_ADDRESS + 0x30   // RCC AHB1 peripheral clock enable register

#define GPIOA_BASE_ADDRESS          0x40020000                // See pg 37 of RM0383
#define GPIOA_IDR                   GPIOA_BASE_ADDRESS + 0x10 // GPIO port input data register

#define GPIOD_BASE_ADDRESS          0x40020C00                // See pg 37 of RM0383
#define GPIOD_MODER                 GPIOD_BASE_ADDRESS + 0x00 // GPIO port mode register
#define GPIOD_ODR                   GPIOD_BASE_ADDRESS + 0x14 // GPIO port output data register

#define ACCESS(address)            *((volatile unsigned int*)(address))

// See page 33 of UM1842.  The schematic shows the LEDs are connected to pins PD12, PD13, PD14 and PD15.
void ConfigureLEDs()
{
	// Give a clock to port D (for the LEDs).  See pg 116 of RM0383.
	ACCESS(RCC_AHB1ENR) |= (1 << 3);

	// See pg 156 of RM0383.  Set mode of the LED pins to output.
	ACCESS(GPIOD_MODER) |= ((1 << 24) | (1 << 26) | (1 << 28) | (1 << 30));
}

// See page 33 of UM1842.  The schematic shows the user button is connected to PA0.
void ConfigureButton()
{
	// Give a clock to port A (for the button).  See pg 116 of RM0383.
	ACCESS(RCC_AHB1ENR) |= 1;

	// See pg 156 of RM0383.  No need to set MODER since input is zero (same as reset).
}

int main(void)
{
	ConfigureLEDs();
	ConfigureButton();

	while(1)
	{
		// Check if the PA0 bit is set.
		if((ACCESS(GPIOA_IDR) & 0x1) == 0x1)
		{
			// Light up LEDs.
			ACCESS(GPIOD_ODR) = ((1 << 12) | (1 << 13) | (1 << 14) | (1 << 15));
		}
		else
		{
			// Turn off LEDs.
			ACCESS(GPIOD_ODR) &= ~((1 << 12) | (1 << 13) | (1 << 14) | (1 << 15));
		}
	}
}
