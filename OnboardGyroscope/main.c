#include "UART.h"
#include "Gyro.h"

#define DELAY_LENGTH  100000

void Delay();

int main()
{
	UartInit();

	GyroInit();

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
