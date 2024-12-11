typedef enum UnitT UnitT;
enum UnitT {
	AluU,
	MemU,
	CtlU,
};

extern char* UNITS[];

typedef enum Type Type;
enum Type {
	i32,
	i64,
	f32,
	f64,
	v64,
	vxx,
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
	int na;
	int nr;
};

extern AOp aoptab[NAOp];
