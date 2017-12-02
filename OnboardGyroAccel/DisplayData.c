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

#include "StringUtilities.h"
#include "UART.h"
#include "Accelerometer.h"
#include "Gyro.h"

void DisplayHeader()
{
	SendString("    Accel   Gyro\r\n");
}

void DisplayIntegerValue(short value)
{
	// Convert the number to string
	char valueAsString[12];
	IntegerToString(value, valueAsString, BASE_10);

	// Right justify display the string
	short strlen = 0;
	while(valueAsString[strlen])
	{
		strlen++;
	}

	while(strlen < 7)
	{
		SendString(" ");
		++strlen;
	}

	SendString(valueAsString);
}

void DisplayAxisValue(char* label, short accel, short gyro)
{
	SendString(label);
	SendString(":");
	DisplayIntegerValue(accel); 
	DisplayIntegerValue(gyro); 
}

void DisplayAxisValues()
{
	short accelX, accelY, accelZ;
	GetAccelerometerValues(&accelX, &accelY, &accelZ);

	short gyroX, gyroY, gyroZ;
	GetGyroValues(&gyroX, &gyroY, &gyroZ);

	DisplayAxisValue("X", accelX, gyroX);
	SendString("\r\n");
	DisplayAxisValue("Y", accelY, gyroY);
	SendString("\r\n");
	DisplayAxisValue("Z", accelZ, gyroZ);

	SendString("\033[2A");  // Makes cursor got up to lines
	SendString("\r");       // Return cursor to the beginning of the line
}
