#include "all.h"

char* UNITS[] = { "Alu", "Mem", "Ctl" };

char* TYPES[] = {"i32", "i64", "f32", "f64", "v64", "---"};

char* ALUERRS[] = {"none", "badi", "div0", "impl"};

char* CTLERRS[] = {"none", "iper", "iovr", "halt"};

char* ENCERRS[] = {"none", "covr", "iovr", "icov"};

u8 u8dummy;

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

Bundle mkbundle(AO ao0, AO ao1, AO ao2, AO ao3, u8 mo0, u8 mo1, CO co0) {
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

void mamexeb(Mam *mam, Bundle b) {
	mam->ctl.ib = b;
	mamtick(mam);
}

void mamexei(Mam *mam, Ins i) {
	u8 x;
	mam->ctl.ib = ins2bundle(i, &x);
	mamtick(mam);
}

static int conclash(bool bcons[4][4], u8 off) {
	if (off < 4 && bcons[0][off])
		return 1;
	if (off < 8 && bcons[1][off/2])
		return 1;
	if (off < 16 && bcons[2][off/4])
		return 1;
	if (off < 32 && bcons[3][off/8])
		return 1;
	return 0;
}

static u8 maxconoff(bool bcons[4][4], bool pbcons[4][4]) {
	u8 maxoff = 0;
	for (u8 n = 0; n < 4; n++) {
		for (u8 m = 0; m < 4; m++) {
			if (bcons[n][m] | pbcons[n][m]) {
				u8 max = (m<<n) + (1<<n)-1;
				if (maxoff < max) {
					maxoff = max;
				}
			}
		}
	}
	return maxoff;
}

EncErr encei(EncIns ei, CLine *ic, bool bc[4][4], u8* poff) {
	Ins i;
	u8 off = *poff;
	u8 conoff;
	u8 len = 0;

	for (u8 n = 0; n < 4; n++) {
		for (u8 m = 0; m < 4; m++) {
			if (ei.bc[n][m]) {
				for (u8 i = 0; i < 1<<n; i++) {
					if (conclash(bc, ((m<<n) + i))) {
						return EncConOvr;
					}
				}
			}
		}
	}
	i = bundle2ins(ei.b, &len);
	if (64 < off+len) {
		return EncInsOvr;
	}
	conoff = maxconoff(ei.bc, bc);
	if (64 < off+len + conoff) {
		return EncInsConOvr;
	}
	for (u8 n = 0; n < 4; n++) {
		for (u8 m = 0; m < 4; m++) {
			if (ei.bc[n][m]) {
				assert(!bc[n][m]);
				bc[n][m] = 1;
				switch (n) {
				case 0: wricu8(ic, (m<<n), (u8)ei.c[n][m]); break;
				case 1: wricu16(ic, (m<<n), (u16)ei.c[n][m]); break;
				case 2: wricu32(ic, (m<<n), (u32)ei.c[n][m]); break;
				case 3: wricu64(ic, (m<<n), (u64)ei.c[n][m]); break;
				}
			}
		}
	}
	for (u8 n = 0; n < len; n++) {
		ic->u8[off+n] = i.op[n];
	}
	*poff += len;
	return EncNoErr;
}

EncErr enceis(EncIns ei[], u8 nei, CLine *ic) {
	u8 off = 0;
	bool bc[4][4] = {0};
	*ic = (CLine){0};
	for (u8 n = 0; n < nei; n++) {
		EncErr err = encei(ei[n], ic, bc, &off);
		if (err != EncNoErr) {
			return err;
		}
	}
	return EncNoErr;
}

void dumpb(Bundle b) {
	printf("[[%8s, %8s, %8s, %8s] [%8s]]", aoptab[b.op[BA0]].o.name, aoptab[b.op[BA1]].o.name, aoptab[b.op[BA2]].o.name, aoptab[b.op[BA3]].o.name, coptab[b.op[BC]].o.name);
}

void dumpei(EncIns ei) {
	dumpb(ei.b);
	printf(" - ");
	for (u8 n = 0; n < 4; n++) {
		printf(" %s [", (char *[4]){"u8", "u16", "u32", "u64"}[n]);
		for (u8 m = 0; m < 4; m++) {
			if (ei.bc[n][m]) {
				printf((char *[4]){"0x%02lx", "0x%04lx", "0x%08lx", "0x%016lx"}[n], ei.c[n][m]);
			} else {
				printf("-");
			}
			printf("%s", (m<3 ? "," : ""));
		}
		printf("]%s", (n < 3 ? "," : ""));
	}
	printf("]\n");
}

void dumpeis(EncIns ei[], u8 nei) {
	for (u8 i = 0; i < nei; i++) {
		printf("ins %3u: ", i);
		dumpei(ei[i]);
	}
}
