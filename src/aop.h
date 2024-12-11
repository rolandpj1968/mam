/* alu ops */

AO(nop,       T(vxx,vxx), S(0,0))
AO(xxx1,      T(vxx,vxx), S(0,0))
AO(xxx2,      T(vxx,vxx), S(0,0))
AO(xxx3,      T(vxx,vxx), S(0,0))
AO(xxx4,      T(vxx,vxx), S(0,0))
AO(xxx5,      T(vxx,vxx), S(0,0))
AO(xxx6,      T(vxx,vxx), S(0,0))
AO(xxx7,      T(vxx,vxx), S(0,0))

/* Arithmetic Binary*/

AO(iadd32,    T(i32,i32), S(0,0))
AO(isub32,    T(i32,i32), S(0,0))
AO(irsub32,   T(i32,i32), S(0,0))
AO(idiv32,    T(i32,i32), S(0,0))
AO(irem32,    T(i32,i32), S(0,0))
AO(iudiv32,   T(i32,i32), S(0,0))
AO(iurem32,   T(i32,i32), S(0,0))
AO(imul32,    T(i32,i32), S(0,0))

AO(iadd64,    T(i64,i64), S(0,0))
AO(isub64,    T(i64,i64), S(0,0))
AO(irsub64,   T(i64,i64), S(0,0))
AO(idiv64,    T(i64,i64), S(0,0))
AO(irem64,    T(i64,i64), S(0,0))
AO(iudiv64,   T(i64,i64), S(0,0))
AO(iurem64,   T(i64,i64), S(0,0))
AO(imul64,    T(i64,i64), S(0,0))
	
AO(fadd32,    T(f32,f32), S(0,0))
AO(fsub32,    T(f32,f32), S(0,0))
AO(frsub32,   T(f32,f32), S(0,0))
AO(fdiv32,    T(f32,f32), S(0,0))
AO(frem32,    T(f32,f32), S(0,0))
AO(xxx29,     T(vxx,vxx), S(0,0))
AO(xxx30,     T(vxx,vxx), S(0,0))
AO(fmul32,    T(f32,f32), S(0,0))

AO(fadd64,    T(f64,f64), S(0,0))
AO(fsub64,    T(f64,f64), S(0,0))
AO(frsub64,   T(f64,f64), S(0,0))
AO(fdiv64,    T(f64,f64), S(0,0))
AO(frem64,    T(f64,f64), S(0,0))
AO(xxx37,     T(vxx,vxx), S(0,0))
AO(xxx38,     T(vxx,vxx), S(0,0))
AO(fmul64,    T(f64,f64), S(0,0))
	
/* Arithmetic Unary */

AO(ineg32,    T(i32,i32), S(0,0))
AO(ineg64,    T(i64,i64), S(0,0))
AO(fneg32,    T(f32,f32), S(0,0))
AO(fneg64,    T(f64,f64), S(0,0))
	
/* Shift Binary */

AO(isar32,    T(i32,i32), S(0,0))
AO(ishr32,    T(i32,i32), S(0,0))
AO(ishl32,    T(i32,i32), S(0,0))
AO(irotr32,   T(i32,i32), S(0,0))

AO(isar64,    T(i64,i32), S(0,0))
AO(ishr64,    T(i64,i32), S(0,0))
AO(ishl64,    T(i64,i32), S(0,0))
AO(irotr64,   T(i64,i32), S(0,0))

/* Bits */

AO(iand32,    T(i32,i32), S(0,0))
AO(ior32,     T(i32,i32), S(0,0))
AO(ixor32,    T(i32,i32), S(0,0))
AO(inot32,    T(i32,i32), S(0,0))

AO(iand64,    T(i64,i64), S(0,0))
AO(ior64,     T(i64,i64), S(0,0))
AO(ixor64,    T(i64,i64), S(0,0))
AO(inot64,    T(i64,i64), S(0,0))

/* Comparisons */

AO(iceq32,    T(i32,i32), S(0,0))
AO(icne32,    T(i32,i32), S(0,0))
AO(iceq64,    T(i32,i32), S(0,0))
AO(icne64,    T(i32,i32), S(0,0))

AO(icsge32,   T(i32,i32), S(0,0))
AO(icsgt32,   T(i32,i32), S(0,0))
AO(icsle32,   T(i32,i32), S(0,0))
AO(icslt32,   T(i32,i32), S(0,0))
AO(icuge32,   T(i32,i32), S(0,0))
AO(icugt32,   T(i32,i32), S(0,0))
AO(icule32,   T(i32,i32), S(0,0))
AO(icult32,   T(i32,i32), S(0,0))

AO(icsge64,   T(i64,i64), S(0,0))
AO(icsgt64,   T(i64,i64), S(0,0))
AO(icsle64,   T(i64,i64), S(0,0))
AO(icslt64,   T(i64,i64), S(0,0))
AO(icuge64,   T(i64,i64), S(0,0))
AO(icugt64,   T(i64,i64), S(0,0))
AO(icule64,   T(i64,i64), S(0,0))
AO(icult64,   T(i64,i64), S(0,0))

