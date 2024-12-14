#include "all.h"

/* Icache constant access */

u8 ctlicu8(Ctl *ctl, u8 noff) {
	assert(noff < 64);
	return ctl->ic.u8[64-1-noff];
}

u16 ctlicu16(Ctl *ctl, u8 noff) {
	assert(noff < 64);
	assert((noff&1) == 0);
	return ctl->ic.u16[(64-2-noff)/2];
}

u32 ctlicu32(Ctl *ctl, u8 noff) {
	assert(noff < 64);
	assert((noff&3) == 0);
	return ctl->ic.u32[(64-4-noff)/4];
}

u64 ctlicu64(Ctl *ctl, u8 noff) {
	assert(noff < 64);
	assert((noff&7) == 0);
	return ctl->ic.u64[(64-8-noff)/8];
}

/* fetch and decode for now - will be pipelined... */
void ctlexe0(Mam *mam, Ctl *ctl) {
	CLine *l;
	Ins i = {0};
	u64 off = ctl->ip & 63;
	u8 ilen;
	ctl->ilen = 0;
	l = findcline(mam->ndram, mam->dram, ctl->ip);
	if (l == 0) {
		ctl->err = CtlBadIp;
		return;
	}
	ctl->ic = *l;
	for (u8 n = 0; n < 8 && off+n < 64; n++) {
		i.op[n] = ctl->ic.u8[off+n];
	}
	ctl->ib = ins2bundle(i, &ilen);
	if (64 < off+ilen) {
		ctl->err = CtlInsOvr;
		return;
	}
	ctl->ilen = ilen;
}

void ctlexe1(Mam *mam, Ctl *ctl, CO o) {
	switch (o) {
	case COnop: break;
	case COhlt: ctl->err = CtlHlt; break;
/* Reserved opcodes */
	default: ctl->err = CtlBadOp; break;
	}
	mam->ctl.ip += mam->ctl.ilen;
}
