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

#define RCC_BASE_ADDRESS        0x40023800
#define RCC_AHB1ENR             RCC_BASE_ADDRESS + 0x30  // RCC AHB1 peripheral clock enable register (pg 116)
#define RCC_APB1ENR             RCC_BASE_ADDRESS + 0x40  // RCC APB1 peripheral clock enable register (pg 117)

#define GPIOD_BASE_ADDRESS      0x40020C00
#define GPIOD_MODER             GPIOD_BASE_ADDRESS + 0x00 // GPIO port mode register
#define GPIOD_OSPEEDR           GPIOD_BASE_ADDRESS + 0x08 // GPIO port output speed register
#define GPIOD_ODR               GPIOD_BASE_ADDRESS + 0x14 // GPIO port output data register

#define TIM3_BASE_ADDRESS       0x40000400
#define TIM3_CR1                TIM3_BASE_ADDRESS + 0x00
#define TIM3_DIER               TIM3_BASE_ADDRESS + 0x0C
#define TIM3_SR                 TIM3_BASE_ADDRESS + 0x10
#define TIM3_EGR                TIM3_BASE_ADDRESS + 0x14
#define TIM3_PSC                TIM3_BASE_ADDRESS + 0x28
#define TIM3_ARR                TIM3_BASE_ADDRESS + 0x2C

#define NVIC_BASE_ADDRESS       0xE000E100  // See pg 218 of PM2014
#define NVIC_ISER0              NVIC_BASE_ADDRESS + 0x00  // "Interrupt set-enable registers" See pg 209 of PM2014

#define ACCESS(address)         *((volatile unsigned int*)(address))

// This function is called when the systick interrupt occurs
void TIM3_Interrupt_Handler()
{
	// Toggle LEDs
	ACCESS(GPIOD_ODR) ^= ((1 << 12) | (1 << 13) | (1 << 14) | (1 << 15));
	ACCESS(TIM3_SR) &= ~1; // Clear the interrupt flag
}

int main(void)
{
	// Give a clock to port D
	ACCESS(RCC_AHB1ENR) |= (1 << 3);

	// Set GPIO pins to output
	ACCESS(GPIOD_MODER) |= ((1 << 24) | (1 << 26) | (1 << 28) | (1 << 30));

	// Set to high speed
	ACCESS(GPIOD_OSPEEDR) |= ((3 << 24) | (3 << 26) | (3 << 28) | (3 << 30));

	// Enable TIM3 clock.  See pg 119 of RM0383
	ACCESS(RCC_APB1ENR) |= (0x1 << 1);

	// See pg 200 of RM0383 ("STM32F411xC/E Reference Manual") for the interrupt
	// vector table.  You'll see TIM3 is interrupt 29.
	// See pg 209 of PM0214 ("STM32F4 Series Programming Manual") for info on "ISER"
	// which is one of the "interrupt set-enable registers".  We enable interrupt
	// number 29.
	ACCESS(NVIC_ISER0) |= 1 << 29;

	// I believe by default the STM32F411 clock will run at 16 MHz.  The PSC for the
	// timer is a prescaler so I believe it simply is used to divide the 16 MHz clock
	// by 2000 -> 16,000,000/2,000 = 8,000.  Then the ARR (auto-reload value) is the 
	// counter.  Since it counts 2,000 times the interrupt should be called every 
	// ~250 milliseconds.
	ACCESS(TIM3_ARR) = 1999;
	ACCESS(TIM3_PSC) = 1999;

	// See pg 359.  Setting the first bit of this register makes the timer automatically 
	// get reset with the auto-reload value (ARR) after each interrupt.
	ACCESS(TIM3_EGR) = 1;

	// Enable the interrupt. (pg 357)
	ACCESS(TIM3_DIER) |= 0x1;

	// Enable the counter.  (pg 352)
	ACCESS(TIM3_CR1) |= 0x1;

	while(1);
}

