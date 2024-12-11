typedef enum UnitT UnitT;
enum UnitT {
	AluU,
	MemU,
	CtlU,
};

static char* UNITS[] = { "Alu", "Mem", "Ctl" };

typedef enum Type Type;
enum Type {
	i32,
	i64,
	f32,
	f64,
	tx,
};

static char* TYPES[] = {"i32", "i64", "f32", "f64", "x"};

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
	Type ta;
	Type tr;
	int na;
	int nr;
};

extern AOp aoptab[NAOp];
