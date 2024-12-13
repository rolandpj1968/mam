/* alu ops */

AO(nop,      T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx1,     T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx2,     T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx3,     T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx4,     T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx5,     T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx6,     T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx7,     T(vxxt,vxxt,vxxt), S(0,0))

/* Integer Arithmetic */

AO(iadd32,   T(i32t,i32t,i32t), S(2,1))
AO(isub32,   T(i32t,i32t,i32t), S(2,1))
AO(irsub32,  T(i32t,i32t,i32t), S(2,1))
AO(idiv32,   T(i32t,i32t,i32t), S(2,1))
AO(irem32,   T(i32t,i32t,i32t), S(2,1))
AO(iudiv32,  T(i32t,i32t,i32t), S(2,1))
AO(iurem32,  T(i32t,i32t,i32t), S(2,1))
AO(imul32,   T(i32t,i32t,i32t), S(2,1))

AO(iadd64,   T(i64t,i64t,i64t), S(2,1))
AO(isub64,   T(i64t,i64t,i64t), S(2,1))
AO(irsub64,  T(i64t,i64t,i64t), S(2,1))
AO(idiv64,   T(i64t,i64t,i64t), S(2,1))
AO(irem64,   T(i64t,i64t,i64t), S(2,1))
AO(iudiv64,  T(i64t,i64t,i64t), S(2,1))
AO(iurem64,  T(i64t,i64t,i64t), S(2,1))
AO(imul64,   T(i64t,i64t,i64t), S(2,1))
	
/* Integer add with remote ALU tos - PREVIOUS cycle */

AO(iadd32r0, T(i32t,vxxt,i32t), S(1,1))
AO(iadd32r1, T(i32t,vxxt,i32t), S(1,1))
AO(iadd32r2, T(i32t,vxxt,i32t), S(1,1))
AO(iadd32r3, T(i32t,vxxt,i32t), S(1,1))
AO(iadd64r0, T(i64t,vxxt,i64t), S(1,1))
AO(iadd64r1, T(i64t,vxxt,i64t), S(1,1))
AO(iadd64r2, T(i64t,vxxt,i64t), S(1,1))
AO(iadd64r3, T(i64t,vxxt,i64t), S(1,1))

/* FP Arithmetic*/

AO(fadd32,   T(f32t,f32t,f32t), S(2,1))
AO(fsub32,   T(f32t,f32t,f32t), S(2,1))
AO(frsub32,  T(f32t,f32t,f32t), S(2,1))
AO(fdiv32,   T(f32t,f32t,f32t), S(2,1))
AO(frem32,   T(f32t,f32t,f32t), S(2,1))
AO(xxx29,    T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx30,    T(vxxt,vxxt,vxxt), S(0,0))
AO(fmul32,   T(f32t,f32t,f32t), S(2,1))

AO(fadd64,   T(f64t,f64t,f64t), S(2,1))
AO(fsub64,   T(f64t,f64t,f64t), S(2,1))
AO(frsub64,  T(f64t,f64t,f64t), S(2,1))
AO(fdiv64,   T(f64t,f64t,f64t), S(2,1))
AO(frem64,   T(f64t,f64t,f64t), S(2,1))
AO(xxx37,    T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx38,    T(vxxt,vxxt,vxxt), S(0,0))
AO(fmul64,   T(f64t,f64t,f64t), S(2,1))
	
/* Shift Binary */

AO(isar32,   T(i32t,i32t,i32t), S(2,1))
AO(ishr32,   T(i32t,i32t,i32t), S(2,1))
AO(ishl32,   T(i32t,i32t,i32t), S(2,1))
AO(irotr32,  T(i32t,i32t,i32t), S(2,1))

AO(isar64,   T(i64t,i32t,i64t), S(2,1))
AO(ishr64,   T(i64t,i32t,i64t), S(2,1))
AO(ishl64,   T(i64t,i32t,i64t), S(2,1))
AO(irotr64,  T(i64t,i32t,i64t), S(2,1))

/* Bits */

AO(iand32,   T(i32t,i32t,i32t), S(2,1))
AO(ior32,    T(i32t,i32t,i32t), S(2,1))
AO(ixor32,   T(i32t,i32t,i32t), S(2,1))
AO(inot32,   T(i32t,vxxt,i32t), S(1,1))

AO(iand64,   T(i64t,i64t,i64t), S(2,1))
AO(ior64,    T(i64t,i64t,i64t), S(2,1))
AO(ixor64,   T(i64t,i64t,i64t), S(2,1))
AO(inot64,   T(i64t,vxxt,i64t), S(1,1))

/* Arithmetic Unary */

AO(ineg32,   T(i32t,vxxt,i32t), S(1,1))
AO(ineg64,   T(i64t,vxxt,i64t), S(1,1))
AO(fneg32,   T(f32t,vxxt,f32t), S(1,1))
AO(fneg64,   T(f64t,vxxt,f64t), S(1,1))
	
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

AO(fceq32,   T(f32t,f32t,i64t), S(2,1))
AO(fcge32,   T(f32t,f32t,i64t), S(2,1))
AO(fcgt32,   T(f32t,f32t,i64t), S(2,1))
AO(fcle32,   T(f32t,f32t,i64t), S(2,1))
AO(fclt32,   T(f32t,f32t,i64t), S(2,1))
AO(fcne32,   T(f32t,f32t,i64t), S(2,1))
AO(fco32,    T(f32t,f32t,i64t), S(2,1))
AO(fcuo32,   T(f32t,f32t,i64t), S(2,1))

