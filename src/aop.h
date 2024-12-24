/* alu ops */

/* -------- Base ISA -------- */

AO(nop,      T(vxxt,vxxt,vxxt), S(0,0))
AO(drop,     T(vxxt,vxxt,vxxt), S(0,0))
AO(inci32,   T(vxxt,vxxt,vxxt), S(0,0))
AO(deci32,   T(vxxt,vxxt,vxxt), S(0,0))
AO(inci64,   T(vxxt,vxxt,vxxt), S(0,0))
AO(deci64,   T(vxxt,vxxt,vxxt), S(0,0))
AO(inc4i32,  T(vxxt,vxxt,vxxt), S(0,0))
AO(inc8i64,  T(vxxt,vxxt,vxxt), S(0,0))

/* Integer Arithmetic XLEN width */

AO(add,      T(i64t,i64t,i64t), S(2,1))
AO(sub,      T(i64t,i64t,i64t), S(2,1))
AO(rsub,     T(i64t,i64t,i64t), S(2,1))
AO(neg,      T(i64t,vxxt,i64t), S(1,1))

/* Integer add with remote ALU tos (PREVIOUS cycle value) XLEN width */

AO(add_a0,   T(i64t,vxxt,i64t), S(1,1))
AO(add_a1,   T(i64t,vxxt,i64t), S(1,1))
AO(add_a2,   T(i64t,vxxt,i64t), S(1,1))
AO(add_a3,   T(i64t,vxxt,i64t), S(1,1))
AO(xxx28,    T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx29,    T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx30,    T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx31,    T(vxxt,vxxt,vxxt), S(0,0))

/* Shift Binary - XLEN width */

AO(sll,      T(i64t,i64t,i64t), S(2,1))
AO(srl,      T(i64t,i64t,i64t), S(2,1))
AO(sra,      T(i64t,i64t,i64t), S(2,1))
AO(xxx202,   T(vxxt,vxxt,vxxt), S(0,0))

/* Bits - XLEN width */

AO(and,      T(i64t,i64t,i64t), S(2,1))
AO(or,       T(i64t,i64t,i64t), S(2,1))
AO(xor,      T(i64t,i64t,i64t), S(2,1))
AO(not,      T(i64t,vxxt,i64t), S(1,1))

/* Comparisons - XLEN width */

AO(slt,      T(i64t,i64t,i64t), S(2,1))
AO(sltu,     T(i64t,i64t,i64t), S(2,1))
AO(seq,      T(i64t,i64t,i64t), S(2,1))
AO(xxx406,   T(vxxt,vxxt,vxxt), S(0,0))

/* Integer comparisons with remote ALU tos (PREVIOUS cycle value) XLEN width */

AO(slt_a0,   T(i64t,vxxt,i64t), S(1,1))
AO(slt_a1,   T(i64t,vxxt,i64t), S(1,1))
AO(slt_a2,   T(i64t,vxxt,i64t), S(1,1))
AO(slt_a3,   T(i64t,vxxt,i64t), S(1,1))
AO(sltu_a0,  T(i64t,vxxt,i64t), S(1,1))
AO(sltu_a1,  T(i64t,vxxt,i64t), S(1,1))
AO(sltu_a2,  T(i64t,vxxt,i64t), S(1,1))
AO(sltu_a3,  T(i64t,vxxt,i64t), S(1,1))
AO(seq_a0,   T(i64t,vxxt,i64t), S(1,1))
AO(seq_a1,   T(i64t,vxxt,i64t), S(1,1))
AO(seq_a2,   T(i64t,vxxt,i64t), S(1,1))
AO(seq_a3,   T(i64t,vxxt,i64t), S(1,1))

/* Extensions and Truncations */

AO(extb,     T(i64t,vxxt,i64t), S(1,1))
AO(extub,    T(i64t,vxxt,i64t), S(1,1))
AO(exth,     T(i64t,vxxt,i64t), S(1,1))
AO(extuh,    T(i64t,vxxt,i64t), S(1,1))

AO(extw,     T(i64t,vxxt,i64t), S(1,1))
AO(extuw,    T(i64t,vxxt,i64t), S(1,1))

/* Stack read */
AO(rd_s0,    T(vxxt,vxxt,v64t), S(0,1))
AO(rd_s1,    T(vxxt,vxxt,v64t), S(0,1))
AO(rd_s2,    T(vxxt,vxxt,v64t), S(0,1))
AO(rd_s3,    T(vxxt,vxxt,v64t), S(0,1))
AO(xxx148,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx149,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx150,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx151,   T(vxxt,vxxt,vxxt), S(0,0))

