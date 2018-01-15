STM32 Gyroscope / Accelerometer
===============================

The [STM32F411 development board](http://www.st.com/en/microcontrollers/stm32f411.html?querycriteria=productId=LN1877) comes equipped with an accelerometer and gyroscope on-board.  In this example I show how to communiacte with these devices in realtime, displaying output to a terminal program like [PuTTY](http://www.putty.org/).  The code is well documented explaining what every non-obvious line of code does.  In order to best understand how the software communicates with the hardware I don't use the HAL of Standard Peripheral Library.

 

**Hardware Prerequisites**

1.   An [STMF32F411](http://www.st.com/en/microcontrollers/stm32f411.html?querycriteria=productId=LN1877) development board.  Currently they can be ordered from the usual sites for around $15 USD plus shipping.
1.   A USB to TTL Serial Cable like [this one from AdaFruit](https://www.adafruit.com/product/954).

 

**Video Demo**

[![STM32 Gyroscope and Accelerometer Demonstration](https://img.youtube.com/vi/488qheY73ic/0.jpg)](https://www.youtube.com/watch?v=488qheY73ic)
