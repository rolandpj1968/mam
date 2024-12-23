/* alu ops */

AO(nop,      T(vxxt,vxxt,vxxt), S(0,0))
AO(drop,     T(vxxt,vxxt,vxxt), S(0,0))
AO(inci32,   T(vxxt,vxxt,vxxt), S(0,0))
AO(deci32,   T(vxxt,vxxt,vxxt), S(0,0))
AO(inci64,   T(vxxt,vxxt,vxxt), S(0,0))
AO(deci64,   T(vxxt,vxxt,vxxt), S(0,0))
AO(inc4i32,  T(vxxt,vxxt,vxxt), S(0,0))
AO(inc8i64,  T(vxxt,vxxt,vxxt), S(0,0))

/* Integer Arithmetic XLEN width */

AO(add,      T(i32t,i32t,i32t), S(2,1))
AO(sub,      T(i32t,i32t,i32t), S(2,1))
AO(rsub,     T(i32t,i32t,i32t), S(2,1))
AO(neg,      T(i32t,vxxt,i32t), S(1,1))

/* TODO 64-bit extension Integer Arithmetic 32-bit width */

AO(addw,     T(i32t,i32t,i32t), S(2,1))
AO(subw,     T(i32t,i32t,i32t), S(2,1))
AO(rsubw,    T(i32t,i32t,i32t), S(2,1))
AO(xxx228,   T(vxxt,vxxt,vxxt), S(0,0))

/* TODO - mul/div extension XLEN WIDTH */

AO(mul,      T(i32t,i32t,i32t), S(2,1))
AO(mulh,     T(i32t,i32t,i32t), S(2,1))
AO(mulhsu,   T(i32t,i32t,i32t), S(2,1))
AO(mulhu,    T(i32t,i32t,i32t), S(2,1))
AO(div,      T(i32t,i32t,i32t), S(2,1))
AO(rem,      T(i32t,i32t,i32t), S(2,1))
AO(divu,     T(i32t,i32t,i32t), S(2,1))
AO(remu,     T(i32t,i32t,i32t), S(2,1))

/* TODO - 64-bit mul/div extension 32-bit width */

AO(mulw,     T(i64t,i64t,i64t), S(2,1))
AO(divw,     T(i64t,i64t,i64t), S(2,1))
AO(remw,     T(i64t,i64t,i64t), S(2,1))
AO(remuw,    T(i64t,i64t,i64t), S(2,1))

/* Integer add with remote ALU tos (PREVIOUS cycle value) XLEN width */

AO(add.a0,   T(i32t,vxxt,i32t), S(1,1))
AO(add.a1,   T(i32t,vxxt,i32t), S(1,1))
AO(add.a2,   T(i32t,vxxt,i32t), S(1,1))
AO(add.a3,   T(i32t,vxxt,i32t), S(1,1))
AO(xxx28,    T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx29,    T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx30,    T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx31,    T(vxxt,vxxt,vxxt), S(0,0))

/* TODO  64-bit extension / Integer add with remote ALU tos (PREVIOUS cycle value) 32-bit width */

AO(addw.a0,  T(i64t,vxxt,i64t), S(1,1))
AO(addw.a1,  T(i64t,vxxt,i64t), S(1,1))
AO(addw.a2,  T(i64t,vxxt,i64t), S(1,1))
AO(addw.a3,  T(i64t,vxxt,i64t), S(1,1))
AO(xxx36,    T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx37,    T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx38,    T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx39,    T(vxxt,vxxt,vxxt), S(0,0))

/* Shift Binary - XLEN width */

AO(sll,      T(i32t,i32t,i32t), S(2,1))
AO(srl,      T(i32t,i32t,i32t), S(2,1))
AO(sra,      T(i32t,i32t,i32t), S(2,1))
AO(xxx202,   T(vxxt,vxxt,vxxt), S(0,0))

/* TODO  64-bit extension / Shift Binary - 32-bit width */

AO(sllw,     T(i32t,i32t,i32t), S(2,1))
AO(srlw,     T(i32t,i32t,i32t), S(2,1))
AO(sraw,     T(i32t,i32t,i32t), S(2,1))
AO(xxx402,   T(vxxt,vxxt,vxxt), S(0,0))

/* Bits - XLEN width */

AO(and,      T(i32t,i32t,i32t), S(2,1))
AO(or,       T(i32t,i32t,i32t), S(2,1))
AO(xor,      T(i32t,i32t,i32t), S(2,1))
AO(not,      T(i32t,vxxt,i32t), S(1,1))

/* Comparisons */

AO(iceq32,   T(i32t,i32t,i64t), S(2,1))
AO(icne32,   T(i32t,i32t,i64t), S(2,1))
AO(iceq64,   T(i64t,i64t,i64t), S(2,1))
AO(icne64,   T(i64t,i64t,i64t), S(2,1))

