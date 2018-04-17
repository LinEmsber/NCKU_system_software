#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "clz.h"

int main(int argc, char *argv[])
{
	int n = atoi(argv[1]);

	printf("__builtin_clz(n): %d\n", __builtin_clz(n));
	printf("clz_debruijn32(n): %d\n", clz_debruijn32(n));
	printf("clz_0(n): %d\n", clz_0(n));
	printf("clz_ones(n): %d\n", clz_ones(n));

	return 0;
}
