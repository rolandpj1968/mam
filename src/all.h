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
	AluBadOp,
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

extern u8 u8dummy;
#define I(ao0, ao1, ao2, ao3) bundle2ins(B(ao0, ao1, ao2, ao3), &u8dummy)

typedef enum CO CO;
enum CO {
#define CO(op) CO##op,
#include "cop.h"
#undef CO
	NCOp,
};

typedef struct COp COp;
struct COp {
	Op o;
};

typedef enum CtlErr CtlErr;
enum CtlErr {
	CtlNoErr,
	CtlBadIp,  /* Ip is not a memory address */
	CtlInsOvr, /* instruction overruns cache line */
	CtlHlt,
};

typedef struct Ctl Ctl;
struct Ctl {
	v64 ip, jp, il, sp, bp;
	Bundle ib; /* decoded instruction */
	CLine ic; /* active i-cache line */
	u8 err;
};

/* RAM/ROM/Device */
typedef struct Dram Dram;
struct Dram {
	bool wr; /* 1 iff writeable */
	v64 addr;
	v64 len;
	CLine *m;
};

typedef struct Mam Mam;
struct Mam {
	u8 ndram;
	Dram **dram;
	v64 clk;
	Alu alu[4];
	Ctl ctl;
	v64 alutos[4];
	v64 memv[2][2];
	bool trap;
	int dbg;
};

typedef struct EncIns EncIns;
struct EncIns {
	Bundle b;
	bool bc[4][4];
	u64 c[4][4];
};

typedef enum EncErr EncErr;
enum EncErr {
	EncNoErr,
	EncConOvr,
	EncInsOvr,
	EncInsConOvr,
};

/* util.c */
extern char* UNITS[];
extern char* TYPES[];
extern char* ALUERRS[];
extern char* CTLERRS[];
extern char* ENCERRS[];
void wricu8(CLine *ic, u8 noff, u8 v8);
void wricu16(CLine *ic, u8 noff, u16 v16);
void wricu32(CLine *ic, u8 noff, u32 v32);
void wricu64(CLine *ic, u8 noff, u64 v64);
Bundle mkbundle(AO ao0, AO ao1, AO ao2, AO ao3, u8 mo0, u8 mo1, CO co0);
Bundle ins2bundle(Ins i, u8 *plen);
Ins bundle2ins(Bundle b, u8 *plen);
void mamexeb(Mam *mam, Bundle b);
void mamexei(Mam *mam, Ins i);
EncErr encei(EncIns ei, CLine *ic, bool bc[4][4], u8* poff);
EncErr enceis(EncIns ei[], u8 nei, CLine *ic);
void dumpb(Bundle b);
void dumpei(EncIns ei);
void dumpeis(EncIns ei[], u8 nei);

/* optab.c */
extern AOp aoptab[NAOp];
extern COp coptab[NCOp];

/* alu.c */
void aluexe0(Mam *mam, Alu *alu, AO o);
void aluexe1(Mam *mam, Alu *alu, AO o);
v64 alutos(Alu *alu);

/* dram.c */
Dram *finddram(u8 ndram, Dram **dram, v64 addr);
CLine *findcline(u8 ndram, Dram **dram, v64 addr);

/* mam.c */
void mamtick(Mam *mam);
v64 mamalutos(Mam *mam, u8 n);
v64 mammemv(Mam *mam, u8 n, u8 m);

/* coptab.c */
extern COp coptab[NCOp];

/* ctl.c */
u8 ctlicu8(Ctl* ctl, u8 noff);
u16 ctlicu16(Ctl* ctl, u8 noff);
u32 ctlicu32(Ctl* ctl, u8 noff);
u64 ctlicu64(Ctl* ctl, u8 noff);
void ctlexe0(Mam *mam, Ctl *ctl);
