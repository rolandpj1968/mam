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

union I64F64 {
	i64 i64;
	f64 f64;
};

static f64 v64ttof64t(v64 v) {
	union I64F64 i64f64;
	i64f64.i64 = (i64)v;
	return i64f64.f64;
}

static v64 f64ttov64t(f64 v) {
	union I64F64 i64f64;
	i64f64.f64 = v;
	return (u64)i64f64.i64;
}

union I32F32 {
	i32 i32;
	f32 f32;
};

static f32 v64ttof32t(v64 v) {
	union I32F32 i32f32;
	i32f32.i32 = v64ttoi32t(v);
	return i32f32.f32;
}

/* 32-bit fp ALU results have hi bits set */
static v64 f32ttov64t(f32 v) {
	union I32F32 i32f32;
	i32f32.f32 = v;
	return (u64)(i32f32.i32 | 0xffffffff00000000ULL);
}

static v64 regr(Alu* alu, u8 n) {
	assert(n < 4);
	return alu->reg[n];
}

static void regw(Alu* alu, u8 n, v64 v) {
	assert(n < 4);
	alu->reg[n] = v;
}

static v64 stkr(Alu* alu, u8 n) {
	assert(n < 4);
	return alu->stk[(alu->tos+n)&3];
}

static void stkw(Alu* alu, u8 n, v64 v) {
	assert(n < 4);
	alu->stk[(alu->tos+n)&3] = v;
}

/* full stack */
static v64 pop(Alu* alu) {
	v64 v = stkr(alu, 0);
	alu->tos = (alu->tos-1) & 3;
	return v;
}

