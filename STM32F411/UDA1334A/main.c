#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_i2s.h"
#include "stm32f4xx_hal_rcc_ex.h"

void SystemClockConfig();
void AudioClockConfig();
void ErrorHandler();
void InitLEDs();
void InitLED(uint16_t pin);
void InitAudioOutput();

I2S_HandleTypeDef hAudioOutI2s;

void NMI_Handler(void)
{
    ErrorHandler();
}

void HardFault_Handler(void)
{
    ErrorHandler();
}

void MemManage_Handler(void)
{
    ErrorHandler();
}

void BusFault_Handler(void)
{
    ErrorHandler();
}

void UsageFault_Handler(void)
{
    ErrorHandler();
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
  HAL_IncTick();
}
void DMA1_Stream7_IRQHandler(void)
{
  HAL_DMA_IRQHandler(hAudioOutI2s.hdmatx);
}

void I2S2_IRQHandler(void)
{
  // Do nothing
}

#define SINE_TABLE_SIZE             256

uint16_t SINE_TABLE[SINE_TABLE_SIZE] = {

   0x0000, 0x0324, 0x0647, 0x096a, 0x0c8b, 0x0fab, 0x12c8, 0x15e2,
   0x18f8, 0x1c0b, 0x1f19, 0x2223, 0x2528, 0x2826, 0x2b1f, 0x2e11,
   0x30fb, 0x33de, 0x36ba, 0x398c, 0x3c56, 0x3f17, 0x41ce, 0x447a,
   0x471c, 0x49b4, 0x4c3f, 0x4ebf, 0x5133, 0x539b, 0x55f5, 0x5842,
   0x5a82, 0x5cb4, 0x5ed7, 0x60ec, 0x62f2, 0x64e8, 0x66cf, 0x68a6,
   0x6a6d, 0x6c24, 0x6dca, 0x6f5f, 0x70e2, 0x7255, 0x73b5, 0x7504,
   0x7641, 0x776c, 0x7884, 0x798a, 0x7a7d, 0x7b5d, 0x7c29, 0x7ce3,
   0x7d8a, 0x7e1d, 0x7e9d, 0x7f09, 0x7f62, 0x7fa7, 0x7fd8, 0x7ff6,
   0x7fff, 0x7ff6, 0x7fd8, 0x7fa7, 0x7f62, 0x7f09, 0x7e9d, 0x7e1d,
   0x7d8a, 0x7ce3, 0x7c29, 0x7b5d, 0x7a7d, 0x798a, 0x7884, 0x776c,
   0x7641, 0x7504, 0x73b5, 0x7255, 0x70e2, 0x6f5f, 0x6dca, 0x6c24,
   0x6a6d, 0x68a6, 0x66cf, 0x64e8, 0x62f2, 0x60ec, 0x5ed7, 0x5cb4,
   0x5a82, 0x5842, 0x55f5, 0x539b, 0x5133, 0x4ebf, 0x4c3f, 0x49b4,
   0x471c, 0x447a, 0x41ce, 0x3f17, 0x3c56, 0x398c, 0x36ba, 0x33de,
   0x30fb, 0x2e11, 0x2b1f, 0x2826, 0x2528, 0x2223, 0x1f19, 0x1c0b,
   0x18f8, 0x15e2, 0x12c8, 0x0fab, 0x0c8b, 0x096a, 0x0647, 0x0324,
   0x0000, 0xfcdc, 0xf9b9, 0xf696, 0xf375, 0xf055, 0xed38, 0xea1e,
   0xe708, 0xe3f5, 0xe0e7, 0xdddd, 0xdad8, 0xd7da, 0xd4e1, 0xd1ef,
   0xcf05, 0xcc22, 0xc946, 0xc674, 0xc3aa, 0xc0e9, 0xbe32, 0xbb86,
   0xb8e4, 0xb64c, 0xb3c1, 0xb141, 0xaecd, 0xac65, 0xaa0b, 0xa7be,
   0xa57e, 0xa34c, 0xa129, 0x9f14, 0x9d0e, 0x9b18, 0x9931, 0x975a,
   0x9593, 0x93dc, 0x9236, 0x90a1, 0x8f1e, 0x8dab, 0x8c4b, 0x8afc,
   0x89bf, 0x8894, 0x877c, 0x8676, 0x8583, 0x84a3, 0x83d7, 0x831d,
   0x8276, 0x81e3, 0x8163, 0x80f7, 0x809e, 0x8059, 0x8028, 0x800a,
   0x8000, 0x800a, 0x8028, 0x8059, 0x809e, 0x80f7, 0x8163, 0x81e3,
   0x8276, 0x831d, 0x83d7, 0x84a3, 0x8583, 0x8676, 0x877c, 0x8894,
   0x89bf, 0x8afc, 0x8c4b, 0x8dab, 0x8f1e, 0x90a1, 0x9236, 0x93dc,
   0x9593, 0x975a, 0x9931, 0x9b18, 0x9d0e, 0x9f14, 0xa129, 0xa34c,
   0xa57e, 0xa7be, 0xaa0b, 0xac65, 0xaecd, 0xb141, 0xb3c1, 0xb64c,
   0xb8e4, 0xbb86, 0xbe32, 0xc0e9, 0xc3aa, 0xc674, 0xc946, 0xcc22,
   0xcf05, 0xd1ef, 0xd4e1, 0xd7da, 0xdad8, 0xdddd, 0xe0e7, 0xe3f5,
   0xe708, 0xea1e, 0xed38, 0xf055, 0xf375, 0xf696, 0xf9b9, 0xfcdc,
};

