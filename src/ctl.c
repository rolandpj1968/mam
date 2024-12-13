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
