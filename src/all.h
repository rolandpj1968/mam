#include <assert.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef float f32;
typedef double f64;

typedef u64 v64;

typedef enum UnitT UnitT;
enum UnitT {
	AluU,
	MemU,
	CtlU,
};

typedef enum Type Type;
enum Type {
	i32t,
	i64t,
	f32t,
	f64t,
	v64t,
	vxxt,
};

typedef enum AO AO;
enum AO {
#define AO(op, t, s) AO##op,
#include "aop.h"
#undef AO
	NAOp,
};

typedef struct Op Op;
struct Op {
	UnitT unit;
	char *name;
};

typedef struct AOp AOp;
struct AOp {
	Op o;
	Type ta0;
	Type ta1;
	Type tr;
	u8 na;
	u8 nr;
};

typedef enum AluErr AluErr;
enum AluErr {
	AluNoErr,
	AluInvOp,
	AluIDiv0,
	AluNoImpl,
};

typedef struct Alu Alu;
struct Alu {
	u64 reg[4];
	u64 stk[4];
	u8 tos;
	u8 err;
};

typedef struct Mem Mem;
struct Mem {
	v64 v[2];
};

typedef union CLine CLine;
union CLine {
	u8 u8[64];
	u16 u16[32];
	u32 u32[16];
	u64 u64[8];
};

typedef struct Ctl Ctl;
struct Ctl {
	v64 ip, ip1, il, sp, bp;
	CLine ic;  /* active i-cache line */
	CLine ic0; /* next i-cache line linearly */
	CLine ic1; /* jump target i-cache line */
};	

typedef struct Mam Mam;
struct Mam {
	v64 clk;
	Alu alu[4];
	Ctl ctl;
	v64 alutos[4];
	v64 memv[2][2];
	bool trap;
	int dbg;
};

static const u8 BA0 = 1, BA1 = 2, BA2 = 3, BA3 = 4;
static const u8 BM0 = 5, BM1 = 6;
static const u8 BC = 7;

/* raw per-slot ops */
typedef struct Bundle Bundle;
struct Bundle {
	u8 op[8];
};

#define B(ao0, ao1, ao2, ao3) mkbundle(ao0, ao1, ao2, ao3, 0, 0, 0)

static const u8 IF = 0;

/* compressed format */
typedef struct Ins Ins;
struct Ins {
	u8 op[8];
};

/* util.c */
extern char* UNITS[];
extern char* TYPES[];
extern char* ALUERRS[];
void wricu8(CLine *ic, u8 noff, u8 v8);
void wricu16(CLine *ic, u8 noff, u16 v16);
Bundle mkbundle(AO ao0, AO ao1, AO ao2, AO ao3, u8 mo0, u8 mo1, u8 co0);
Bundle ins2bundle(Ins i, u8 *plen);
Ins bundle2ins(Bundle b, u8 *plen);

/* aoptab.c */
extern AOp aoptab[NAOp];

/* alu.c */
void aluexe0(Mam *mam, Alu *alu, AO o);
void aluexe1(Mam *mam, Alu *alu, AO o);
v64 alutos(Alu *alu);

/* mam.c */
void mamtick(Mam *mam, Bundle b);
v64 mamalutos(Mam *mam, u8 n);
v64 mammemv(Mam *mam, u8 n, u8 m);

/* ctl.c */
u8 ctlicu8(Ctl* ctl, u8 noff);
u16 ctlicu16(Ctl* ctl, u8 noff);
