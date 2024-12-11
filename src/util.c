#include "all.h"

char* UNITS[] = { "Alu", "Mem", "Ctl" };

char* TYPES[] = {"i32", "i64", "f32", "f64", "v64", "---"};

char* ALUERRS[] = {"none", "invi", "div0", "impl"};

void wricu8(v64 ic[8], u8 noff, u8 v8) {
	union u64u8x8 *pu64u8x8;
	assert(((u64)ic & 3) == 0);
	assert(noff < 64);
	u8 noff64 = noff >> 3;
	pu64u8x8 = (union u64u8x8*)&ic[8-1-noff64];
	pu64u8x8->v8[8-1-(noff&3)] = v8;
}
