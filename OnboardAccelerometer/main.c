#include "UART.h"
#include "Accelerometer.h"

#define DELAY_LENGTH  100000

void Delay();

int main()
{
	UartInit();

	AccelerometerInit();

	while(1)
	{
		DisplayAxisValues();
		Delay();
	}

	return 0;
}

void Delay()
{
	for(volatile int i = 0; i < DELAY_LENGTH; ++i);
}
