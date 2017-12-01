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

// Register addresses for the STM32F411 chip

#define PWR_BASE_ADDRESS            0x40007000
#define PWR_CR                      PWR_BASE_ADDRESS + 0x00

#define RCC_BASE_ADDRESS            0x40023800
#define RCC_CR                      RCC_BASE_ADDRESS + 0x00
#define RCC_PLLCFGR                 RCC_BASE_ADDRESS + 0x04
#define RCC_CFGR                    RCC_BASE_ADDRESS + 0x08
#define RCC_CIR                     RCC_BASE_ADDRESS + 0x0C
#define RCC_APB1RSTR                RCC_BASE_ADDRESS + 0x20  // RCC APB1 peripheral reset register for (pg 112)
#define RCC_AHB1ENR                 RCC_BASE_ADDRESS + 0x30  // RCC AHB1 peripheral clock enable register (pg 116)
#define RCC_APB1ENR                 RCC_BASE_ADDRESS + 0x40
#define RCC_PLLI2SCFGR              RCC_BASE_ADDRESS + 0x84  // RCC PLLI2S configuration register (pg 132)

#define GPIOA_BASE_ADDRESS          0x40020000
#define GPIOA_MODER                 GPIOA_BASE_ADDRESS + 0x00 // GPIO port mode register
#define GPIOA_OTYPER                GPIOA_BASE_ADDRESS + 0x04 // GPIO port output type register
#define GPIOA_OSPEEDR               GPIOA_BASE_ADDRESS + 0x08 // GPIO port output speed register
#define GPIOA_PUPDR                 GPIOA_BASE_ADDRESS + 0x0C // GPIO port pull-up/pull-down register
#define GPIOA_BSRR                  GPIOA_BASE_ADDRESS + 0x18 // GPIO port bit set/reset register
#define GPIOA_AFLR                  GPIOA_BASE_ADDRESS + 0x20 // GPIO alternate function low register
#define GPIOA_AFLH                  GPIOA_BASE_ADDRESS + 0x24 // GPIO alternate function high register

#define GPIOB_BASE_ADDRESS          0x40020400
#define GPIOB_MODER                 GPIOB_BASE_ADDRESS + 0x00 // GPIO port mode register
#define GPIOB_OTYPER                GPIOB_BASE_ADDRESS + 0x04 // GPIO port output type register
#define GPIOB_OSPEEDR               GPIOB_BASE_ADDRESS + 0x08 // GPIO port output speed register
#define GPIOB_PUPDR                 GPIOB_BASE_ADDRESS + 0x0C // GPIO port pull-up/pull-down register
#define GPIOB_BSRR                  GPIOB_BASE_ADDRESS + 0x18 // GPIO port bit set/reset register
#define GPIOB_AFLR                  GPIOB_BASE_ADDRESS + 0x20 // GPIO alternate function low register
#define GPIOB_AFLH                  GPIOB_BASE_ADDRESS + 0x24 // GPIO alternate function high register

#define GPIOC_BASE_ADDRESS          0x40020800
#define GPIOC_MODER                 GPIOC_BASE_ADDRESS + 0x00 // GPIO port mode register
#define GPIOC_OTYPER                GPIOC_BASE_ADDRESS + 0x04 // GPIO port output type register
#define GPIOC_OSPEEDR               GPIOC_BASE_ADDRESS + 0x08 // GPIO port output speed register
#define GPIOC_PUPDR                 GPIOC_BASE_ADDRESS + 0x0C // GPIO port pull-up/pull-down register
#define GPIOC_BSRR                  GPIOC_BASE_ADDRESS + 0x18 // GPIO port bit set/reset register
#define GPIOC_AFLR                  GPIOC_BASE_ADDRESS + 0x20 // GPIO alternate function low register
#define GPIOC_AFLH                  GPIOC_BASE_ADDRESS + 0x24 // GPIO alternate function high register

#define GPIOD_BASE_ADDRESS          0x40020C00
#define GPIOD_MODER                 GPIOD_BASE_ADDRESS + 0x00 // GPIO port mode register
#define GPIOD_OSPEEDR               GPIOD_BASE_ADDRESS + 0x08 // GPIO port output speed register
#define GPIOD_PUPDR                 GPIOD_BASE_ADDRESS + 0x0C // GPIO port pull-up/pull-down register
#define GPIOD_BSRR                  GPIOD_BASE_ADDRESS + 0x18 // GPIO port bit set/reset register

#define SPI3_I2S3_BASE_ADDRESS      0x40003C00
#define SPI3_I2S3_SR                SPI3_I2S3_BASE_ADDRESS + 0x08 // SPI status register (pg 605)
#define SPI3_I2S3_DR                SPI3_I2S3_BASE_ADDRESS + 0x0C // SPI data register (pg 606)
#define SPI3_I2S3_CFGR              SPI3_I2S3_BASE_ADDRESS + 0x1C // SPI_I2S configuration register (pg 608)
#define SPI3_I2S3_I2SPR             SPI3_I2S3_BASE_ADDRESS + 0x20 // SPI_I2S prescaler register (pg 609)

#define I2C1_BASE_ADDRESS           0x40005400
#define I2C1_CR1                    I2C1_BASE_ADDRESS + 0x00 // I2C Control register 1 (pg 492)
#define I2C1_CR2                    I2C1_BASE_ADDRESS + 0x04 // I2C Control register 2 (pg 494)
#define I2C1_OAR1                   I2C1_BASE_ADDRESS + 0x08 // I2C Own address register 1 (pg 496)
#define I2C1_DR                     I2C1_BASE_ADDRESS + 0x10 // I2C Own address register 1 (pg 497)
#define I2C1_SR1                    I2C1_BASE_ADDRESS + 0x14 // I2C Status register 1 (pg 497)
#define I2C1_SR2                    I2C1_BASE_ADDRESS + 0x18 // I2C Status register 2 (pg 501)
#define I2C1_CCR                    I2C1_BASE_ADDRESS + 0x1C // I2C Clock control register (pg 502)
#define I2C1_TRISE                  I2C1_BASE_ADDRESS + 0x20 // I2C TRISE register (pg 503)
