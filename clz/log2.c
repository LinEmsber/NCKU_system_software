#include <stdio.h>
#include <stdint.h>

#define LOG2(X) ((unsigned) \
		(8 * sizeof (unsigned long long) - __builtin_clzll((X)) - 1))

uint32_t log_2_uint32(unsigned int x)
{
	unsigned int i, BITS = 31;

	for (i = 0; i < 32; i++) {
	    if (x & 0x80000000) break;
	    x <<= 1;
	}
	printf("count leading zero: %d\n", i);
	return BITS - i;
}


int main()
{
	// printf("%u\n%u\n", LOG2(0x10), LOG2(0.5));
	printf("%u\n", log_2_uint32(0x10));
}
