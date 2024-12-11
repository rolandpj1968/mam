#include <stdio.h>

#include "all.h"

int main() {
	printf("\n%d ALU ops\n\n", NAOp);
	for (int op = 0; op < NAOp; op++) {
		printf("    %4d 0x%02x %3s %10s\n", op, op, UNITS[aoptab[op].o.unit], aoptab[op].o.name);
	}
}