AO(fceq32,    T(f32,f32), S(0,0))
AO(fcge32,    T(f32,f32), S(0,0))
AO(fcgt32,    T(f32,f32), S(0,0))
AO(fcle32,    T(f32,f32), S(0,0))
AO(fclt32,    T(f32,f32), S(0,0))
AO(fcne32,    T(f32,f32), S(0,0))
AO(fco32,     T(f32,f32), S(0,0))
AO(fcuo32,    T(f32,f32), S(0,0))

AO(fceq64,    T(f64,f64), S(0,0))
AO(fcge64,    T(f64,f64), S(0,0))
AO(fcgt64,    T(f64,f64), S(0,0))
AO(fcle64,    T(f64,f64), S(0,0))
AO(fclt64,    T(f64,f64), S(0,0))
AO(fcne64,    T(f64,f64), S(0,0))
AO(fco64,     T(f64,f64), S(0,0))
AO(fcuo64,    T(f64,f64), S(0,0))

/* Extensions and Truncations */

AO(i32exts8,  T(i32,i32), S(0,0))
AO(i32extu8,  T(i32,i32), S(0,0))
AO(i32exts16, T(i32,i32), S(0,0))
AO(i32extu16, T(i32,i32), S(0,0))

AO(i64exts8,  T(i64,i64), S(0,0))
AO(i64extu8,  T(i64,i64), S(0,0))
AO(i64exts16, T(i64,i64), S(0,0))
AO(i64extu16, T(i64,i64), S(0,0))

AO(i64exts32, T(i64,i64), S(0,0))
AO(i64extu32, T(i64,i64), S(0,0))

AO(fext32,    T(f32,f64), S(0,0))
AO(ftrunc64,  T(f64,f32), S(0,0))

AO(f32tosi32, T(f32,i32), S(0,0))
AO(f32toui32, T(f32,i32), S(0,0))
AO(f32tosi64, T(f32,i64), S(0,0))
AO(f32toui64, T(f32,i64), S(0,0))
AO(f64tosi32, T(f64,i32), S(0,0))
AO(f64toui32, T(f64,i32), S(0,0))
AO(f64tosi64, T(f64,i64), S(0,0))
AO(f64toui64, T(f64,i64), S(0,0))

AO(i32stof32, T(i32,f32), S(0,0))
AO(i32utof32, T(i32,f32), S(0,0))
AO(i64stof32, T(i64,f32), S(0,0))
AO(i64utof32, T(i64,f32), S(0,0))
AO(i32stof64, T(i32,f64), S(0,0))
AO(i32utof64, T(i32,f64), S(0,0))
AO(i64stof64, T(i64,f64), S(0,0))
AO(i64utof64, T(i64,f64), S(0,0))

/* Stack read */
AO(stk0, T(vxx,v64), S(0,0))
AO(stk1, T(vxx,v64), S(0,0))
AO(stk2, T(vxx,v64), S(0,0))
AO(stk3, T(vxx,v64), S(0,0))
	
/* Register read */
AO(reg0, T(vxx,v64), S(0,0))
AO(reg1, T(vxx,v64), S(0,0))
AO(reg2, T(vxx,v64), S(0,0))
AO(reg3, T(vxx,v64), S(0,0))
	
/* Register write popping */
AO(regp0, T(v64,vxx), S(0,0))
AO(regp1, T(v64,vxx), S(0,0))
AO(regp2, T(v64,vxx), S(0,0))
AO(regp3, T(v64,vxx), S(0,0))
	
/* Register write non-popping */
AO(regw0, T(v64,v64), S(0,0))
AO(regw1, T(v64,v64), S(0,0))
AO(regw2, T(v64,v64), S(0,0))
AO(regw3, T(v64,v64), S(0,0))

/* Remote unit TOS access */
AO(tos0, T(vxx,v64), S(0,0))
AO(tos1, T(vxx,v64), S(0,0))
AO(tos2, T(vxx,v64), S(0,0))
AO(tos3, T(vxx,v64), S(0,0))
AO(tos4, T(vxx,v64), S(0,0))
AO(tos5, T(vxx,v64), S(0,0))
AO(tos6, T(vxx,v64), S(0,0))
AO(tos7, T(vxx,v64), S(0,0))
AO(tos8, T(vxx,v64), S(0,0))
AO(tos9, T(vxx,v64), S(0,0))
AO(tos10, T(vxx,v64), S(0,0))
AO(tos11, T(vxx,v64), S(0,0))
AO(tos12, T(vxx,v64), S(0,0))
AO(tos13, T(vxx,v64), S(0,0))
AO(tos14, T(vxx,v64), S(0,0))
AO(tos15, T(vxx,v64), S(0,0))

/* TODO constants */
