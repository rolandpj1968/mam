#include "all.h"

static void mamtrap(Mam *mam, u8 n) {
	/* For now... */
	printf("\nclk %12lu ALU %u raised %s... resetting...\n\n", mam->clk, n, ALUERRS[mam->alu[n].err]);
	mam->alu[n].err = AluNoErr;
}

/* For now... eventually we read code from "memory" */
void mamtick(Mam *mam, u8 ao[4]) {
	mam->clk++;
	mam->trap = 0;
	for (u8 n = 0; n < 4; n++) {
		if (mam->alu[n].err != AluNoErr) {
			mam->trap = 1;
			mamtrap(mam, n);
			if (mam->dbg >= 1) {
				printf("DBG: clk %10lu trap cycle ALU %u\n", mam->clk, n);
			}
			return;
		}
	}
	for (u8 n = 0; n < 4; n++) {
		aluexe0(mam, &mam->alu[n], ao[n]);
	}
	for (u8 n = 0; n < 4; n++) {
		mam->alutos[n] = alutos(&mam->alu[n]);
	}
	for (u8 n = 0; n < 4; n++) {
		aluexe1(mam, &mam->alu[n], ao[n]);
	}
	if (mam->dbg >= 1) {
		printf("DBG: clk %10lu - %16lx ALU[0] / %16lx ALU[1] / %16lx ALU[2] / 0x%16lx ALU[3]\n", mam->clk, mamalutos(mam, 0), mamalutos(mam, 1), mamalutos(mam, 2), mamalutos(mam, 3));
	}
}

v64 mamalutos(Mam *mam, u8 n) {
	assert(n < 4);
	return mam->alutos[n];
}

v64 mammemv(Mam *mam, u8 n, u8 m) {
	assert(n < 4);
	assert(m < 4);
	/* TODO stall */
	return mam->memv[n][m];
}

v64 mami8con(Mam *mam, u8 n) {
	/* sign-extended */
	return (v64)(i64)(i8)ctlicu8(&mam->ctl, n);
}
