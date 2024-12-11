#include <stdio.h>

#include "all.h"

int main() {
	printf("\n%d ALU ops\n\n", NAOp);
	for (int op = 0; op < NAOp; op++) {
		if ((op&0x7) == 0)
			printf("--------\n");
		printf("    %4d 0x%02x %3s %10s    (%s) <- (%s, %s)\n", op, op, UNITS[aoptab[op].o.unit], aoptab[op].o.name, TYPES[aoptab[op].tr], TYPES[aoptab[op].ta0], TYPES[aoptab[op].ta1]);
	}
}
