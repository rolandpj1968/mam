#include "all.h"

int main() {
	printf("\n%d ALU ops\n\n", NAOp);
	for (int op = 0; op < NAOp; op++) {
		if ((op&0x7) == 0)
			printf("--------\n");
		assert((aoptab[op].ta0 == vxxt) == (aoptab[op].na == 0));
		assert((aoptab[op].ta1 == vxxt) == (aoptab[op].na <= 1));
		assert((aoptab[op].tr == vxxt) == (aoptab[op].nr == 0));
		assert(aoptab[op].na <= 2);
		assert(aoptab[op].nr <= 1);
		printf("    %4d 0x%02x %3s %10s    (%s) <- (%s, %s)\n", op, op, UNITS[aoptab[op].o.unit], aoptab[op].o.name, TYPES[aoptab[op].tr], TYPES[aoptab[op].ta0], TYPES[aoptab[op].ta1]);
	}
}
