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

extern char* UNITS[];

typedef enum Type Type;
enum Type {
	i32t,
	i64t,
	f32t,
	f64t,
	v64t,
	vxxt,
};

extern char* TYPES[];

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

extern AOp aoptab[NAOp];

typedef enum AluErr AluErr;
enum AluErr {
	AluNoErr,
	AluInvOp,
	AluIDiv0,
	AluNoImpl,
};

extern char* ALUERRS[];

typedef struct Alu Alu;
struct Alu {
	u64 reg[4];
	u64 stk[4];
	u8 tos;
	u8 err;
};

typedef struct Mam Mam;
struct Mam {
};
