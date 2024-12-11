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
	return alu->stk[n];
}

static void stkw(Alu* alu, u8 n, v64 v) {
	assert(n < 4);
	alu->stk[n] = v;
}

/* full stack */
static v64 pop(Alu* alu) {
	v64 v = stkr(alu, alu->tos);
	alu->tos = (alu->tos-1) & 3;
	return v;
}

/* full stack */
static void push(Alu* alu, v64 v) {
	alu->tos = (alu->tos+1) & 3;
	stkw(alu, alu->tos, v);
}

#define S(a) a##b = 1; a
#define V(a) (assert(a##b), a)

void exe0(Mam *mam, Alu *alu, AO o) {
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
		case v64t: break;
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
		case v64t: break;
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

	case AOiadd32:   S(ri32) = V(a0i32) + V(a1i32); break;
	case AOisub32:   S(ri32) = V(a0i32) - V(a1i32); break;
	case AOirsub32:  S(ri32) = V(a1i32) - V(a0i32); break;
	case AOidiv32:   S(ri32) = V(a0i32) / V(a1i32);	break;
	case AOirem32:   S(ri32) = V(a0i32) % V(a1i32); break;
	case AOiudiv32:  S(ri32) = (i32)((u32)V(a0i32) / (u32)V(a1i32)); break;
	case AOiurem32:  S(ri32) = (i32)((u32)V(a0i32) % (u32)V(a1i32)); break;
	case AOimul32:   S(ri32) = V(a0i32) * V(a1i32); break;

	case AOiadd64:   S(ri64) = V(a0i64) + V(a1i64); break;
	case AOisub64:   S(ri64) = V(a0i64) - V(a1i64); break;
	case AOirsub64:  S(ri64) = V(a1i64) - V(a0i64); break;
	case AOidiv64:   S(ri64) = V(a0i64) / V(a1i64);	break;
	case AOirem64:   S(ri64) = V(a0i64) % V(a1i64); break;
	case AOiudiv64:  S(ri64) = (i64)((u64)V(a0i64) / (u64)V(a1i64)); break;
	case AOiurem64:  S(ri64) = (i64)((u64)V(a0i64) % (u64)V(a1i64)); break;
	case AOimul64:   S(ri64) = V(a0i64) * V(a1i64); break;
	
	case AOfadd32:   S(rf32) = V(a0f32) + V(a1f32); break;
	case AOfsub32:   S(rf32) = V(a0f32) + V(a1f32); break;
	case AOfrsub32:  S(rf32) = V(a0f32) + V(a1f32); break;
	case AOfdiv32:   S(rf32) = V(a0f32) + V(a1f32); break;
	case AOfrem32:   S(rf32) = V(a0f32) + V(a1f32); break;
	case AOfmul32:   S(rf32) = V(a0f32) + V(a1f32); break;

	case AOfadd64:   S(rf64) = V(a0f64) + V(a1f64); break;
	case AOfsub64:   S(rf64) = V(a0f64) + V(a1f64); break;
	case AOfrsub64:  S(rf64) = V(a0f64) + V(a1f64); break;
	case AOfdiv64:   S(rf64) = V(a0f64) + V(a1f64); break;
	case AOfrem64:   S(rf64) = V(a0f64) + V(a1f64); break;
	case AOfmul64:   S(rf64) = V(a0f64) + V(a1f64); break;
	
/* Shift Binary */

	case AOisar32:
	case AOishr32:
	case AOishl32:
	case AOirotr32:

	case AOisar64:
	case AOishr64:
	case AOishl64:
	case AOirotr64:

/* Bits */

	case AOiand32:
	case AOior32:
	case AOixor32:
	case AOinot32:

	case AOiand64:
	case AOior64:
	case AOixor64:
	case AOinot64:

/* Arithmetic Unary */

	case AOineg32:
	case AOineg64:
	case AOfneg32:
	case AOfneg64:
	
/* Comparisons */

	case AOiceq32:
	case AOicne32:
	case AOiceq64:
	case AOicne64:

	case AOicsge32:
	case AOicsgt32:
	case AOicsle32:
	case AOicslt32:
	case AOicuge32:
	case AOicugt32:
	case AOicule32:
	case AOicult32:

	case AOicsge64:
	case AOicsgt64:
	case AOicsle64:
	case AOicslt64:
	case AOicuge64:
	case AOicugt64:
	case AOicule64:
	case AOicult64:

	case AOfceq32:
	case AOfcge32:
	case AOfcgt32:
	case AOfcle32:
	case AOfclt32:
	case AOfcne32:
	case AOfco32:
	case AOfcuo32:

	case AOfceq64:
	case AOfcge64:
	case AOfcgt64:
	case AOfcle64:
	case AOfclt64:
	case AOfcne64:
	case AOfco64:
	case AOfcuo64:

/* Extensions and Truncations */

	case AOi32exts8:
	case AOi32extu8:
	case AOi32exts16:
	case AOi32extu16:

	case AOi64exts8:
	case AOi64extu8:
	case AOi64exts16:
	case AOi64extu16:

	case AOi64exts32:
	case AOi64extu32:

	case AOfext32:
	case AOftrunc64:

/* Select using remote alu condition */
	case AOsel0:
	case AOsel1:
	case AOsel2:
	case AOsel3:

	case AOf32tosi32:
	case AOf32toui32:
	case AOf32tosi64:
	case AOf32toui64:
	case AOf64tosi32:
	case AOf64toui32:
	case AOf64tosi64:
	case AOf64toui64:

	case AOi32stof32:
	case AOi32utof32:
	case AOi64stof32:
	case AOi64utof32:
	case AOi32stof64:
	case AOi32utof64:
	case AOi64stof64:
	case AOi64utof64: 

/* Stack read */
	case AOstk0:
	case AOstk1:
	case AOstk2:
	case AOstk3:
	
/* Register read */
	case AOreg0:      S(r) = regr(alu, 0); break;
	case AOreg1:      S(r) = regr(alu, 1); break;
	case AOreg2:      S(r) = regr(alu, 2); break;
	case AOreg3:      S(r) = regr(alu, 3); break;
	
/* Register write popping */
	case AOregp0:
	case AOregp1:
	case AOregp2:
	case AOregp3:
	
/* Register write non-popping */
	case AOregw0:
	case AOregw1:
	case AOregw2:
	case AOregw3:

/* Remote alu TOS access */
	case AOtos0:
	case AOtos1:
	case AOtos2:
	case AOtos3:

/* Remote mem value access */
	case AOmem0v0:
	case AOmem0v1:
	case AOmem1v0:
	case AOmem1v1:

/* TODO constants */
	case AOxxx1:
	case AOxxx2:
	case AOxxx3:
	case AOxxx4:
	case AOxxx5:
	case AOxxx6:
	case AOxxx7:
	case AOxxx29:
	case AOxxx30:
	case AOxxx37:
	case AOxxx38:
	default:
		alu->err = AluInvOp;
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
		assert(rb);
		push(alu, r);
	}
}
