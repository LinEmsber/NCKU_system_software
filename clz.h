#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define WORDBITS 32

int cno_32(unsigned int x);

/* count number ones 32bit */
int cno_32(unsigned int x)
{
	x -= ((x >> 1) & 0x55555555);
	x = (((x >> 2) & 0x33333333) + (x & 0x33333333));
	x = (((x >> 4) + x) & 0x0f0f0f0f);
	x += (x >> 8);
	x += (x >> 16);

	return(x & 0x0000003f);
}

unsigned int clz_ones( unsigned int x)
{
	x |= (x >> 1);
	x |= (x >> 2);
	x |= (x >> 4);
	x |= (x >> 8);
	x |= (x >> 16);

	return(WORDBITS - cno_32(x));
}



int clz_0 (int32_t input)
{
	int sample = ( input < 0 ) ? 0 : input;
	int leadingZeros = ( input < 0 ) ? 0 : 32;

	while(sample) {
		sample >>= 1;
		--leadingZeros;
	}

	return leadingZeros;
}

int clz_debruijn32(uint32_t x)
{
	static const char debruijn32[32] = {
		0, 31, 9, 30, 3, 8, 13, 29, 2, 5, 7, 21, 12, 24, 28, 19,
		1, 10, 4, 14, 6, 22, 25, 20, 11, 15, 23, 26, 16, 27, 17, 18
	};
	x |= x>>1;
	x |= x>>2;
	x |= x>>4;
	x |= x>>8;
	x |= x>>16;
	x++;
	return debruijn32[x*0x076be629>>27];

}