/* Register read */
AO(rd_r0,    T(vxxt,vxxt,v64t), S(0,1))
AO(rd_r1,    T(vxxt,vxxt,v64t), S(0,1))
AO(rd_r2,    T(vxxt,vxxt,v64t), S(0,1))
AO(rd_r3,    T(vxxt,vxxt,v64t), S(0,1))
AO(xxx156,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx157,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx158,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx159,   T(vxxt,vxxt,vxxt), S(0,0))

/* Register write popping */
AO(wp_r0,    T(v64t,vxxt,vxxt), S(1,0))
AO(wp_r1,    T(v64t,vxxt,vxxt), S(1,0))
AO(wp_r2,    T(v64t,vxxt,vxxt), S(1,0))
AO(wp_r3,    T(v64t,vxxt,vxxt), S(1,0))
AO(xxx164,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx165,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx166,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx167,   T(vxxt,vxxt,vxxt), S(0,0))

/* Register write non-popping */
AO(wr_r0,    T(v64t,vxxt,v64t), S(1,1))
AO(wr_r1,    T(v64t,vxxt,v64t), S(1,1))
AO(wr_r2,    T(v64t,vxxt,v64t), S(1,1))
AO(wr_r3,    T(v64t,vxxt,v64t), S(1,1))
AO(xxx172,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx173,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx174,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx175,   T(vxxt,vxxt,vxxt), S(0,0))

/* Remote alu TOS access (THIS cycle result) */
AO(rd_a0,    T(vxxt,vxxt,v64t), S(0,1))
AO(rd_a1,    T(vxxt,vxxt,v64t), S(0,1))
AO(rd_a2,    T(vxxt,vxxt,v64t), S(0,1))
AO(rd_a3,    T(vxxt,vxxt,v64t), S(0,1))
AO(xxx180,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx181,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx182,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx183,   T(vxxt,vxxt,vxxt), S(0,0))

/* (Remote) Mem unit value access (THIS cycle result) */
AO(rd_m0v0,  T(vxxt,vxxt,v64t), S(0,1))
AO(rd_m0v1,  T(vxxt,vxxt,v64t), S(0,1))
AO(rd_m1v0,  T(vxxt,vxxt,v64t), S(0,1))
AO(rd_m1v1,  T(vxxt,vxxt,v64t), S(0,1))
AO(xxx188,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx189,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx190,   T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx191,   T(vxxt,vxxt,vxxt), S(0,0))

/* Select using remote alu condition (THIS cycle value) */
AO(selz_a0,  T(v64t,v64t,v64t), S(2,1))
AO(selz_a1,  T(v64t,v64t,v64t), S(2,1))
AO(selz_a2,  T(v64t,v64t,v64t), S(2,1))
AO(selz_a3,  T(v64t,v64t,v64t), S(2,1))
AO(xxx196,   T(v64t,v64t,v64t), S(2,1))
AO(xxx197,   T(v64t,v64t,v64t), S(2,1))
AO(xxx198,   T(v64t,v64t,v64t), S(2,1))
AO(xxx199,   T(v64t,v64t,v64t), S(2,1))
AO(selnz_a0, T(v64t,v64t,v64t), S(2,1))
AO(selnz_a1, T(v64t,v64t,v64t), S(2,1))
AO(selnz_a2, T(v64t,v64t,v64t), S(2,1))
AO(selnz_a3, T(v64t,v64t,v64t), S(2,1))
AO(xxx204,   T(v64t,v64t,v64t), S(2,1))
AO(xxx205,   T(v64t,v64t,v64t), S(2,1))
AO(xxx206,   T(v64t,v64t,v64t), S(2,1))
AO(xxx207,   T(v64t,v64t,v64t), S(2,1))

/* Icache constants */

