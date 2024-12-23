#include "all.h"

static void encadd0to7slow(CLine *ic) {
	EncIns ei[7] = {
		{B(AOi8con0, AOi8con1, AOi8con2, AOi8con3), {{1,1,1,1,0,0,0,0}}, {{0,2,4,6,0,0,0,0}}},
		{B(AOi8con4, AOi8con5, AOi8con6, AOi8con7), {{0,0,0,0,1,1,1,1}}, {{0,0,0,0,1,3,5,7}}},
		{B(AOiadd32, AOiadd32, AOiadd32, AOiadd32), {{0}}, {{0}}},
		{B(AOalur1,  AOnop,    AOalur3,  AOnop),    {{0}}, {{0}}},
		{B(AOiadd32, AOnop,    AOiadd32, AOnop),    {{0}}, {{0}}},
		{B(AOalur2,  AOnop,    AOnop,    AOnop),    {{0}}, {{0}}},
		{B(AOiadd32, AOnop,    AOnop,    AOnop),    {{0}}, {{0}}},
	};
	dumpeis(ei, 7);
	printf("\n");
	EncErr err = enceis(ei, 7, ic);
	if (err != EncNoErr) {
		printf("Encoding failed with %s\n\n", ENCERRS[err]);
	}
}

static void runadd0to7slow() {
	Mam mam = {0};
	CLine ic;
	Dram dram = {.wr = 0, .addr = 0, .len = 64, .m = &ic};
	Dram *pdram[1] = {&dram};

	mam.ndram = 1;
	mam.dram = pdram;

	encadd0to7slow(&ic);

	mam.dbg = 1;
	mam.ctl.ip = 0;
	for (u8 i = 0; i < 7; i++) {
		mamtick(&mam);
	}
}

#if 0
static void add0to7slow(Mam *mam) {
	wricu8(&mam->ctl.ic, 0, (u8)4);
	wricu8(&mam->ctl.ic, 1, (u8)5);
	wricu8(&mam->ctl.ic, 2, (u8)6);
	wricu8(&mam->ctl.ic, 3, (u8)7);
	mamexei(mam, I(AOlit0,   AOlit2,   AOi8con0, AOi8con2));
	mamexei(mam, I(AOlit1,   AOlit3,   AOi8con1, AOi8con3));
	mamexei(mam, I(AOiadd32, AOiadd32, AOiadd32, AOiadd32));
	mamexei(mam, I(AOalur1,  AOnop,    AOalur3,  AOnop));
	mamexei(mam, I(AOiadd32, AOnop,    AOiadd32, AOnop));
	mamexei(mam, I(AOalur2,  AOnop,    AOnop,    AOnop));
	mamexei(mam, I(AOiadd32, AOnop,    AOnop,    AOnop));

	printf("\n\nsum{0..7} = %lu\n\n", mamalutos(mam, 0));
}

static void add0to7fast(Mam *mam) {
	wricu8(&mam->ctl.ic, 0, (u8)4);
	wricu8(&mam->ctl.ic, 1, (u8)5);
	wricu8(&mam->ctl.ic, 2, (u8)6);
	wricu8(&mam->ctl.ic, 3, (u8)7);
	mamexei(mam, I(AOlit0,     AOlit2,   AOi8con0,   AOi8con2));
	mamexei(mam, I(AOlit1,     AOlit3,   AOi8con1,   AOi8con3));
	mamexei(mam, I(AOiadd32,   AOiadd32, AOiadd32,   AOiadd32));
	mamexei(mam, I(AOiadd32r1, AOnop,    AOiadd32r3, AOnop));
	mamexei(mam, I(AOiadd32r2, AOnop,    AOnop,      AOnop));

	printf("\n\nsum{0..7} = %lu\n\n", mamalutos(mam, 0));
}

