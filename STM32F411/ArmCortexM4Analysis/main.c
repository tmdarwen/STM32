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

#define RCC_BASE_ADDRESS            0x40023800
#define RCC_AHB1ENR                 RCC_BASE_ADDRESS + 0x30  // RCC AHB1 peripheral clock enable register (pg 116)

#define GPIOD_BASE_ADDRESS          0x40020C00
#define GPIOD_MODER                 GPIOD_BASE_ADDRESS + 0x00 // GPIO port mode register
#define GPIOD_OSPEEDR               GPIOD_BASE_ADDRESS + 0x08 // GPIO port output speed register
#define GPIOD_ODR                   GPIOD_BASE_ADDRESS + 0x14 // GPIO port output data register

#define SYSTICK_BASE_ADDRESS        0xE000E000
#define SYSTICK_CTRL                SYSTICK_BASE_ADDRESS + 0x10 // SysTick control and status register (pg 246 of DM00046982)
#define SYSTICK_LOAD                SYSTICK_BASE_ADDRESS + 0x14 // SysTick reload value register (pg 247 of DM00046982)
#define SYSTICK_VAL                 SYSTICK_BASE_ADDRESS + 0x18 // SysTick current value register (pg 248 of DM00046982)

#define ACCESS(address)            *((volatile unsigned int*)(address))

const unsigned int LED1  = (1 << 12);
const unsigned int LED2  = (1 << 13);
const unsigned int LED3  = (1 << 14);
const unsigned int LED4  = (1 << 15);

unsigned int lightsOn = 0;
unsigned int interruptCount = 0;
unsigned int uninitializedArray[10];
unsigned int initializedArray[10] = {1,2,3,4,5,6,7,8,9,10};

// This function is called when the systick interrupt occurs
void SysTick_Handler()
{
	ACCESS(GPIOD_ODR) ^= lightsOn;

	++interruptCount;

	// Simply using the arrays so they don't get optimized out
	uninitializedArray[0] = interruptCount;
	initializedArray[0] = interruptCount;
}

void Init(int led1, int led2)
{
	// Set given LEDs
	lightsOn = led1 | led2;

	// Give a clock to port D
	ACCESS(RCC_AHB1ENR) |= (1 << 3);

	// Set GPIO pins to output
	ACCESS(GPIOD_MODER) |= ((1 << 24) | (1 << 26) | (1 << 28) | (1 << 30));

	// Set to high speed
	ACCESS(GPIOD_OSPEEDR) |= ((3 << 24) | (3 << 26) | (3 << 28) | (3 << 30));

	// Set the systick interrupt timer to it's max value to create max delay
	ACCESS(SYSTICK_LOAD) |= 0xFFFFFF;

	// Set the systick inital value to zero
	ACCESS(SYSTICK_VAL) &= ~(0xFFFFFF);

	// Set the systick clock source to the processsor clock, enable the interrupt 
	// request and activate the systick timer.
	ACCESS(SYSTICK_CTRL) |= ((1 << 2) | (1 << 1) | 1);
}

int main()
{
	unsigned int ledOn1 = LED1;
	unsigned int ledOn2 = LED3;

	Init(ledOn1, ledOn2);
	while(1);
}
