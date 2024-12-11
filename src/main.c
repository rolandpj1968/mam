#include "all.h"

static void add0to7(Mam *mam) {
	mamtick(mam, (u8[4]){AOlit0,   AOlit2,   AOlit4,   AOlit6});
	mamtick(mam, (u8[4]){AOlit1,   AOlit3,   AOlit5,   AOlit7});
	mamtick(mam, (u8[4]){AOiadd32, AOiadd32, AOiadd32, AOiadd32});
	mamtick(mam, (u8[4]){AOtos1,   AOnop,    AOtos3,   AOnop});
	mamtick(mam, (u8[4]){AOiadd32, AOnop,    AOiadd32, AOnop});
	mamtick(mam, (u8[4]){AOtos2,   AOnop,    AOnop,    AOnop});
	mamtick(mam, (u8[4]){AOiadd32, AOnop,    AOnop,    AOnop});

	printf("\n\nsum{0..7} = %lu\n\n", mamalutos(mam, 0));
}

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
	mam.dbg = 1;
	//checkmam(&mam);
	add0to7(&mam);
}
