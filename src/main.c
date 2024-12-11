#include "all.h"

static void checkalu() {
	Mam mam;
	Alu alu = {0};

	for (int op = 0; op < NAOp; op++) {
		if ((op&0x7) == 0)
			printf("--------\n");
		assert((aoptab[op].ta0 == vxxt) == (aoptab[op].na == 0));
		assert((aoptab[op].ta1 == vxxt) == (aoptab[op].na <= 1));
		assert((aoptab[op].tr == vxxt) == (aoptab[op].nr == 0));
		assert(aoptab[op].na <= 2);
		assert(aoptab[op].nr <= 1);
		printf("    %4d 0x%02x %3s %10s    (%s) <- (%s, %s)", op, op, UNITS[aoptab[op].o.unit], aoptab[op].o.name, TYPES[aoptab[op].tr], TYPES[aoptab[op].ta0], TYPES[aoptab[op].ta1]);
		fflush(stdout);
		assert(alu.err == AluNoErr);
		aluexe0(&mam, &alu, op);
		if (alu.err == AluNoErr) {
			printf(" ... ok\n");
		} else {
			printf(" ... err %s, resetting\n", ALUERRS[alu.err]);
			alu.err = AluNoErr;
		}
	}	
	printf("\nDone!\n");
}

int main() {
	checkalu();
}