AO(conb0,    T(vxxt,vxxt,i64t), S(0,1))
AO(conb1,    T(vxxt,vxxt,i64t), S(0,1))
AO(conb2,    T(vxxt,vxxt,i64t), S(0,1))
AO(conb3,    T(vxxt,vxxt,i64t), S(0,1))
AO(conb4,    T(vxxt,vxxt,i64t), S(0,1))
AO(conb5,    T(vxxt,vxxt,i64t), S(0,1))
AO(conb6,    T(vxxt,vxxt,i64t), S(0,1))
AO(conb7,    T(vxxt,vxxt,i64t), S(0,1))
AO(conh0,    T(vxxt,vxxt,i64t), S(0,1))
AO(conh1,    T(vxxt,vxxt,i64t), S(0,1))
AO(conh2,    T(vxxt,vxxt,i64t), S(0,1))
AO(conh3,    T(vxxt,vxxt,i64t), S(0,1))
AO(conh4,    T(vxxt,vxxt,i64t), S(0,1))
AO(conh5,    T(vxxt,vxxt,i64t), S(0,1))
AO(conh6,    T(vxxt,vxxt,i64t), S(0,1))
AO(conh7,    T(vxxt,vxxt,i64t), S(0,1))
AO(conw0,    T(vxxt,vxxt,i64t), S(0,1))
AO(conw1,    T(vxxt,vxxt,i64t), S(0,1))
AO(conw2,    T(vxxt,vxxt,i64t), S(0,1))
AO(conw3,    T(vxxt,vxxt,i64t), S(0,1))
AO(conw4,    T(vxxt,vxxt,i64t), S(0,1))
AO(conw5,    T(vxxt,vxxt,i64t), S(0,1))
AO(conw6,    T(vxxt,vxxt,i64t), S(0,1))
AO(conw7,    T(vxxt,vxxt,i64t), S(0,1))

/* -------- Mul/Div Extension -------- */

AO(mul,      T(i64t,i64t,i64t), S(2,1))
AO(mulh,     T(i64t,i64t,i64t), S(2,1))
AO(mulhsu,   T(i64t,i64t,i64t), S(2,1))
AO(mulhu,    T(i64t,i64t,i64t), S(2,1))
AO(div,      T(i64t,i64t,i64t), S(2,1))
AO(rem,      T(i64t,i64t,i64t), S(2,1))
AO(divu,     T(i64t,i64t,i64t), S(2,1))
AO(remu,     T(i64t,i64t,i64t), S(2,1))

/* -------- MAM64 Extension -------- */

/* Integer Arithmetic 32-bit width */

AO(addw,     T(i32t,i32t,i32t), S(2,1))
AO(subw,     T(i32t,i32t,i32t), S(2,1))
AO(rsubw,    T(i32t,i32t,i32t), S(2,1))
AO(xxx228,   T(vxxt,vxxt,vxxt), S(0,0))

/* Integer add with remote ALU tos (PREVIOUS cycle value) 32-bit width */

AO(addw_a0,  T(i32t,vxxt,i32t), S(1,1))
AO(addw_a1,  T(i32t,vxxt,i32t), S(1,1))
AO(addw_a2,  T(i32t,vxxt,i32t), S(1,1))
AO(addw_a3,  T(i32t,vxxt,i32t), S(1,1))
AO(xxx36,    T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx37,    T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx38,    T(vxxt,vxxt,vxxt), S(0,0))
AO(xxx39,    T(vxxt,vxxt,vxxt), S(0,0))

/* Shift Binary - 32-bit width */

AO(sllw,     T(i32t,i32t,i32t), S(2,1))
AO(srlw,     T(i32t,i32t,i32t), S(2,1))
AO(sraw,     T(i32t,i32t,i32t), S(2,1))
AO(xxx402,   T(vxxt,vxxt,vxxt), S(0,0))

/* 64-bit Icache constants */
AO(cond0,    T(vxxt,vxxt,i64t), S(0,1))
AO(cond1,    T(vxxt,vxxt,i64t), S(0,1))
AO(cond2,    T(vxxt,vxxt,i64t), S(0,1))
AO(cond3,    T(vxxt,vxxt,i64t), S(0,1))
AO(cond4,    T(vxxt,vxxt,i64t), S(0,1))
AO(cond5,    T(vxxt,vxxt,i64t), S(0,1))
AO(cond6,    T(vxxt,vxxt,i64t), S(0,1))
AO(cond7,    T(vxxt,vxxt,i64t), S(0,1))

/* -------- MAM64 + Mul/Div Extension -------- */

AO(mulw,     T(i32t,i32t,i32t), S(2,1))
AO(divw,     T(i32t,i32t,i32t), S(2,1))
AO(remw,     T(i32t,i32t,i32t), S(2,1))
AO(remuw,    T(i32t,i32t,i32t), S(2,1))

