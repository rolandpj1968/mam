typedef enum Unit Unit;
enum UnitT {
	AluU,
	MemU,
	CtlU,
};

static char* UNITS[] = { "Alu", "Mem", "Ctl" };

typedef enum AO AO;
enum AO {
#define AO(op) AO##op,
#include "aop.h"
#undef AO
	NAOp,
};

typedef struct Op Op;
struct Op {
	int unit;
	char *name;
};

typedef struct AOp AOp;
struct AOp {
	Op o;
};

extern AOp aoptab[NAOp];
