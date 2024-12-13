#include "all.h"

AOp aoptab[NAOp] = {
#define T(a0, a1, r) .ta0 = a0, .ta1 = a1, .tr = r
#define S(a, r) .na = a, .nr = r
#define AO(op, T, S) [AO##op]={.o = {.unit = AluU, .name = #op}, T, S},
#include "aop.h"
#undef AO
};

COp coptab[NCOp] = {
#define CO(op) [CO##op]={.o = {.unit = CtlU, .name = #op}},
#include "cop.h"
#undef CO
};