void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
{
    HAL_I2S_Transmit_DMA(&hAudioOutI2s, SINE_TABLE, SINE_TABLE_SIZE);
}

int main(void)
{
    HAL_Init();

    InitLEDs();

    SystemClockConfig();

    AudioClockConfig();

    InitAudioOutput();

    while(1);

    return 0;
}

void InitLEDs()
{
	// Use the red and green LEDs
    InitLED(GPIO_PIN_12);
    InitLED(GPIO_PIN_13);

    // Turn on green LED to indicate everything is okay
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
}

void InitLED(uint16_t pin)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    __HAL_RCC_GPIOD_CLK_ENABLE();

    // Configure the GPIO_LED pin
    GPIO_InitStruct.Pin = pin; //
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOD, pin, GPIO_PIN_RESET);
}

void ErrorHandler()
{
    // Turn off the green LED
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);

    // Turn on the red LED to indicate an error
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);

    while(1);
}

  // System Clock Configuration
  //         The system Clock is configured as follow :
  //            System Clock source            = PLL (HSE)
  //            SYSCLK(Hz)                     = 84000000
  //            HCLK(Hz)                       = 84000000
  //            AHB Prescaler                  = 1
  //            APB1 Prescaler                 = 2
  //            APB2 Prescaler                 = 1
  //            HSE Frequency(Hz)              = 8000000
  //            PLL_M                          = 8
  //            PLL_N                          = 336
  //            PLL_P                          = 4
  //            PLL_Q                          = 7
  //            VDD(V)                         = 3.3
  //            Main regulator output voltage  = Scale2 mode
  //            Flash Latency(WS)              = 2
void SystemClockConfig()
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;

    // Enable Power Control clock
    __HAL_RCC_PWR_CLK_ENABLE();

    // The voltage scaling allows optimizing the power consumption when the device is
    // clocked below the maximum system frequency, to update the voltage scaling value
    // regarding system frequency refer to product datasheet.
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

    // Enable HSE Oscillator and activate PLL with HSE as source
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        ErrorHandler();
    }

    // Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
    // clocks dividers
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        ErrorHandler();
    }
}