AO(icsge32,  T(i32t,i32t,i64t), S(2,1))
AO(icsgt32,  T(i32t,i32t,i64t), S(2,1))
AO(icsle32,  T(i32t,i32t,i64t), S(2,1))
AO(icslt32,  T(i32t,i32t,i64t), S(2,1))
AO(icuge32,  T(i32t,i32t,i64t), S(2,1))
AO(icugt32,  T(i32t,i32t,i64t), S(2,1))
AO(icule32,  T(i32t,i32t,i64t), S(2,1))
AO(icult32,  T(i32t,i32t,i64t), S(2,1))

AO(icsge64,  T(i64t,i64t,i64t), S(2,1))
AO(icsgt64,  T(i64t,i64t,i64t), S(2,1))
AO(icsle64,  T(i64t,i64t,i64t), S(2,1))
AO(icslt64,  T(i64t,i64t,i64t), S(2,1))
AO(icuge64,  T(i64t,i64t,i64t), S(2,1))
AO(icugt64,  T(i64t,i64t,i64t), S(2,1))
AO(icule64,  T(i64t,i64t,i64t), S(2,1))
AO(icult64,  T(i64t,i64t,i64t), S(2,1))

/* Integer comparisons with remote ALU tos (PREVIOUS cycle value) */
/* no op space for r4-7 */

AO(iceq32r0, T(i32t,vxxt,i64t), S(1,1))
AO(iceq32r1, T(i32t,vxxt,i64t), S(1,1))
AO(iceq32r2, T(i32t,vxxt,i64t), S(1,1))
AO(iceq32r3, T(i32t,vxxt,i64t), S(1,1))
AO(iceq64r0, T(i64t,vxxt,i64t), S(1,1))
AO(iceq64r1, T(i64t,vxxt,i64t), S(1,1))
AO(iceq64r2, T(i64t,vxxt,i64t), S(1,1))
AO(iceq64r3, T(i64t,vxxt,i64t), S(1,1))
AO(iclt32r0, T(i32t,vxxt,i64t), S(1,1))
AO(iclt32r1, T(i32t,vxxt,i64t), S(1,1))
AO(iclt32r2, T(i32t,vxxt,i64t), S(1,1))
AO(iclt32r3, T(i32t,vxxt,i64t), S(1,1))
AO(iclt64r0, T(i64t,vxxt,i64t), S(1,1))
AO(iclt64r1, T(i64t,vxxt,i64t), S(1,1))
AO(iclt64r2, T(i64t,vxxt,i64t), S(1,1))
AO(iclt64r3, T(i64t,vxxt,i64t), S(1,1))

/* Extensions and Truncations */

AO(exts8,    T(i64t,vxxt,i64t), S(1,1))
AO(extu8,    T(i64t,vxxt,i64t), S(1,1))
AO(exts16,   T(i64t,vxxt,i64t), S(1,1))
AO(extu16,   T(i64t,vxxt,i64t), S(1,1))

AO(exts32,   T(i64t,vxxt,i64t), S(1,1))
AO(extu32,   T(i64t,vxxt,i64t), S(1,1))

/* Stack read */
AO(stk0,     T(vxxt,vxxt,v64t), S(0,1))
AO(stk1,     T(vxxt,vxxt,v64t), S(0,1))
AO(stk2,     T(vxxt,vxxt,v64t), S(0,1))
AO(stk3,     T(vxxt,vxxt,v64t), S(0,1))
AO(xxx148,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx149,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx150,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx151,   T(vxxt,vxxt,vxxt), S(0,0))

/* Register read */
AO(reg0,     T(vxxt,vxxt,v64t), S(0,1))
AO(reg1,     T(vxxt,vxxt,v64t), S(0,1))
AO(reg2,     T(vxxt,vxxt,v64t), S(0,1))
AO(reg3,     T(vxxt,vxxt,v64t), S(0,1))
AO(xxx156,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx157,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx158,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx159,   T(vxxt,vxxt,vxxt), S(0,0))

/* Register write popping */
AO(regp0,    T(v64t,vxxt,vxxt), S(1,0))
AO(regp1,    T(v64t,vxxt,vxxt), S(1,0))
AO(regp2,    T(v64t,vxxt,vxxt), S(1,0))
AO(regp3,    T(v64t,vxxt,vxxt), S(1,0))
AO(xxx164,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx165,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx166,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx167,   T(vxxt,vxxt,vxxt), S(0,0))

/* Register write non-popping */
AO(regw0,    T(v64t,vxxt,v64t), S(1,1))
AO(regw1,    T(v64t,vxxt,v64t), S(1,1))
AO(regw2,    T(v64t,vxxt,v64t), S(1,1))
AO(regw3,    T(v64t,vxxt,v64t), S(1,1))
AO(xxx172,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx173,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx174,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx175,   T(vxxt,vxxt,vxxt), S(0,0))

