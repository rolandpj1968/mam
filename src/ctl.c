#include "all.h"

/* Icache constant access */

u8 ctlicu8(Ctl *ctl, u8 noff) {
	union u64u8x8 u64u8x8;
	v64 *ic = ctl->ic;
	assert(((u64)ic & 3) == 0);
	assert(noff < 64);
	u8 noff64 = noff >> 3;
	u64u8x8.v64 = ic[8-1-noff64];
	return u64u8x8.v8[8-1-(noff&3)];
}

