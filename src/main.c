#include <stdio.h>

#include "all.h"

int main() {
	printf("\n%d ALU ops\n\n", NAOp);
	for (int op = 0; op < NAOp; op++) {
		if ((op&0x7) == 0)
			printf("--------\n");
		printf("    %4d 0x%02x %3s %10s %3s * %d -> %3s * %d\n", op, op, UNITS[aoptab[op].o.unit], aoptab[op].o.name, TYPES[aoptab[op].ta], aoptab[op].na, TYPES[aoptab[op].tr], aoptab[op].nr);
	}
}