void AudioClockConfig()
{
    RCC_PeriphCLKInitTypeDef rccclkinit;

    // Enable PLLI2S clock
    HAL_RCCEx_GetPeriphCLKConfig(&rccclkinit);

    // I2S clock config
    // PLLI2S_VCO = f(VCO clock) = f(PLLI2S clock input) × (PLLI2SN/PLLM)
    // I2SCLK = f(PLLI2S clock output) = f(VCO clock) / PLLI2SR
    rccclkinit.PeriphClockSelection = RCC_PERIPHCLK_I2S;
    rccclkinit.PLLI2S.PLLI2SM = 8;
    rccclkinit.PLLI2S.PLLI2SN = 271;
    rccclkinit.PLLI2S.PLLI2SR = 6;
    if(HAL_RCCEx_PeriphCLKConfig(&rccclkinit) != HAL_OK)
    {
        ErrorHandler();
    }
}

void InitAudioOutput()
{
    // Enable I2S3 clock
    __HAL_RCC_SPI3_CLK_ENABLE();

    // Enable I2S GPIO clocks
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // I2S3 pins configuration: WS, SCK and SD pins
    static DMA_HandleTypeDef hdma_i2sTx;
    GPIO_InitTypeDef  GPIO_InitStruct;
    GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin         = GPIO_PIN_4 ;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // I2S3 pins configuration: MCK pin
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitStruct.Pin = GPIO_PIN_7;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    // Enable the I2S DMA clock
    __HAL_RCC_DMA1_CLK_ENABLE();

	// Configure the hdma_i2sTx handle parameters
	hdma_i2sTx.Init.Channel = DMA_CHANNEL_0;
	hdma_i2sTx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	hdma_i2sTx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_i2sTx.Init.MemInc = DMA_MINC_ENABLE;
	hdma_i2sTx.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
	hdma_i2sTx.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
	hdma_i2sTx.Init.Mode = DMA_NORMAL;
	hdma_i2sTx.Init.Priority = DMA_PRIORITY_HIGH;
	hdma_i2sTx.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
	hdma_i2sTx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	hdma_i2sTx.Init.MemBurst = DMA_MBURST_SINGLE;
	hdma_i2sTx.Init.PeriphBurst = DMA_PBURST_SINGLE;

	hdma_i2sTx.Instance = DMA1_Stream7;

    // Associate the DMA handle
    __HAL_LINKDMA(&hAudioOutI2s, hdmatx, hdma_i2sTx);

    // Deinitialize the Stream for new transfer
    HAL_DMA_DeInit(&hdma_i2sTx);

    // Configure the DMA Stream
    HAL_DMA_Init(&hdma_i2sTx);

    // I2S DMA IRQ Channel configuration
    HAL_NVIC_SetPriority(DMA1_Stream7_IRQn, 0x0E, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream7_IRQn);

    // Disable I2S block
    hAudioOutI2s.Instance = SPI3;
    __HAL_I2S_DISABLE(&hAudioOutI2s);

    // I2S3 peripheral configuration
    hAudioOutI2s.Init.AudioFreq = 44100;
    hAudioOutI2s.Init.ClockSource = I2S_CLOCK_PLL;
    hAudioOutI2s.Init.CPOL = I2S_CPOL_LOW;
    hAudioOutI2s.Init.DataFormat = I2S_DATAFORMAT_16B;
    hAudioOutI2s.Init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE;
    hAudioOutI2s.Init.Mode = I2S_MODE_MASTER_TX;
    hAudioOutI2s.Init.Standard = I2S_STANDARD_PHILIPS;

    // Initialize the I2S peripheral with the structure above
    if(HAL_I2S_Init(&hAudioOutI2s) != HAL_OK)
    {
    	ErrorHandler();
    }

    // Send audio output
    HAL_I2S_Transmit_DMA(&hAudioOutI2s, SINE_TABLE, 2 * SINE_TABLE_SIZE);
}
