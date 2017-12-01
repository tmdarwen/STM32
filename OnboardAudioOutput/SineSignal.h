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

// A full cycle of a sine wave consisting of 16 bit PCM audio data

uint16_t SINE_SIGNAL[100] = {
	0x0000, 0x0405, 0x0805, 0x0bfe, 0x0feb, 0x13c7, 0x178f, 0x1b40,
	0x1ed5, 0x224b, 0x259e, 0x28cc, 0x2bd0, 0x2ea7, 0x3150, 0x33c7,
	0x3609, 0x3815, 0x39e9, 0x3b81, 0x3cde, 0x3dfd, 0x3ede, 0x3f7f,
	0x3fe0, 0x4000, 0x3fe0, 0x3f7f, 0x3ede, 0x3dfd, 0x3cde, 0x3b81,
	0x39e9, 0x3815, 0x3609, 0x33c7, 0x3150, 0x2ea7, 0x2bd0, 0x28cc,
	0x259e, 0x224b, 0x1ed5, 0x1b40, 0x178f, 0x13c7, 0x0feb, 0x0bfe,
	0x0805, 0x0405, 0x0000, 0xfbfc, 0xf7fc, 0xf403, 0xf016, 0xec3a,
	0xe872, 0xe4c1, 0xe12c, 0xddb6, 0xda63, 0xd735, 0xd431, 0xd15a,
	0xceb1, 0xcc3a, 0xc9f8, 0xc7ec, 0xc618, 0xc480, 0xc323, 0xc204,
	0xc123, 0xc082, 0xc021, 0xc001, 0xc021, 0xc082, 0xc123, 0xc204,
	0xc323, 0xc480, 0xc618, 0xc7ec, 0xc9f8, 0xcc3a, 0xceb1, 0xd15a,
	0xd431, 0xd735, 0xda63, 0xddb6, 0xe12c, 0xe4c1, 0xe872, 0xec3a,
	0xf016, 0xf403, 0xf7fc, 0xfbfc
};
