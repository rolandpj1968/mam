/* place-holder for now */

/* FP Arithmetic*/

AO(fadd32,   T(f32t,f32t,f32t), S(2,1))
AO(fsub32,   T(f32t,f32t,f32t), S(2,1))
AO(frsub32,  T(f32t,f32t,f32t), S(2,1))
AO(fdiv32,   T(f32t,f32t,f32t), S(2,1))
AO(frem32,   T(f32t,f32t,f32t), S(2,1))
AO(xxx45,    T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx46,    T(vxxt,vxxt,vxxt), S(0,0))
AO(fmul32,   T(f32t,f32t,f32t), S(2,1))

AO(fadd64,   T(f64t,f64t,f64t), S(2,1))
AO(fsub64,   T(f64t,f64t,f64t), S(2,1))
AO(frsub64,  T(f64t,f64t,f64t), S(2,1))
AO(fdiv64,   T(f64t,f64t,f64t), S(2,1))
AO(frem64,   T(f64t,f64t,f64t), S(2,1))
AO(xxx53,    T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx54,    T(vxxt,vxxt,vxxt), S(0,0))
AO(fmul64,   T(f64t,f64t,f64t), S(2,1))

/* Arithmetic Unary */

AO(fneg32,   T(f32t,vxxt,f32t), S(1,1))
AO(fneg64,   T(f64t,vxxt,f64t), S(1,1))

/* FP Comparisons */

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

/* FP conversions */

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