AO(fceq64,   T(f64t,f64t,i64t), S(2,1))
AO(fcge64,   T(f64t,f64t,i64t), S(2,1))
AO(fcgt64,   T(f64t,f64t,i64t), S(2,1))
AO(fcle64,   T(f64t,f64t,i64t), S(2,1))
AO(fclt64,   T(f64t,f64t,i64t), S(2,1))
AO(fcne64,   T(f64t,f64t,i64t), S(2,1))
AO(fco64,    T(f64t,f64t,i64t), S(2,1))
AO(fcuo64,   T(f64t,f64t,i64t), S(2,1))

/* Integer comparisons with remote ALU tos - PREVIOUS cycle */

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

AO(fext32,   T(f32t,vxxt,f64t), S(1,1))
AO(ftrunc64, T(f64t,vxxt,f32t), S(1,1))

AO(f32toi32, T(f32t,vxxt,i32t), S(1,1))
AO(f32tou32, T(f32t,vxxt,i32t), S(1,1))
AO(f32toi64, T(f32t,vxxt,i64t), S(1,1))
AO(f32tou64, T(f32t,vxxt,i64t), S(1,1))
AO(f64toi32, T(f64t,vxxt,i32t), S(1,1))
AO(f64tou32, T(f64t,vxxt,i32t), S(1,1))
AO(f64toi64, T(f64t,vxxt,i64t), S(1,1))
AO(f64tou64, T(f64t,vxxt,i64t), S(1,1))

AO(i32tof32, T(i32t,vxxt,f32t), S(1,1))
AO(u32tof32, T(i32t,vxxt,f32t), S(1,1))
AO(i64tof32, T(i64t,vxxt,f32t), S(1,1))
AO(u64tof32, T(i64t,vxxt,f32t), S(1,1))
AO(i32tof64, T(i32t,vxxt,f64t), S(1,1))
AO(u32tof64, T(i32t,vxxt,f64t), S(1,1))
AO(i64tof64, T(i64t,vxxt,f64t), S(1,1))
AO(u64tof64, T(i64t,vxxt,f64t), S(1,1))

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

/* Remote alu TOS access - THIS cycle result */
AO(alur0,    T(vxxt,vxxt,v64t), S(0,1))
AO(alur1,    T(vxxt,vxxt,v64t), S(0,1))
AO(alur2,    T(vxxt,vxxt,v64t), S(0,1))
AO(alur3,    T(vxxt,vxxt,v64t), S(0,1))

/* (Remote) Mem unit value access */
AO(mem0v0,   T(vxxt,vxxt,v64t), S(0,1))
AO(mem0v1,   T(vxxt,vxxt,v64t), S(0,1))
AO(mem1v0,   T(vxxt,vxxt,v64t), S(0,1))
AO(mem1v1,   T(vxxt,vxxt,v64t), S(0,1))

AO(xxx184,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx185,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx186,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx187,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx188,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx189,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx190,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx191,   T(vxxt,vxxt,vxxt), S(0,0))

/* Select using remote alu condition - PREVIOUS cycle */
AO(selzr0,   T(v64t,v64t,v64t), S(2,1))
AO(selzr1,   T(v64t,v64t,v64t), S(2,1))
AO(selzr2,   T(v64t,v64t,v64t), S(2,1))
AO(selzr3,   T(v64t,v64t,v64t), S(2,1))
AO(selnzr0,  T(v64t,v64t,v64t), S(2,1))
AO(selnzr1,  T(v64t,v64t,v64t), S(2,1))
AO(selnzr2,  T(v64t,v64t,v64t), S(2,1))
AO(selnzr3,  T(v64t,v64t,v64t), S(2,1))

/* Literal constants */
AO(lit0,     T(vxxt,vxxt,i64t), S(0,1))
AO(lit1,     T(vxxt,vxxt,i64t), S(0,1))
AO(lit2,     T(vxxt,vxxt,i64t), S(0,1))
AO(lit3,     T(vxxt,vxxt,i64t), S(0,1))
AO(litm1,    T(vxxt,vxxt,i64t), S(0,1))
AO(litm2,    T(vxxt,vxxt,i64t), S(0,1))
AO(litm3,    T(vxxt,vxxt,i64t), S(0,1))
AO(litm4,    T(vxxt,vxxt,i64t), S(0,1))

/* TODO 16,32,64 bit lits */

/* Icache constants */
AO(i8con0,   T(vxxt,vxxt,i64t), S(0,1))
AO(i8con1,   T(vxxt,vxxt,i64t), S(0,1))
AO(i8con2,   T(vxxt,vxxt,i64t), S(0,1))
AO(i8con3,   T(vxxt,vxxt,i64t), S(0,1))
AO(i16con0,  T(vxxt,vxxt,i64t), S(0,1))
AO(i16con1,  T(vxxt,vxxt,i64t), S(0,1))
AO(i16con2,  T(vxxt,vxxt,i64t), S(0,1))
AO(i16con3,  T(vxxt,vxxt,i64t), S(0,1))
/* AO(i32con0,  T(vxxt,vxxt,i64t), S(0,1)) */
/* AO(i32con1,  T(vxxt,vxxt,i64t), S(0,1)) */
/* AO(i32con2,  T(vxxt,vxxt,i64t), S(0,1)) */
/* AO(i32con3,  T(vxxt,vxxt,i64t), S(0,1)) */
/* AO(i64con0,  T(vxxt,vxxt,i64t), S(0,1)) */
/* AO(i64con1,  T(vxxt,vxxt,i64t), S(0,1)) */
/* AO(i64con2,  T(vxxt,vxxt,i64t), S(0,1)) */
/* AO(i64con3,  T(vxxt,vxxt,i64t), S(0,1)) */

