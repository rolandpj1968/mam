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
	pu64u8x8->v8[8-1-(noff&7)] = v8;
}

void wricu16(v64 ic[8], u8 noff, u16 v16) {
	union u64u16x4 *pu64u16x4;
	assert(((u64)ic & 3) == 0);
	assert((noff & 1) == 0);
	assert(noff < 64);
	u8 noff64 = noff >> 3;
	pu64u16x4 = (union u64u16x4*)&ic[8-1-noff64];
	pu64u16x4->v16[4-1-(noff&7)/2] = v16;
}

Bundle mkbundle(AO ao0, AO ao1, AO ao2, AO ao3, u8 mo0, u8 mo1, u8 co0) {
	Bundle b = {0};
	b.op[BA0] = ao0;
	b.op[BA1] = ao1;
	b.op[BA2] = ao2;
	b.op[BA3] = ao3;
	b.op[BM0] = mo0;
	b.op[BM1] = mo1;
	b.op[BC]  = co0;
	return b;
}

Bundle ins2bundle(Ins i, u8 *plen) {
	Bundle b = {0};
	u8 flags = i.op[IF];
	u8 off = 1;
	for (u8 slot = 1; slot < 8; slot++) {
		if (flags & (1 << slot)) {
			b.op[slot] = i.op[off++];
		}
	}
	*plen = off;
	return b;
}

Ins bundle2ins(Bundle b, u8 *plen) {
	Ins i = {0};
	u8 flags = 0;
	u8 off = 1;
	for (u8 slot = 1; slot < 8; slot++) {
		if (b.op[slot]) {
			flags = flags | (1 << slot);
			i.op[off++] = b.op[slot];
		}
	}
	i.op[IF] = flags;
	*plen = off;
	return i;
}

