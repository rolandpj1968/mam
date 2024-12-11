typedef enum Unit Unit;
enum UnitT {
	AluU,
	MemU,
	CtlU,
};

static char* UNITS[] = { "Alu", "Mem", "Ctl" };

typedef struct Op Op;
struct Op {
	int op;
	int unit;
	char *name;
};

typedef enum AO AO;
enum AO {
#define AO(op) AO##op,
#include "aop.h"
	NAOp,
};
