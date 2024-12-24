#include "all.h"

/* Register bitwise representation */

static i32 v64ttoi32t(v64 v) {
	return (i32)v;
}

/* 32-bit integer ALU results are sign-extended to 64 bits */
static v64 i32ttov64t(i32 v) {
	return (u64)(i64)v;
}

static i64 v64ttoi64t(v64 v) {
	return (i64)v;
}

static v64 i64ttov64t(u64 v) {
	return (u64)v;
}

static v64 rd_r(Alu* alu, u8 n) {
	assert(n < 4);
	return alu->reg[n];
}

static void wr_r(Alu* alu, u8 n, v64 v) {
	assert(n < 4);
	alu->reg[n] = v;
}

static v64 rd_s(Alu* alu, u8 n) {
	assert(n < 4);
	return alu->stk[(alu->tos+n)&3];
}

static void wr_s(Alu* alu, u8 n, v64 v) {
	assert(n < 4);
	alu->stk[(alu->tos+n)&3] = v;
}

/* full stack */
static v64 pop(Alu* alu) {
	v64 v = rd_s(alu, 0);
	alu->tos = (alu->tos-1) & 3;
	return v;
}

/* full stack */
static void push(Alu* alu, v64 v) {
	alu->tos = (alu->tos+1) & 3;
	wr_s(alu, 0, v);
}

#define S(a) a##b = 1; a
#define V(a) (assert(a##b), a)

