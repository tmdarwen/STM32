STM32 Onboard Audio Output
==========================

This code is based on A.Finkelmeyer's original code posted at [http://www.mind-dump.net/configuring-the-stm32f4-discovery-for-audio](http://www.mind-dump.net/configuring-the-stm32f4-discovery-for-audio). I've heavily modified this code to to directly interact with the registers of the STM32F4 instead of using the Standard Peripheral Library.

The [STM32F411 development board](http://www.st.com/en/microcontrollers/stm32f411.html?querycriteria=productId=LN1877) comes equipped with a [Cirrus Logic CS43L22 DAC](https://www.cirrus.com/products/cs43l22/) audio DAC.

The I2C/I2S data sent from the STM32F411 can also be used on an external DAC.  The STM32F411 pins to use are as follows:
-       Pin A4 = LRCLK
-       Pin C7 = MCLK
-       Pin C10 = SCLK
-       Pin C12 = SDIN

