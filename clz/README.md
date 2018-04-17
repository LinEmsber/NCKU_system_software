# Count Leading Zero

## Introduction
Why need to calculate the count leading zeros (CLZ) ?

Because if we need to calculate log number on base 2, we only need to count leading zeros and subtract it by 32.

```c
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
```

##

## References:
 - [B04: clz](https://hackmd.io/s/ry1u0uDFg)
 - [重新理解數值](https://hackmd.io/s/Hy-pTh8Fl)
 - [CLZ(counting leading zeros)](https://www.youtube.com/watch?v=DRkXFjLfaVg)