/* full stack */
static void push(Alu* alu, v64 v) {
	alu->tos = (alu->tos+1) & 3;
	stkw(alu, 0, v);
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

	f32 a0f32 = 0, a1f32 = 0, rf32 = 0;
	bool a0f32b = 0, a1f32b = 0, rf32b = 0;

	f64 a0f64 = 0, a1f64 = 0, rf64 = 0;
	bool a0f64b = 0, a1f64b = 0, rf64b = 0;

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
		case f32t: S(a1f32) = v64ttof32t(a1); break;
		case f64t: S(a1f64) = v64ttof64t(a1); break;
		case v64t: S(a1) = a1; break;
		default: assert(0 && "invalid a1 type");
		}
	}
	if (op->na >= 1) {
		S(a0) = pop(alu);
		switch (op->ta0) {
		case i32t: S(a0i32) = v64ttoi32t(a0); break;
		case i64t: S(a0i64) = v64ttoi64t(a0); break;
		case f32t: S(a0f32) = v64ttof32t(a0); break;
		case f64t: S(a0f64) = v64ttof64t(a0); break;
		case v64t: S(a0) = a0; break;
		default: assert(0 && "invalid a0 type");
		}
	}

	switch (o) {
	case AOidiv32:
	case AOirem32:
	case AOiudiv32:
	case AOiurem32:
		if (V(a1i32) == 0) {
			alu->err = AluIDiv0;
			goto Done;
		}
		break;
	case AOidiv64:
	case AOirem64:
	case AOiudiv64:
	case AOiurem64:
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

	case AOiadd32:    S(ri32) = V(a0i32) + V(a1i32); break;
	case AOisub32:    S(ri32) = V(a0i32) - V(a1i32); break;
	case AOirsub32:   S(ri32) = V(a1i32) - V(a0i32); break;
	case AOidiv32:    S(ri32) = V(a0i32) / V(a1i32);	break;
	case AOirem32:    S(ri32) = V(a0i32) % V(a1i32); break;
	case AOiudiv32:   S(ri32) = (i32)((u32)V(a0i32) / (u32)V(a1i32)); break;
	case AOiurem32:   S(ri32) = (i32)((u32)V(a0i32) % (u32)V(a1i32)); break;
	case AOimul32:    S(ri32) = V(a0i32) * V(a1i32); break;

	case AOiadd64:    S(ri64) = V(a0i64) + V(a1i64); break;
	case AOisub64:    S(ri64) = V(a0i64) - V(a1i64); break;
	case AOirsub64:   S(ri64) = V(a1i64) - V(a0i64); break;
	case AOidiv64:    S(ri64) = V(a0i64) / V(a1i64);	break;
	case AOirem64:    S(ri64) = V(a0i64) % V(a1i64); break;
	case AOiudiv64:   S(ri64) = (i64)((u64)V(a0i64) / (u64)V(a1i64)); break;
	case AOiurem64:   S(ri64) = (i64)((u64)V(a0i64) % (u64)V(a1i64)); break;
	case AOimul64:    S(ri64) = V(a0i64) * V(a1i64); break;

/* Integer add with remote ALU tos */
	case AOiadd32r0:
	case AOiadd32r1:
	case AOiadd32r2:
	case AOiadd32r3: {
		v64 a1r = mamalutos(mam, (u8)(o-AOiadd32r0));
		S(ri32) = V(a0i32) + (i32)a1r;
		break;
	}
	case AOiadd64r0:
	case AOiadd64r1:
	case AOiadd64r2:
	case AOiadd64r3: {
		v64 a1r = mamalutos(mam, (u8)(o-AOiadd64r0));
		S(ri64) = V(a0i64) + (i64)a1r;
		break;
	}

	case AOfadd32:    S(rf32) = V(a0f32) + V(a1f32); break;
	case AOfsub32:    S(rf32) = V(a0f32) + V(a1f32); break;
	case AOfrsub32:   S(rf32) = V(a0f32) + V(a1f32); break;
	case AOfdiv32:    S(rf32) = V(a0f32) + V(a1f32); break;
	case AOfrem32:    S(rf32) = V(a0f32) + V(a1f32); break;
	case AOfmul32:    S(rf32) = V(a0f32) + V(a1f32); break;

	case AOfadd64:    S(rf64) = V(a0f64) + V(a1f64); break;
	case AOfsub64:    S(rf64) = V(a0f64) + V(a1f64); break;
	case AOfrsub64:   S(rf64) = V(a0f64) + V(a1f64); break;
	case AOfdiv64:    S(rf64) = V(a0f64) + V(a1f64); break;
	case AOfrem64:    S(rf64) = V(a0f64) + V(a1f64); break;
	case AOfmul64:    S(rf64) = V(a0f64) + V(a1f64); break;

/* Shift Binary */

	case AOisar32:    S(ri32) = (V(a0i32) >> (u32)V(a1i32)); break;
	case AOishr32:    S(ri32) = (i32)((u32)V(a0i32) >> (u32)V(a1i32)); break;
	case AOishl32:    S(ri32) = (V(a0i32) << (u32)V(a1i32)); break;
	case AOirotr32:   alu->err = AluNoImpl; break;

	case AOisar64:    S(ri64) = (V(a0i64) >> (u64)V(a1i32)); break;
	case AOishr64:    S(ri64) = (i64)((u64)V(a0i64) >> (u64)V(a1i32)); break;
	case AOishl64:    S(ri64) = (V(a0i64) << (u64)V(a1i32)); break;
	case AOirotr64:   alu->err = AluNoImpl; break;

/* Bits */

	case AOiand32:    S(ri32) = V(a0i32) & V(a1i32); break;
	case AOior32:     S(ri32) = V(a0i32) | V(a1i32); break;
	case AOixor32:    S(ri32) = V(a0i32) ^ V(a1i32); break;
	case AOinot32:    S(ri32) = ~V(a0i32); break;

	case AOiand64:    S(ri64) = V(a0i64) & V(a1i64); break;
	case AOior64:     S(ri64) = V(a0i64) | V(a1i64); break;
	case AOixor64:    S(ri64) = V(a0i64) ^ V(a1i64); break;
	case AOinot64:    S(ri64) = ~V(a0i64); break;

/* Arithmetic Unary */

	case AOineg32:    S(ri32) = -V(a0i32); break;
	case AOineg64:    S(ri64) = -V(a0i64); break;
	case AOfneg32:    S(rf32) = -V(a0f32); break;
	case AOfneg64:    S(rf64) = -V(a0f64); break;

/* Comparisons */

	case AOiceq32:    S(ri64) = (i64)(V(a0i32) == V(a1i32)); break;
	case AOicne32:    S(ri64) = (i64)(V(a0i32) != V(a1i32)); break;
	case AOiceq64:    S(ri64) = (i64)(V(a0i64) == V(a1i64)); break;
	case AOicne64:    S(ri64) = (i64)(V(a0i64) != V(a1i64)); break;

	case AOicsge32:   S(ri64) = (i64)(V(a0i32) >= V(a1i32)); break;
	case AOicsgt32:   S(ri64) = (i64)(V(a0i32) >  V(a1i32)); break;
	case AOicsle32:   S(ri64) = (i64)(V(a0i32) <= V(a1i32)); break;
	case AOicslt32:   S(ri64) = (i64)(V(a0i32) <  V(a1i32)); break;
	case AOicuge32:   S(ri64) = (i64)((u32)V(a0i32) >= (u32)V(a1i32)); break;
	case AOicugt32:   S(ri64) = (i64)((u32)V(a0i32) >  (u32)V(a1i32)); break;
	case AOicule32:   S(ri64) = (i64)((u32)V(a0i32) <= (u32)V(a1i32)); break;
	case AOicult32:   S(ri64) = (i64)((u32)V(a0i32) <  (u32)V(a1i32)); break;

	case AOicsge64:   S(ri64) = (i64)(V(a0i64) >= V(a1i64)); break;
	case AOicsgt64:   S(ri64) = (i64)(V(a0i64) >  V(a1i64)); break;
	case AOicsle64:   S(ri64) = (i64)(V(a0i64) <= V(a1i64)); break;
	case AOicslt64:   S(ri64) = (i64)(V(a0i64) <  V(a1i64)); break;
	case AOicuge64:   S(ri64) = (i64)((u64)V(a0i64) >= (u64)V(a1i64)); break;
	case AOicugt64:   S(ri64) = (i64)((u64)V(a0i64) >  (u64)V(a1i64)); break;
	case AOicule64:   S(ri64) = (i64)((u64)V(a0i64) <= (u64)V(a1i64)); break;
	case AOicult64:   S(ri64) = (i64)((u64)V(a0i64) <  (u64)V(a1i64)); break;

	case AOfceq32:    S(ri64) = (i64)(V(a0f32) == V(a1f32)); break;
	case AOfcge32:    S(ri64) = (i64)(V(a0f32) >= V(a1f32)); break;
	case AOfcgt32:    S(ri64) = (i64)(V(a0f32) >  V(a1f32)); break;
	case AOfcle32:    S(ri64) = (i64)(V(a0f32) <= V(a1f32)); break;
	case AOfclt32:    S(ri64) = (i64)(V(a0f32) <  V(a1f32)); break;
	case AOfcne32:    S(ri64) = (i64)(V(a0f32) != V(a1f32)); break;
	case AOfco32:     alu->err = AluNoImpl; break;
	case AOfcuo32:    alu->err = AluNoImpl; break;

	case AOfceq64:    S(ri64) = (i64)(V(a0f64) == V(a1f64)); break;
	case AOfcge64:    S(ri64) = (i64)(V(a0f64) >= V(a1f64)); break;
	case AOfcgt64:    S(ri64) = (i64)(V(a0f64) >  V(a1f64)); break;
	case AOfcle64:    S(ri64) = (i64)(V(a0f64) <= V(a1f64)); break;
	case AOfclt64:    S(ri64) = (i64)(V(a0f64) <  V(a1f64)); break;
	case AOfcne64:    S(ri64) = (i64)(V(a0f64) != V(a1f64)); break;
	case AOfco64:     alu->err = AluNoImpl; break;
	case AOfcuo64:    alu->err = AluNoImpl; break;

/* Integer comparisons with remote ALU tos */

	case AOiceq32r0:
	case AOiceq32r1:
	case AOiceq32r2:
	case AOiceq32r3: {
		v64 a1r = mamalutos(mam, (u8)(o-AOiceq32r0));
		S(ri64) = (i64)(V(a0i32) == (i32)a1r);
		break;
	}
	case AOiceq64r0:
	case AOiceq64r1:
	case AOiceq64r2:
	case AOiceq64r3: {
		v64 a1r = mamalutos(mam, (u8)(o-AOiceq64r0));
		S(ri64) = (i64)(V(a0i64) == (i64)a1r);
		break;
	}
	case AOiclt32r0:
	case AOiclt32r1:
	case AOiclt32r2:
	case AOiclt32r3: {
		v64 a1r = mamalutos(mam, (u8)(o-AOiclt32r0));
		S(ri64) = (i64)(V(a0i32) < (i32)a1r);
		break;
	}
	case AOiclt64r0:
	case AOiclt64r1:
	case AOiclt64r2:
	case AOiclt64r3: {
		v64 a1r = mamalutos(mam, (u8)(o-AOiclt64r0));
		S(ri64) = (i64)(V(a0i64) < (i64)a1r);
		break;
	}

/* Extensions and Truncations */

	case AOexts8:     S(ri64) = (i64)(i8)V(a0i64); break;
	case AOextu8:     S(ri64) = (i64)(u8)V(a0i64); break;
	case AOexts16:    S(ri64) = (i64)(i16)V(a0i64); break;
	case AOextu16:    S(ri64) = (i64)(u16)V(a0i64); break;

	case AOexts32:    S(ri64) = (i64)(i32)V(a0i64); break;
	case AOextu32:    S(ri64) = (i64)(u32)V(a0i64); break;

	case AOfext32:    S(rf64) = (f64)V(a0f32); break;
	case AOftrunc64:  S(rf32) = (f32)V(a0f64); break;

	case AOf32toi32:  S(ri32) = (i32)V(a0f32); break;
	case AOf32tou32:  S(ri32) = (i32)(u32)V(a0f32); break;
	case AOf32toi64:  S(ri64) = (i64)V(a0f32); break;
	case AOf32tou64:  S(ri64) = (i64)(u64)V(a0f32); break;
	case AOf64toi32:  S(ri32) = (i32)V(a0f64); break;
	case AOf64tou32:  S(ri32) = (i32)(u32)V(a0f64); break;
	case AOf64toi64:  S(ri64) = (i64)V(a0f64); break;
	case AOf64tou64:  S(ri64) = (i64)(u64)V(a0f64); break;

	case AOi32tof32:  S(rf32) = (f32)V(a0i32); break;
	case AOu32tof32:  S(rf32) = (f32)(u32)V(a0i32); break;
	case AOi64tof32:  S(rf32) = (f32)V(a0i64); break;
	case AOu64tof32:  S(rf32) = (f32)(u64)V(a0i64); break;
	case AOi32tof64:  S(rf64) = (f64)V(a0i32); break;
	case AOu32tof64:  S(rf64) = (f64)(u32)V(a0i32); break;
	case AOi64tof64:  S(rf64) = (f64)V(a0i64); break;
	case AOu64tof64:  S(rf64) = (f64)(u64)V(a0i64); break;

/* Stack read */
	case AOstk0:      S(r) = stkr(alu, 0); break;
	case AOstk1:      S(r) = stkr(alu, 1); break;
	case AOstk2:      S(r) = stkr(alu, 2); break;
	case AOstk3:      S(r) = stkr(alu, 3); break;

/* Register read */
	case AOreg0:      S(r) = regr(alu, 0); break;
	case AOreg1:      S(r) = regr(alu, 1); break;
	case AOreg2:      S(r) = regr(alu, 2); break;
	case AOreg3:      S(r) = regr(alu, 3); break;

/* Register write popping */
	case AOregp0:     regw(alu, 0, V(a0)); break;
	case AOregp1:     regw(alu, 1, V(a0)); break;
	case AOregp2:     regw(alu, 2, V(a0)); break;
	case AOregp3:     regw(alu, 3, V(a0)); break;

/* Register write non-popping */
	case AOregw0:     regw(alu, 0, V(a0)); S(r) = a0; break;
	case AOregw1:     regw(alu, 1, V(a0)); S(r) = a0; break;
	case AOregw2:     regw(alu, 2, V(a0)); S(r) = a0; break;
	case AOregw3:     regw(alu, 3, V(a0)); S(r) = a0; break;

/* Remote alu TOS access */
	case AOalur0:
	case AOalur1:
	case AOalur2:
	case AOalur3:

/* Remote mem value access */
	case AOmem0v0:
	case AOmem0v1:
	case AOmem1v0:
	case AOmem1v1:    skip = 1; break;

/* Select using remote alu condition */
	case AOselzr0:
	case AOselzr1:
	case AOselzr2:
	case AOselzr3: {
		v64 c = mamalutos(mam, (u8)(o-AOselzr0));
		S(r) = c ? V(a1) : V(a0);
		break;
	}
	case AOselnzr0:
	case AOselnzr1:
	case AOselnzr2:
	case AOselnzr3: {
		v64 c = mamalutos(mam, (u8)(o-AOselnzr0));
		S(r) = c ? V(a0) : V(a1);
		break;
	}

/* Literal constants */
	case AOlit0:
	case AOlit1:
	case AOlit2:
	case AOlit3:      S(ri64) = (i64)(o-AOlit0); break;

	case AOlitm1:
	case AOlitm2:
	case AOlitm3:
	case AOlitm4:     S(ri64) = -(i64)(o-AOlitm1+1); break;

/* Icache constants */
	case AOi8con0:
	case AOi8con1:
	case AOi8con2:
	case AOi8con3: {
		/* sign-extended */
		S(ri64) = (i64)(i8)ctlicu8(&mam->ctl, (u8)(o-AOi8con0));
		break;
	}
	case AOi16con0:
	case AOi16con1:
	case AOi16con2:
	case AOi16con3: {
		/* sign-extended */
		S(ri64) = (i64)(i16)ctlicu16(&mam->ctl, (u8)((o-AOi16con0)*2));
		break;
	}
	case AOi32con0:
	case AOi32con1:
	case AOi32con2:
	case AOi32con3: {
		/* sign-extended */
		S(ri64) = (i64)(i32)ctlicu32(&mam->ctl, (u8)((o-AOi32con0)*4));
		break;
	}
	case AOi64con0:
	case AOi64con1:
	case AOi64con2:
	case AOi64con3: {
		S(ri64) = (i64)ctlicu64(&mam->ctl, (u8)((o-AOi64con0)*8));
		break;
	}

/* Reserved opcodes */
	default:
		alu->err = AluBadOp;
		break;
	}

