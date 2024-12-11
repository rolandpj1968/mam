#include "all.h"

static void checkmam(Mam *mam) {
	for (int op = 0; op < NAOp;) {
		u8 ao[4] = {op, op, op, op};
		if ((op&0x7) == 0)
			printf("--------\n");
		assert((aoptab[op].ta0 == vxxt) == (aoptab[op].na == 0));
		assert((aoptab[op].ta1 == vxxt) == (aoptab[op].na <= 1));
		assert((aoptab[op].tr == vxxt) == (aoptab[op].nr == 0));
		assert(aoptab[op].na <= 2);
		assert(aoptab[op].nr <= 1);
		/* assert(alu.err == AluNoErr); */
		mamtick(mam, ao);
		if (!mam->trap) {
			printf("    clk %3lu: %4d 0x%02x %3s %10s    (%s) <- (%s, %s)\n", mam->clk, op, op, UNITS[aoptab[op].o.unit], aoptab[op].o.name, TYPES[aoptab[op].tr], TYPES[aoptab[op].ta0], TYPES[aoptab[op].ta1]);
			op++;
		} else {
			printf("    clk %3lu: trap cycle\n", mam->clk);
		}
		/* if (alu.err == AluNoErr) { */
		/* 	printf(" ... ok\n"); */
		/* } else { */
		/* 	printf(" ... err %s, resetting\n", ALUERRS[alu.err]); */
		/* 	alu.err = AluNoErr; */
		/* } */
	}	
	printf("\nDone!\n");
}

int main() {
	Mam mam = {0};
	checkmam(&mam);
}