void aluexe0(Mam *mam, Alu *alu, AO o) {
	v64 a0 = 0, a1 = 0, r = 0;
	bool a0b = 0, a1b = 0, rb = 0;

	i32 a0i32 = 0, a1i32 = 0, ri32 = 0;
	bool a0i32b = 0, a1i32b = 0, ri32b = 0;

	i64 a0i64 = 0, a1i64 = 0, ri64 = 0;
	bool a0i64b = 0, a1i64b = 0, ri64b = 0;

	bool skip = 0; /* remote values */

	alu->err = AluNoErr;

	AOp *op = &aoptab[o];

	assert(op->na <= 2);
	/* a1 is TOS */
	if (op->na >= 2) {
		a1 = pop(alu);
		switch (op->ta1) {
		case i32t: S(a1i32) = v64ttoi32t(a1); break;
		case i64t: S(a1i64) = v64ttoi64t(a1); break;
		case v64t: S(a1) = a1; break;
		default: assert(0 && "invalid a1 type");
		}
	}
	if (op->na >= 1) {
		S(a0) = pop(alu);
		switch (op->ta0) {
		case i32t: S(a0i32) = v64ttoi32t(a0); break;
		case i64t: S(a0i64) = v64ttoi64t(a0); break;
		case v64t: S(a0) = a0; break;
		default: assert(0 && "invalid a0 type");
		}
	}

	switch (o) {
	case AOdivw:
	case AOremw:
	case AOremuw:
		if (V(a1i32) == 0) {
			alu->err = AluIDiv0;
			goto Done;
		}
		break;
	case AOdiv:
	case AOrem:
	case AOdivu:
	case AOremu:
		if (V(a1i64) == 0) {
			alu->err = AluIDiv0;
			goto Done;
		}
		break;
	default: break;
	}

	switch (o) {

/* alu ops */

	case AOnop:      break;

/* Arithmetic Binary*/

	case AOadd:       S(ri64) = V(a0i64) + V(a1i64); break;
	case AOsub:       S(ri64) = V(a0i64) - V(a1i64); break;
	case AOrsub:      S(ri64) = V(a1i64) - V(a0i64); break;
	case AOneg:       S(ri64) = -V(a0i64); break;

	case AOaddw:      S(ri32) = V(a0i32) + V(a1i32); break;
	case AOsubw:      S(ri32) = V(a0i32) - V(a1i32); break;
	case AOrsubw:     S(ri32) = V(a1i32) - V(a0i32); break;

	case AOmul:       S(ri64) = V(a0i64) * V(a1i64); break;
	case AOmulh:      alu->err = AluNoImpl; break;
	case AOmulhsu:    alu->err = AluNoImpl; break;
	case AOmulhu:     alu->err = AluNoImpl; break;
	case AOdiv:       S(ri64) = V(a0i64) / V(a1i64); break;
	case AOrem:       S(ri64) = V(a0i64) % V(a1i64); break;
	case AOdivu:      S(ri64) = (i64)((u64)V(a0i64) / (u64)V(a1i64)); break;
	case AOremu:      S(ri64) = (i64)((u64)V(a0i64) % (u64)V(a1i64)); break;

	case AOmulw:      S(ri32) = V(a0i32) * V(a1i32); break;
	case AOdivw:      S(ri32) = V(a0i32) / V(a1i32);	break;
	case AOremw:      S(ri32) = V(a0i32) % V(a1i32); break;
	case AOremuw:     S(ri32) = (i32)((u32)V(a0i32) % (u32)V(a1i32)); break;

/* Integer add with remote ALU tos */

	case AOadd_a0:
	case AOadd_a1:
	case AOadd_a2:
	case AOadd_a3: {
		v64 a1r = mamalutos(mam, (u8)(o-AOadd_a0));
		S(ri64) = V(a0i64) + (i64)a1r;
		break;
	}
	case AOaddw_a0:
	case AOaddw_a1:
	case AOaddw_a2:
	case AOaddw_a3: {
		v64 a1r = mamalutos(mam, (u8)(o-AOaddw_a0));
		S(ri32) = V(a0i32) + (i32)a1r;
		break;
	}

/* Shift Binary */

	case AOsll:       S(ri64) = (V(a0i64) << (u64)V(a1i64)); break;
	case AOsrl:       S(ri64) = (i64)((u64)V(a0i64) >> (u64)V(a1i64)); break;
	case AOsra:       S(ri64) = (V(a0i64) >> (u64)V(a1i64)); break;

	case AOsllw:      S(ri32) = (V(a0i32) << (u32)V(a1i32)); break;
	case AOsrlw:      S(ri32) = (i32)((u32)V(a0i32) >> (u32)V(a1i32)); break;
	case AOsraw:      S(ri32) = (V(a0i32) >> (u32)V(a1i32)); break;

/* Bits */

	case AOand:       S(ri64) = V(a0i64) & V(a1i64); break;
	case AOor:        S(ri64) = V(a0i64) | V(a1i64); break;
	case AOxor:       S(ri64) = V(a0i64) ^ V(a1i64); break;
	case AOnot:       S(ri64) = ~V(a0i64); break;

/* Comparisons */

	case AOslt:       S(ri64) = (i64)(V(a0i64) < V(a1i64)); break;
	case AOsltu:      S(ri64) = (i64)((u64)V(a0i64) < (u64)V(a1i64)); break;
	case AOseq:       S(ri64) = (i64)(V(a0i64) == V(a1i64)); break;

/* Integer comparisons with remote ALU tos */

	case AOslt_a0:
	case AOslt_a1:
	case AOslt_a2:
	case AOslt_a3: {
		v64 a1r = mamalutos(mam, (u8)(o-AOslt_a0));
		S(ri64) = (i64)(V(a0i64) < (i64)a1r);
		break;
	}
	case AOsltu_a0:
	case AOsltu_a1:
	case AOsltu_a2:
	case AOsltu_a3: {
		v64 a1r = mamalutos(mam, (u8)(o-AOsltu_a0));
		S(ri64) = (i64)((u64)V(a0i64) < (u64)a1r);
		break;
	}
	case AOseq_a0:
	case AOseq_a1:
	case AOseq_a2:
	case AOseq_a3: {
		v64 a1r = mamalutos(mam, (u8)(o-AOseq_a0));
		S(ri64) = (i64)(V(a0i64) == (i64)a1r);
		break;
	}

/* Extensions and Truncations */

	case AOextb:      S(ri64) = (i64)(i8)V(a0i64); break;
	case AOextub:     S(ri64) = (i64)(u8)V(a0i64); break;
	case AOexth:      S(ri64) = (i64)(i16)V(a0i64); break;
	case AOextuh:     S(ri64) = (i64)(u16)V(a0i64); break;

	case AOextw:      S(ri64) = (i64)(i32)V(a0i64); break;
	case AOextuw:     S(ri64) = (i64)(u32)V(a0i64); break;

/* Stack read */
	case AOrd_s0:     S(r) = rd_s(alu, 0); break;
	case AOrd_s1:     S(r) = rd_s(alu, 1); break;
	case AOrd_s2:     S(r) = rd_s(alu, 2); break;
	case AOrd_s3:     S(r) = rd_s(alu, 3); break;

/* Register read */
	case AOrd_r0:     S(r) = rd_r(alu, 0); break;
	case AOrd_r1:     S(r) = rd_r(alu, 1); break;
	case AOrd_r2:     S(r) = rd_r(alu, 2); break;
	case AOrd_r3:     S(r) = rd_r(alu, 3); break;

/* Register write popping */
	case AOwp_r0:     wr_r(alu, 0, V(a0)); break;
	case AOwp_r1:     wr_r(alu, 1, V(a0)); break;
	case AOwp_r2:     wr_r(alu, 2, V(a0)); break;
	case AOwp_r3:     wr_r(alu, 3, V(a0)); break;

/* Register write non-popping */
	case AOwr_r0:     wr_r(alu, 0, V(a0)); S(r) = a0; break;
	case AOwr_r1:     wr_r(alu, 1, V(a0)); S(r) = a0; break;
	case AOwr_r2:     wr_r(alu, 2, V(a0)); S(r) = a0; break;
	case AOwr_r3:     wr_r(alu, 3, V(a0)); S(r) = a0; break;

/* Remote alu TOS access */
	case AOrd_a0:
	case AOrd_a1:
	case AOrd_a2:
	case AOrd_a3:

/* Remote mem value access */
	case AOrd_m0v0:
	case AOrd_m0v1:
	case AOrd_m1v0:
	case AOrd_m1v1:    skip = 1; break;

/* Select using remote alu condition */
	case AOselz_a0:
	case AOselz_a1:
	case AOselz_a2:
	case AOselz_a3: {
		v64 c = mamalutos(mam, (u8)(o-AOselz_a0));
		S(r) = c ? V(a1) : V(a0);
		break;
	}
	case AOselnz_a0:
	case AOselnz_a1:
	case AOselnz_a2:
	case AOselnz_a3: {
		v64 c = mamalutos(mam, (u8)(o-AOselnz_a0));
		S(r) = c ? V(a0) : V(a1);
		break;
	}

/* Icache constants */
	case AOconb0:
	case AOconb1:
	case AOconb2:
	case AOconb3:
	case AOconb4:
	case AOconb5:
	case AOconb6:
	case AOconb7: {
		/* sign-extended */
		S(ri64) = (i64)(i8)ctlicu8(&mam->ctl, (u8)(o-AOconb0));
		break;
	}
	case AOconh0:
	case AOconh1:
	case AOconh2:
	case AOconh3:
	case AOconh4:
	case AOconh5:
	case AOconh6:
	case AOconh7: {
		/* sign-extended */
		S(ri64) = (i64)(i16)ctlicu16(&mam->ctl, (u8)((o-AOconh0)*2));
		break;
	}
	case AOconw0:
	case AOconw1:
	case AOconw2:
	case AOconw3:
	case AOconw4:
	case AOconw5:
	case AOconw6:
	case AOconw7: {
		/* sign-extended */
		S(ri64) = (i64)(i32)ctlicu32(&mam->ctl, (u8)((o-AOconw0)*4));
		break;
	}
	case AOcond0:
	case AOcond1:
	case AOcond2:
	case AOcond3:
	case AOcond4:
	case AOcond5:
	case AOcond6:
	case AOcond7: {
		S(ri64) = (i64)ctlicu64(&mam->ctl, (u8)((o-AOcond0)*8));
		break;
	}

/* Reserved opcodes */
	default: alu->err = AluBadOp; break;
	}

Done:
	assert(op->nr <= 1);
	if (skip || alu->err != AluNoErr)
		return;
	if (op->nr == 1) {
		switch (op->tr) {
		case i32t: S(r) = i32ttov64t(V(ri32)); break;
		case i64t: S(r) = i64ttov64t(V(ri64)); break;
		case v64t: break;
		default: assert(0 && "invalid r type");
		}
		push(alu, V(r));
	}
}

void aluexe1(Mam *mam, Alu *alu, AO o) {
	v64 r = 0;
	bool rb = 0;
	bool skip = 0; /* everything except remote values */

	switch (o) {

/* Remote alu TOS access */
	case AOrd_a0:   S(r) = mamalutos(mam, 0); break;
	case AOrd_a1:   S(r) = mamalutos(mam, 1); break;
	case AOrd_a2:   S(r) = mamalutos(mam, 2); break;
	case AOrd_a3:   S(r) = mamalutos(mam, 3); break;

/* Remote mem value access */
	case AOrd_m0v0: S(r) = mammemv(mam, 0, 0); break;
	case AOrd_m0v1: S(r) = mammemv(mam, 0, 1); break;
	case AOrd_m1v0: S(r) = mammemv(mam, 1, 0); break;
	case AOrd_m1v1: S(r) = mammemv(mam, 1, 1); break;

	default: skip = 1; break;

	}

	if (skip || alu->err != AluNoErr)
		return;

	push(alu, V(r));
}

v64 alutos(Alu *alu) {
	return rd_s(alu, 0);
}
