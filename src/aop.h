/* alu ops */

/* -------- Base ISA -------- */

AO(nop,      E(Base), T(vxxt,vxxt,vxxt), S(0,0))
AO(drop,     E(Base), T(vxxt,vxxt,vxxt), S(1,0))
AO(add1,     E(Base), T(vxxt,vxxt,vxxt), S(0,0))
AO(sub1,     E(Base), T(vxxt,vxxt,vxxt), S(0,0))
AO(add2,     E(Base), T(vxxt,vxxt,vxxt), S(0,0))
AO(sub2,     E(Base), T(vxxt,vxxt,vxxt), S(0,0))
AO(add4,     E(Base), T(vxxt,vxxt,vxxt), S(0,0))
AO(sub4,     E(Base), T(vxxt,vxxt,vxxt), S(0,0))

/* Integer Arithmetic XLEN width */

AO(add,      E(Base), T(i64t,i64t,i64t), S(2,1))
AO(sub,      E(Base), T(i64t,i64t,i64t), S(2,1))
AO(rsub,     E(Base), T(i64t,i64t,i64t), S(2,1))
AO(neg,      E(Base), T(i64t,vxxt,i64t), S(1,1))

/* Integer add with remote ALU tos (PREVIOUS cycle value) XLEN width */

AO(add_a0,   E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(add_a1,   E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(add_a2,   E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(add_a3,   E(Base), T(i64t,vxxt,i64t), S(1,1))

/* Shift Binary - XLEN width */

AO(sll,      E(Base), T(i64t,i64t,i64t), S(2,1))
AO(srl,      E(Base), T(i64t,i64t,i64t), S(2,1))
AO(sra,      E(Base), T(i64t,i64t,i64t), S(2,1))

/* Bits - XLEN width */

AO(and,      E(Base), T(i64t,i64t,i64t), S(2,1))
AO(or,       E(Base), T(i64t,i64t,i64t), S(2,1))
AO(xor,      E(Base), T(i64t,i64t,i64t), S(2,1))
AO(not,      E(Base), T(i64t,vxxt,i64t), S(1,1))

/* Comparisons - XLEN width */

AO(slt,      E(Base), T(i64t,i64t,i64t), S(2,1))
AO(sltu,     E(Base), T(i64t,i64t,i64t), S(2,1))
AO(seq,      E(Base), T(i64t,i64t,i64t), S(2,1))

/* Integer comparisons with remote ALU tos (PREVIOUS cycle value) XLEN width */

AO(slt_a0,   E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(slt_a1,   E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(slt_a2,   E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(slt_a3,   E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(sltu_a0,  E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(sltu_a1,  E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(sltu_a2,  E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(sltu_a3,  E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(seq_a0,   E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(seq_a1,   E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(seq_a2,   E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(seq_a3,   E(Base), T(i64t,vxxt,i64t), S(1,1))

/* Extensions and Truncations */

AO(extb,     E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(extub,    E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(exth,     E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(extuh,    E(Base), T(i64t,vxxt,i64t), S(1,1))

AO(extw,     E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(extuw,    E(Base), T(i64t,vxxt,i64t), S(1,1))

/* Stack read */
AO(rd_s0,    E(Base), T(vxxt,vxxt,v64t), S(0,1))
AO(rd_s1,    E(Base), T(vxxt,vxxt,v64t), S(0,1))
AO(rd_s2,    E(Base), T(vxxt,vxxt,v64t), S(0,1))
AO(rd_s3,    E(Base), T(vxxt,vxxt,v64t), S(0,1))

/* Register read */
AO(rd_r0,    E(Base), T(vxxt,vxxt,v64t), S(0,1))
AO(rd_r1,    E(Base), T(vxxt,vxxt,v64t), S(0,1))
AO(rd_r2,    E(Base), T(vxxt,vxxt,v64t), S(0,1))
AO(rd_r3,    E(Base), T(vxxt,vxxt,v64t), S(0,1))

/* Register write popping */
AO(wp_r0,    E(Base), T(v64t,vxxt,vxxt), S(1,0))
AO(wp_r1,    E(Base), T(v64t,vxxt,vxxt), S(1,0))
AO(wp_r2,    E(Base), T(v64t,vxxt,vxxt), S(1,0))
AO(wp_r3,    E(Base), T(v64t,vxxt,vxxt), S(1,0))

/* Register write non-popping */
AO(wr_r0,    E(Base), T(v64t,vxxt,v64t), S(1,1))
AO(wr_r1,    E(Base), T(v64t,vxxt,v64t), S(1,1))
AO(wr_r2,    E(Base), T(v64t,vxxt,v64t), S(1,1))
AO(wr_r3,    E(Base), T(v64t,vxxt,v64t), S(1,1))

/* Remote alu TOS access (THIS cycle result) */
AO(rd_a0,    E(Base), T(vxxt,vxxt,v64t), S(0,1))
AO(rd_a1,    E(Base), T(vxxt,vxxt,v64t), S(0,1))
AO(rd_a2,    E(Base), T(vxxt,vxxt,v64t), S(0,1))
AO(rd_a3,    E(Base), T(vxxt,vxxt,v64t), S(0,1))

/* (Remote) Mem unit value access (THIS cycle result) */
AO(rd_m0v0,  E(Base), T(vxxt,vxxt,v64t), S(0,1))
AO(rd_m0v1,  E(Base), T(vxxt,vxxt,v64t), S(0,1))
AO(rd_m1v0,  E(Base), T(vxxt,vxxt,v64t), S(0,1))
AO(rd_m1v1,  E(Base), T(vxxt,vxxt,v64t), S(0,1))

/* Select using remote alu condition (THIS cycle value) */
AO(selz_a0,  E(Base), T(v64t,v64t,v64t), S(2,1))
AO(selz_a1,  E(Base), T(v64t,v64t,v64t), S(2,1))
AO(selz_a2,  E(Base), T(v64t,v64t,v64t), S(2,1))
AO(selz_a3,  E(Base), T(v64t,v64t,v64t), S(2,1))
AO(selnz_a0, E(Base), T(v64t,v64t,v64t), S(2,1))
AO(selnz_a1, E(Base), T(v64t,v64t,v64t), S(2,1))
AO(selnz_a2, E(Base), T(v64t,v64t,v64t), S(2,1))
AO(selnz_a3, E(Base), T(v64t,v64t,v64t), S(2,1))

/* Icache constants */

AO(conb0,    E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conb1,    E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conb2,    E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conb3,    E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conb4,    E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conb5,    E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conb6,    E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conb7,    E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conh0,    E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conh1,    E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conh2,    E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conh3,    E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conh4,    E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conh5,    E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conh6,    E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conh7,    E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conw0,    E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conw1,    E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conw2,    E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conw3,    E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conw4,    E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conw5,    E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conw6,    E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conw7,    E(Base), T(vxxt,vxxt,i64t), S(0,1))

/* -------- MAM64 Extension -------- */

/* Integer Arithmetic 32-bit width */

AO(addw,     E(64), T(i32t,i32t,i32t), S(2,1))
AO(subw,     E(64), T(i32t,i32t,i32t), S(2,1))
AO(rsubw,    E(64), T(i32t,i32t,i32t), S(2,1))

/* Integer add with remote ALU tos (PREVIOUS cycle value) 32-bit width */

AO(addw_a0,  E(64), T(i32t,vxxt,i32t), S(1,1))
AO(addw_a1,  E(64), T(i32t,vxxt,i32t), S(1,1))
AO(addw_a2,  E(64), T(i32t,vxxt,i32t), S(1,1))
AO(addw_a3,  E(64), T(i32t,vxxt,i32t), S(1,1))

/* Shift Binary - 32-bit width */

AO(sllw,     E(64), T(i32t,i32t,i32t), S(2,1))
AO(srlw,     E(64), T(i32t,i32t,i32t), S(2,1))
AO(sraw,     E(64), T(i32t,i32t,i32t), S(2,1))

/* 64-bit Icache constants */
AO(cond0,    E(64), T(vxxt,vxxt,i64t), S(0,1))
AO(cond1,    E(64), T(vxxt,vxxt,i64t), S(0,1))
AO(cond2,    E(64), T(vxxt,vxxt,i64t), S(0,1))
AO(cond3,    E(64), T(vxxt,vxxt,i64t), S(0,1))
AO(cond4,    E(64), T(vxxt,vxxt,i64t), S(0,1))
AO(cond5,    E(64), T(vxxt,vxxt,i64t), S(0,1))
AO(cond6,    E(64), T(vxxt,vxxt,i64t), S(0,1))
AO(cond7,    E(64), T(vxxt,vxxt,i64t), S(0,1))

/* -------- Mul/Div Extension -------- */

AO(mul,      E(MulDiv), T(i64t,i64t,i64t), S(2,1))
AO(mulh,     E(MulDiv), T(i64t,i64t,i64t), S(2,1))
AO(mulhsu,   E(MulDiv), T(i64t,i64t,i64t), S(2,1))
AO(mulhu,    E(MulDiv), T(i64t,i64t,i64t), S(2,1))
AO(div,      E(MulDiv), T(i64t,i64t,i64t), S(2,1))
AO(rem,      E(MulDiv), T(i64t,i64t,i64t), S(2,1))
AO(divu,     E(MulDiv), T(i64t,i64t,i64t), S(2,1))
AO(remu,     E(MulDiv), T(i64t,i64t,i64t), S(2,1))

/* -------- MAM64 + Mul/Div Extension -------- */

AO(mulw,     E(MulDiv64), T(i32t,i32t,i32t), S(2,1))
AO(divw,     E(MulDiv64), T(i32t,i32t,i32t), S(2,1))
AO(remw,     E(MulDiv64), T(i32t,i32t,i32t), S(2,1))
AO(remuw,    E(MulDiv64), T(i32t,i32t,i32t), S(2,1))

