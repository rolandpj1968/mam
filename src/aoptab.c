#include "all.h"

AOp aoptab[NAOp] = {
#define AO(op) [AO##op]={.o = {.unit = AluU, .name = #op}},
#include "aop.h"
#undef AO
};
