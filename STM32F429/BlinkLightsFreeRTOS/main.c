/**
  ******************************************************************************
  * @file    FreeRTOS/FreeRTOS_ThreadCreation/Src/main.c
  * @author  MCD Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright © 2017 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"

#define RCC_BASE_ADDRESS            0x40023800
#define RCC_AHB1ENR                 RCC_BASE_ADDRESS + 0x30  // RCC AHB1 peripheral clock enable (datasheet pg 242)

#define GPIOG_BASE_ADDRESS          0x40021800  // See page 65 of the datasheet
#define GPIOG_MODER                 GPIOG_BASE_ADDRESS + 0x00 // GPIO port mode register
#define GPIOG_OSPEEDR               GPIOG_BASE_ADDRESS + 0x08 // GPIO port output speed register
#define GPIOG_PUPDR                 GPIOG_BASE_ADDRESS + 0x0C // GPIO port pull-up/pull-down register
#define GPIOG_ODR                   GPIOG_BASE_ADDRESS + 0x14 // GPIO port pull-up/pull-down register

#define ACCESS(address)            *((volatile unsigned int*)(address))

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TaskHandle_t LEDThread1Handle, LEDThread2Handle;

// The SysTick interrupt handler is used by FreeRTOS. xPortSysTickHandler() is 
// defined in FreeRTOS code.  Just making a forward decl here to avoid compilation 
// warning.
void xPortSysTickHandler(void);
void SysTick_Handler(void)
{
  xPortSysTickHandler();
}

// A definition for SystemCoreClock is necessary for FreeRTOS.  See FreeRTOSConfig.h.
uint32_t SystemCoreClock = 16000000;

/* Private function prototypes -----------------------------------------------*/
static void LED_Thread1(void const *argument);
static void LED_Thread2(void const *argument);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* Configure LED3 and LED4 */
  ACCESS(RCC_AHB1ENR) |= (1 << 6);

  ACCESS(GPIOG_MODER) |= (1 << 26);
  ACCESS(GPIOG_OSPEEDR) |= (2 << 26);
  ACCESS(GPIOG_PUPDR) |= (1 << 26);

  ACCESS(GPIOG_MODER) |= (1 << 28);
  ACCESS(GPIOG_OSPEEDR) |= (2 << 28);
  ACCESS(GPIOG_PUPDR) |= (1 << 28);

  /* Start thread 1 */
  xTaskCreate((TaskFunction_t)LED_Thread1, "LED3", 128, 0x0, 0, &LEDThread1Handle);
  
  /* Start thread 2 */
  xTaskCreate((TaskFunction_t)LED_Thread2, "LED4", 128, 0x0, 0, &LEDThread2Handle);
  
  /* Start scheduler */
  vTaskStartScheduler();

  /* We should never get here as control is now taken by the scheduler */
  for(;;);
}

/**
  * @brief  Toggle LED3 and LED4 thread
  * @param  thread not used
  * @retval None
  */
static void LED_Thread1(void const *argument)
{
  uint32_t count = 0;
  (void) argument;
  
  for(;;)
  {
    count = xTaskGetTickCount() + 5000;
    
    /* Toggle LED3 every 200 ms for 5 s */
    while (count >= xTaskGetTickCount())
    {
      ACCESS(GPIOG_ODR) ^= (1 << 13);
      
      vTaskDelay(200);
    }
    
    /* Turn off LED3 */
    ACCESS(GPIOG_ODR) &= ~(1 << 13);
    
    /* Suspend Thread 1 */
    vTaskSuspend(NULL);
    
    count = xTaskGetTickCount() + 5000;
    
    /* Toggle LED3 every 400 ms for 5 s */
    while (count >= xTaskGetTickCount())
    {
      ACCESS(GPIOG_ODR) ^= (1 << 14);
      
      vTaskDelay(400);
    }
    
    /* Resume Thread 2 */
    vTaskResume(LEDThread2Handle);
  }
}

/**
  * @brief  Toggle LED4 thread
  * @param  argument not used
  * @retval None
  */
static void LED_Thread2(void const *argument)
{
  uint32_t count;
  (void) argument;
  
  for(;;)
  {
    count = xTaskGetTickCount() + 10000;
    
    /* Toggle LED4 every 500 ms for 10 s */
    while (count >= xTaskGetTickCount())
    {
      ACCESS(GPIOG_ODR) ^= (1 << 14);

      vTaskDelay(500);
    }
    
    /* Turn off LED4 */
    ACCESS(GPIOG_ODR) &= ~(1 << 14);
    
    /* Resume Thread 1 */
    vTaskResume(LEDThread1Handle);
    
    /* Suspend Thread 2 */
    vTaskSuspend(NULL);  
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
