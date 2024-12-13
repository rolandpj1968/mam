#include "all.h"

char* UNITS[] = { "Alu", "Mem", "Ctl" };

char* TYPES[] = {"i32", "i64", "f32", "f64", "v64", "---"};

char* ALUERRS[] = {"none", "invi", "div0", "impl"};

void wricu8(CLine *ic, u8 noff, u8 v8) {
	assert(noff < 64);
	ic->u8[64-1-noff] = v8;
}

void wricu16(CLine *ic, u8 noff, u16 v16) {
	assert(noff < 64);
	assert((noff&1) == 0);
	ic->u16[(64-2-noff)/2] = v16;
}

void wricu32(CLine *ic, u8 noff, u32 v32) {
	assert(noff < 64);
	assert((noff&3) == 0);
	ic->u32[(64-4-noff)/4] = v32;
}

void wricu64(CLine *ic, u8 noff, u64 v64) {
	assert(noff < 64);
	assert((noff&7) == 0);
	ic->u64[(64-8-noff)/8] = v64;
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