/* Remote alu TOS access (THIS cycle result) */
AO(alur0,    T(vxxt,vxxt,v64t), S(0,1))
AO(alur1,    T(vxxt,vxxt,v64t), S(0,1))
AO(alur2,    T(vxxt,vxxt,v64t), S(0,1))
AO(alur3,    T(vxxt,vxxt,v64t), S(0,1))
AO(xxx180,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx181,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx182,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx183,   T(vxxt,vxxt,vxxt), S(0,0))

/* (Remote) Mem unit value access (THIS cycle result) */
AO(mem0v0,   T(vxxt,vxxt,v64t), S(0,1))
AO(mem0v1,   T(vxxt,vxxt,v64t), S(0,1))
AO(mem1v0,   T(vxxt,vxxt,v64t), S(0,1))
AO(mem1v1,   T(vxxt,vxxt,v64t), S(0,1))
AO(xxx188,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx189,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx190,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx191,   T(vxxt,vxxt,vxxt), S(0,0))

/* Select using remote alu condition (PREVIOUS cycle value) */
AO(selzr0,   T(v64t,v64t,v64t), S(2,1))
AO(selzr1,   T(v64t,v64t,v64t), S(2,1))
AO(selzr2,   T(v64t,v64t,v64t), S(2,1))
AO(selzr3,   T(v64t,v64t,v64t), S(2,1))
AO(xxx196,   T(v64t,v64t,v64t), S(2,1))
AO(xxx197,   T(v64t,v64t,v64t), S(2,1))
AO(xxx198,   T(v64t,v64t,v64t), S(2,1))
AO(xxx199,   T(v64t,v64t,v64t), S(2,1))
AO(selnzr0,  T(v64t,v64t,v64t), S(2,1))
AO(selnzr1,  T(v64t,v64t,v64t), S(2,1))
AO(selnzr2,  T(v64t,v64t,v64t), S(2,1))
AO(selnzr3,  T(v64t,v64t,v64t), S(2,1))
AO(xxx204,   T(v64t,v64t,v64t), S(2,1))
AO(xxx205,   T(v64t,v64t,v64t), S(2,1))
AO(xxx206,   T(v64t,v64t,v64t), S(2,1))
AO(xxx207,   T(v64t,v64t,v64t), S(2,1))

/* Icache constants */

AO(i8con0,   T(vxxt,vxxt,i64t), S(0,1))
AO(i8con1,   T(vxxt,vxxt,i64t), S(0,1))
AO(i8con2,   T(vxxt,vxxt,i64t), S(0,1))
AO(i8con3,   T(vxxt,vxxt,i64t), S(0,1))
AO(i8con4,   T(vxxt,vxxt,i64t), S(0,1))
AO(i8con5,   T(vxxt,vxxt,i64t), S(0,1))
AO(i8con6,   T(vxxt,vxxt,i64t), S(0,1))
AO(i8con7,   T(vxxt,vxxt,i64t), S(0,1))
AO(i16con0,  T(vxxt,vxxt,i64t), S(0,1))
AO(i16con1,  T(vxxt,vxxt,i64t), S(0,1))
AO(i16con2,  T(vxxt,vxxt,i64t), S(0,1))
AO(i16con3,  T(vxxt,vxxt,i64t), S(0,1))
AO(i16con4,  T(vxxt,vxxt,i64t), S(0,1))
AO(i16con5,  T(vxxt,vxxt,i64t), S(0,1))
AO(i16con6,  T(vxxt,vxxt,i64t), S(0,1))
AO(i16con7,  T(vxxt,vxxt,i64t), S(0,1))
AO(i32con0,  T(vxxt,vxxt,i64t), S(0,1))
AO(i32con1,  T(vxxt,vxxt,i64t), S(0,1))
AO(i32con2,  T(vxxt,vxxt,i64t), S(0,1))
AO(i32con3,  T(vxxt,vxxt,i64t), S(0,1))
AO(i32con4,  T(vxxt,vxxt,i64t), S(0,1))
AO(i32con5,  T(vxxt,vxxt,i64t), S(0,1))
AO(i32con6,  T(vxxt,vxxt,i64t), S(0,1))
AO(i32con7,  T(vxxt,vxxt,i64t), S(0,1))
AO(i64con0,  T(vxxt,vxxt,i64t), S(0,1))
AO(i64con1,  T(vxxt,vxxt,i64t), S(0,1))
AO(i64con2,  T(vxxt,vxxt,i64t), S(0,1))
AO(i64con3,  T(vxxt,vxxt,i64t), S(0,1))
AO(i64con4,  T(vxxt,vxxt,i64t), S(0,1))
AO(i64con5,  T(vxxt,vxxt,i64t), S(0,1))
AO(i64con6,  T(vxxt,vxxt,i64t), S(0,1))
AO(i64con7,  T(vxxt,vxxt,i64t), S(0,1))
