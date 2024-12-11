#include "all.h"

AOp aoptab[NAOp] = {
#define T(a, r) .ta = a, .tr = r
#define S(a, r) .na = a, .nr = r
#define AO(op, T, S) [AO##op]={.o = {.unit = AluU, .name = #op}, T, S},
#include "aop.h"
#undef AO
};
