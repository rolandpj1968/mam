#include "all.h"

static void add0to7slow(Mam *mam) {
	wricu8(mam->ctl.ic, 0, (u8)4);
	wricu8(mam->ctl.ic, 1, (u8)5);
	wricu8(mam->ctl.ic, 2, (u8)6);
	wricu8(mam->ctl.ic, 3, (u8)7);
	mamtick(mam, (u8[4]){AOlit0,   AOlit2,   AOi8con0, AOi8con2});
	mamtick(mam, (u8[4]){AOlit1,   AOlit3,   AOi8con1, AOi8con3});
	mamtick(mam, (u8[4]){AOiadd32, AOiadd32, AOiadd32, AOiadd32});
	mamtick(mam, (u8[4]){AOalur1,  AOnop,    AOalur3,  AOnop});
	mamtick(mam, (u8[4]){AOiadd32, AOnop,    AOiadd32, AOnop});
	mamtick(mam, (u8[4]){AOalur2,  AOnop,    AOnop,    AOnop});
	mamtick(mam, (u8[4]){AOiadd32, AOnop,    AOnop,    AOnop});

	printf("\n\nsum{0..7} = %lu\n\n", mamalutos(mam, 0));
}

static void add0to7fast(Mam *mam) {
	wricu8(mam->ctl.ic, 0, (u8)4);
	wricu8(mam->ctl.ic, 1, (u8)5);
	wricu8(mam->ctl.ic, 2, (u8)6);
	wricu8(mam->ctl.ic, 3, (u8)7);
	mamtick(mam, (u8[4]){AOlit0,     AOlit2,   AOi8con0,   AOi8con2});
	mamtick(mam, (u8[4]){AOlit1,     AOlit3,   AOi8con1,   AOi8con3});
	mamtick(mam, (u8[4]){AOiadd32,   AOiadd32, AOiadd32,   AOiadd32});
	mamtick(mam, (u8[4]){AOiadd32r1, AOnop,    AOiadd32r3, AOnop});
	mamtick(mam, (u8[4]){AOiadd32r2, AOnop,    AOnop,      AOnop});

	printf("\n\nsum{0..7} = %lu\n\n", mamalutos(mam, 0));
}

static void addm1tom8slow(Mam *mam) {
	wricu8(mam->ctl.ic, 1, (u8)-5);
	wricu8(mam->ctl.ic, 2, (u8)-6);
	wricu8(mam->ctl.ic, 3, (u8)-7);
	wricu8(mam->ctl.ic, 0, (u8)-8);
	mamtick(mam, (u8[4]){AOlitm1,  AOlitm3,  AOi8con0, AOi8con2});
	mamtick(mam, (u8[4]){AOlitm2,  AOlitm4,  AOi8con1, AOi8con3});
	mamtick(mam, (u8[4]){AOiadd32, AOiadd32, AOiadd32, AOiadd32});
	mamtick(mam, (u8[4]){AOalur1,  AOnop,    AOalur3,  AOnop});
	mamtick(mam, (u8[4]){AOiadd32, AOnop,    AOiadd32, AOnop});
	mamtick(mam, (u8[4]){AOalur2,  AOnop,    AOnop,    AOnop});
	mamtick(mam, (u8[4]){AOiadd32, AOnop,    AOnop,    AOnop});

	printf("\n\nsum{-1..-8} = %ld\n\n", mamalutos(mam, 0));
}

static void addm1tom8fast(Mam *mam) {
	wricu8(mam->ctl.ic, 1, (u8)-5);
	wricu8(mam->ctl.ic, 2, (u8)-6);
	wricu8(mam->ctl.ic, 3, (u8)-7);
	wricu8(mam->ctl.ic, 0, (u8)-8);
	mamtick(mam, (u8[4]){AOlitm1,    AOlitm3,  AOi8con0,   AOi8con2});
	mamtick(mam, (u8[4]){AOlitm2,    AOlitm4,  AOi8con1,   AOi8con3});
	mamtick(mam, (u8[4]){AOiadd32,   AOiadd32, AOiadd32,   AOiadd32});
	mamtick(mam, (u8[4]){AOiadd32r1, AOnop,    AOiadd32r3, AOnop});
	mamtick(mam, (u8[4]){AOiadd32r2, AOnop,    AOnop,      AOnop});

	printf("\n\nsum{-1..-8} = %ld\n\n", mamalutos(mam, 0));
}

static void addm1tom8fast16(Mam *mam) {
	wricu16(mam->ctl.ic, 2, (u16)-5);
	assert(ctlicu16(&mam->ctl, 2) == (u16)-5);
	wricu16(mam->ctl.ic, 4, (u16)-6);
	wricu16(mam->ctl.ic, 6, (u16)-7);
	wricu16(mam->ctl.ic, 0, (u16)-8);
	mamtick(mam, (u8[4]){AOlitm1,    AOlitm3,  AOi16con0,   AOi16con2});
	mamtick(mam, (u8[4]){AOlitm2,    AOlitm4,  AOi16con1,   AOi16con3});
	mamtick(mam, (u8[4]){AOiadd32,   AOiadd32, AOiadd32,   AOiadd32});
	mamtick(mam, (u8[4]){AOiadd32r1, AOnop,    AOiadd32r3, AOnop});
	mamtick(mam, (u8[4]){AOiadd32r2, AOnop,    AOnop,      AOnop});

	printf("\n\nsum{-1..-8} = %ld\n\n", mamalutos(mam, 0));
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
		mamtick(mam, ao);
		if (!mam->trap) {
			printf("    clk %3lu: %4d 0x%02x %3s %10s    (%s) <- (%s, %s)\n", mam->clk, op, op, UNITS[aoptab[op].o.unit], aoptab[op].o.name, TYPES[aoptab[op].tr], TYPES[aoptab[op].ta0], TYPES[aoptab[op].ta1]);
			op++;
		} else {
			printf("    clk %3lu: trap cycle\n", mam->clk);
		}
	}	
	printf("\nDone!\n");
}

int main() {
	Mam mam = {0};
	printf("#ALU ops is %d\n", NAOp);
	mam.dbg = 1;
	checkmam(&mam);
	add0to7slow(&mam);
	add0to7fast(&mam);
	addm1tom8slow(&mam);
	addm1tom8fast(&mam);
	addm1tom8fast16(&mam);
	printf("\n#ALU ops is %d\n\n", NAOp);
}
