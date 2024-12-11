/* alu ops */

AO(nop)
AO(xxx1)
AO(xxx2)
AO(xxx3)
AO(xxx4)
AO(xxx5)
AO(xxx6)
AO(xxx7)

/* Arithmetic Binary*/

AO(iadd32)
AO(isub32)
AO(irsub32)
AO(idiv32)
AO(irem32)
AO(iudiv32)
AO(iurem32)
AO(imul32)

AO(iadd64)
AO(isub64)
AO(irsub64)
AO(idiv64)
AO(irem64)
AO(iudiv64)
AO(iurem64)
AO(imul64)
	
AO(fadd32)
AO(fsub32)
AO(frsub32)
AO(fdiv32)
AO(frem32)
AO(xxx29)
AO(xxx30)
AO(fmul32)

AO(fadd64)
AO(fsub64)
AO(frsub64)
AO(fdiv64)
AO(frem64)
AO(xxx37)
AO(xxx38)
AO(fmul64)
	
/* Arithmetic Unary */

AO(ineg32)
AO(ineg64)
AO(fneg32)
AO(fneg64)
	
/* Shift Binary */

AO(isar32)
AO(ishr32)
AO(ishl32)
AO(irotr32)

AO(isar64)
AO(ishr64)
AO(ishl64)
AO(irotr64)

/* Bits */

AO(iand32)
AO(ior32)
AO(ixor32)
AO(inot32)

AO(iand64)
AO(ior64)
AO(ixor64)
AO(inot64)

/* Comparisons */

AO(iceq32)
AO(icne32)
AO(iceq64)
AO(icne64)

AO(icsge32)
AO(icsgt32)
AO(icsle32)
AO(icslt32)
AO(icuge32)
AO(icugt32)
AO(icule32)
AO(icult32)

AO(icsge64)
AO(icsgt64)
AO(icsle64)
AO(icslt64)
AO(icuge64)
AO(icugt64)
AO(icule64)
AO(icult64)

AO(fceq32)
AO(fcge32)
AO(fcgt32)
AO(fcle32)
AO(fclt32)
AO(fcne32)
AO(fco32)
AO(fcuo32)

AO(fceq64)
AO(fcge64)
AO(fcgt64)
AO(fcle64)
AO(fclt64)
AO(fcne64)
AO(fco64)
AO(fcuo64)

/* Extensions and Truncations */

AO(i32exts8)
AO(i32extu8)
AO(i32exts16)
AO(i32extu16)
AO(i32exts32)
AO(i32extu32)

AO(i64exts8)
AO(i64extu8)
AO(i64exts16)
AO(i64extu16)
AO(i64exts32)
AO(i64extu32)

AO(fext32)
AO(ftrunc64)

AO(f32tosi32)
AO(f32toui32)
AO(f32tosi64)
AO(f32toui64)
AO(f64tosi32)
AO(f64toui32)
AO(f64tosi64)
AO(f64toui64)

AO(i32stof32)
AO(i32utof32)
AO(i64stof32)
AO(i64utof32)
AO(i32stof64)
AO(i32utof64)
AO(i64stof64)
AO(i64utof64)

/* Stack read */
AO(stk0)
AO(stk1)
AO(stk2)
AO(stk3)
	
/* Register read */
AO(reg0)
AO(reg1)
AO(reg2)
AO(reg3)
	
/* Register write popping */
AO(regp0)
AO(regp1)
AO(regp2)
AO(regp3)
	
/* Register write non-popping */
AO(regw0)
AO(regw1)
AO(regw2)
AO(regw3)

/* Remote unit TOS access */
AO(tos0)
AO(tos1)
AO(tos2)
AO(tos3)
AO(tos4)
AO(tos5)
AO(tos6)
AO(tos7)
AO(tos8)
AO(tos9)
AO(tos10)
AO(tos11)
AO(tos12)
AO(tos13)
AO(tos14)
AO(tos15)

