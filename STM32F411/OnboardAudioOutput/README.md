STM32 Onboard Audio Output
==========================

The [STM32F411 development board](http://www.st.com/en/microcontrollers/stm32f411.html?querycriteria=productId=LN1877) comes equipped with a [Cirrus Logic CS43L22 audio DAC](https://www.cirrus.com/products/cs43l22/) that can be used to output reasonably high fidelity stereo audio output from the 1/8th inch adapter on the board.  This example outputs a 16 bit stereo sine wave tone from this onboard DAC.

This code is based on Andreas Finkelmeyer's original code posted at [http://www.mind-dump.net/configuring-the-stm32f4-discovery-for-audio](http://www.mind-dump.net/configuring-the-stm32f4-discovery-for-audio) though I've heavily modified it to directly interact with the registers of the STM32F411 instead of using the Standard Peripheral Library.

The I2C/I2S data sent from the STM32F411 can also be used on an external DAC.  I've successfully done this using my [CS4334 Audio DAC breakout board](https://github.com/tmdarwen/Misc/tree/main/CS4334BreakoutBoard) and a [Digilent PMOD I2S](https://reference.digilentinc.com/reference/pmod/pmodi2s/start). The STM32F411 pins to use to do this are as follows:
* Pin A4 = LRCLK
* Pin C7 = MCLK
* Pin C10 = SCLK
* Pin C12 = SDIN

