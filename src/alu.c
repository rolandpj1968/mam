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

	AOp *op = &aoptab[o];

	assert(op->na <= 2);
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

	switch (o) {
	default:
		alu->err = AluInvOp;
		break;
	}

	assert(op->nr <= 1);
	if (skip)
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