Done:
	assert(op->nr <= 1);
	if (skip || alu->err != AluNoErr)
		return;
	if (op->nr == 1) {
		switch (op->tr) {
		case i32t: S(r) = i32ttov64t(V(ri32)); break;
		case i64t: S(r) = i64ttov64t(V(ri64)); break;
		case f32t: S(r) = f32ttov64t(V(rf32)); break;
		case f64t: S(r) = f64ttov64t(V(rf64)); break;
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
	case AOalur0:   S(r) = mamalutos(mam, 0); break;
	case AOalur1:   S(r) = mamalutos(mam, 1); break;
	case AOalur2:   S(r) = mamalutos(mam, 2); break;
	case AOalur3:   S(r) = mamalutos(mam, 3); break;

/* Remote mem value access */
	case AOmem0v0: S(r) = mammemv(mam, 0, 0); break;
	case AOmem0v1: S(r) = mammemv(mam, 0, 1); break;
	case AOmem1v0: S(r) = mammemv(mam, 1, 0); break;
	case AOmem1v1: S(r) = mammemv(mam, 1, 1); break;

	default: skip = 1; break;

	}

	if (skip || alu->err != AluNoErr)
		return;

	push(alu, V(r));
}

v64 alutos(Alu *alu) {
	return stkr(alu, 0);
}