static void addm1tom8slow(Mam *mam) {
	wricu8(&mam->ctl.ic, 1, (u8)-5);
	wricu8(&mam->ctl.ic, 2, (u8)-6);
	wricu8(&mam->ctl.ic, 3, (u8)-7);
	wricu8(&mam->ctl.ic, 0, (u8)-8);
	mamexei(mam, I(AOlitm1,  AOlitm3,  AOi8con0, AOi8con2));
	mamexei(mam, I(AOlitm2,  AOlitm4,  AOi8con1, AOi8con3));
	mamexei(mam, I(AOiadd32, AOiadd32, AOiadd32, AOiadd32));
	mamexei(mam, I(AOalur1,  AOnop,    AOalur3,  AOnop));
	mamexei(mam, I(AOiadd32, AOnop,    AOiadd32, AOnop));
	mamexei(mam, I(AOalur2,  AOnop,    AOnop,    AOnop));
	mamexei(mam, I(AOiadd32, AOnop,    AOnop,    AOnop));

	printf("\n\nsum{-1..-8} = %ld\n\n", mamalutos(mam, 0));
}

static void addm1tom8fast(Mam *mam) {
	wricu8(&mam->ctl.ic, 1, (u8)-5);
	wricu8(&mam->ctl.ic, 2, (u8)-6);
	wricu8(&mam->ctl.ic, 3, (u8)-7);
	wricu8(&mam->ctl.ic, 0, (u8)-8);
	mamexei(mam, I(AOlitm1,    AOlitm3,  AOi8con0,   AOi8con2));
	mamexei(mam, I(AOlitm2,    AOlitm4,  AOi8con1,   AOi8con3));
	mamexei(mam, I(AOiadd32,   AOiadd32, AOiadd32,   AOiadd32));
	mamexei(mam, I(AOiadd32r1, AOnop,    AOiadd32r3, AOnop));
	mamexei(mam, I(AOiadd32r2, AOnop,    AOnop,      AOnop));

	printf("\n\nsum{-1..-8} = %ld\n\n", mamalutos(mam, 0));
}

static void addm1tom8fast16(Mam *mam) {
	wricu16(&mam->ctl.ic, 2, (u16)-5);
	wricu16(&mam->ctl.ic, 4, (u16)-6);
	wricu16(&mam->ctl.ic, 6, (u16)-7);
	wricu16(&mam->ctl.ic, 0, (u16)-8);
	mamexei(mam, I(AOlitm1,    AOlitm3,  AOi16con0,   AOi16con2));
	mamexei(mam, I(AOlitm2,    AOlitm4,  AOi16con1,   AOi16con3));
	mamexei(mam, I(AOiadd32,   AOiadd32, AOiadd32,   AOiadd32));
	mamexei(mam, I(AOiadd32r1, AOnop,    AOiadd32r3, AOnop));
	mamexei(mam, I(AOiadd32r2, AOnop,    AOnop,      AOnop));

	printf("\n\nsum{-1..-8} = %ld\n\n", mamalutos(mam, 0));
}

static void checkmam(Mam *mam) {
	for (int op = 0; op < NAOp;) {
		if ((op&0x7) == 0)
			printf("--------\n");
		assert((aoptab[op].ta0 == vxxt) == (aoptab[op].na == 0));
		assert((aoptab[op].ta1 == vxxt) == (aoptab[op].na <= 1));
		assert((aoptab[op].tr == vxxt) == (aoptab[op].nr == 0));
		assert(aoptab[op].na <= 2);
		assert(aoptab[op].nr <= 1);
		mamexei(mam, I(op, op, op, op));
		if (!mam->trap) {
			printf("    clk %3lu: %4d 0x%02x %3s %10s    (%s) <- (%s, %s)\n", mam->clk, op, op, UNITS[aoptab[op].o.unit], aoptab[op].o.name, TYPES[aoptab[op].tr], TYPES[aoptab[op].ta0], TYPES[aoptab[op].ta1]);
			op++;
		} else {
			printf("    clk %3lu: trap cycle\n", mam->clk);
		}
	}
	printf("\nDone!\n\n");
}
#endif /*0*/

int main() {
	/* Mam mam = {0}; */
	/* printf("#ALU ops is %d\n", NAOp); */
	/* mam.dbg = 0; */
	/* checkmam(&mam); */
	/* add0to7slow(&mam); */
	/* add0to7fast(&mam); */
	/* addm1tom8slow(&mam); */
	/* addm1tom8fast(&mam); */
	/* addm1tom8fast16(&mam); */
	//encadd0to7slow(&(CLine){0});
	runadd0to7slow();
	printf("\n#ALU ops is %d\n\n", NAOp);
	printf("\n#CTL ops is %d\n\n", NCOp);
}
