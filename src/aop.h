/* alu ops */

/* -------- Base ISA -------- */

AO(nop,      O(=0x00), E(Base), T(vxxt,vxxt,vxxt), S(0,0))
AO(drop,     O(     ), E(Base), T(vxxt,vxxt,vxxt), S(1,0))
AO(add1,     O(     ), E(Base), T(vxxt,vxxt,vxxt), S(0,0))
AO(sub1,     O(     ), E(Base), T(vxxt,vxxt,vxxt), S(0,0))
AO(add2,     O(     ), E(Base), T(vxxt,vxxt,vxxt), S(0,0))
AO(sub2,     O(     ), E(Base), T(vxxt,vxxt,vxxt), S(0,0))
AO(add4,     O(     ), E(Base), T(vxxt,vxxt,vxxt), S(0,0))
AO(sub4,     O(     ), E(Base), T(vxxt,vxxt,vxxt), S(0,0))

/* Integer Arithmetic XLEN width */

AO(add,      O(=0x08), E(Base), T(i64t,i64t,i64t), S(2,1))
AO(sub,      O(     ), E(Base), T(i64t,i64t,i64t), S(2,1))
AO(rsub,     O(     ), E(Base), T(i64t,i64t,i64t), S(2,1))
AO(neg,      O(     ), E(Base), T(i64t,vxxt,i64t), S(1,1))

/* Integer add with remote ALU tos (PREVIOUS cycle value) XLEN width */

AO(add_a0,   O(=0x0c), E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(add_a1,   O(     ), E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(add_a2,   O(     ), E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(add_a3,   O(     ), E(Base), T(i64t,vxxt,i64t), S(1,1))

/* Shift Binary - XLEN width */

AO(sll,      O(=0x10), E(Base), T(i64t,i64t,i64t), S(2,1))
AO(srl,      O(     ), E(Base), T(i64t,i64t,i64t), S(2,1))
AO(sra,      O(     ), E(Base), T(i64t,i64t,i64t), S(2,1))

/* Bits - XLEN width */

AO(and,      O(=0x14), E(Base), T(i64t,i64t,i64t), S(2,1))
AO(or,       O(     ), E(Base), T(i64t,i64t,i64t), S(2,1))
AO(xor,      O(     ), E(Base), T(i64t,i64t,i64t), S(2,1))
AO(not,      O(     ), E(Base), T(i64t,vxxt,i64t), S(1,1))

/* Comparisons - XLEN width */

AO(slt,      O(=0x18), E(Base), T(i64t,i64t,i64t), S(2,1))
AO(sltu,     O(     ), E(Base), T(i64t,i64t,i64t), S(2,1))
AO(seq,      O(     ), E(Base), T(i64t,i64t,i64t), S(2,1))

/* Integer comparisons with remote ALU tos (PREVIOUS cycle value) XLEN width */

AO(slt_a0,   O(=0x1c), E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(slt_a1,   O(     ), E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(slt_a2,   O(     ), E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(slt_a3,   O(     ), E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(sltu_a0,  O(     ), E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(sltu_a1,  O(     ), E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(sltu_a2,  O(     ), E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(sltu_a3,  O(     ), E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(seq_a0,   O(     ), E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(seq_a1,   O(     ), E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(seq_a2,   O(     ), E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(seq_a3,   O(     ), E(Base), T(i64t,vxxt,i64t), S(1,1))

/* Extensions and Truncations */

AO(extb,     O(=0x30), E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(extub,    O(     ), E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(exth,     O(     ), E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(extuh,    O(     ), E(Base), T(i64t,vxxt,i64t), S(1,1))

AO(extw,     O(=0x34), E(Base), T(i64t,vxxt,i64t), S(1,1))
AO(extuw,    O(     ), E(Base), T(i64t,vxxt,i64t), S(1,1))

/* Stack read */
AO(rd_s0,    O(=0x38), E(Base), T(vxxt,vxxt,v64t), S(0,1))
AO(rd_s1,    O(     ), E(Base), T(vxxt,vxxt,v64t), S(0,1))
AO(rd_s2,    O(     ), E(Base), T(vxxt,vxxt,v64t), S(0,1))
AO(rd_s3,    O(     ), E(Base), T(vxxt,vxxt,v64t), S(0,1))

/* Register read */
AO(rd_r0,    O(=0x3c), E(Base), T(vxxt,vxxt,v64t), S(0,1))
AO(rd_r1,    O(     ), E(Base), T(vxxt,vxxt,v64t), S(0,1))
AO(rd_r2,    O(     ), E(Base), T(vxxt,vxxt,v64t), S(0,1))
AO(rd_r3,    O(     ), E(Base), T(vxxt,vxxt,v64t), S(0,1))

/* Register write popping */
AO(wp_r0,    O(=0x40), E(Base), T(v64t,vxxt,vxxt), S(1,0))
AO(wp_r1,    O(     ), E(Base), T(v64t,vxxt,vxxt), S(1,0))
AO(wp_r2,    O(     ), E(Base), T(v64t,vxxt,vxxt), S(1,0))
AO(wp_r3,    O(     ), E(Base), T(v64t,vxxt,vxxt), S(1,0))

/* Register write non-popping */
AO(wr_r0,    O(=0x44), E(Base), T(v64t,vxxt,v64t), S(1,1))
AO(wr_r1,    O(     ), E(Base), T(v64t,vxxt,v64t), S(1,1))
AO(wr_r2,    O(     ), E(Base), T(v64t,vxxt,v64t), S(1,1))
AO(wr_r3,    O(     ), E(Base), T(v64t,vxxt,v64t), S(1,1))

/* Remote alu TOS access (THIS cycle result) */
AO(rd_a0,    O(=0x48), E(Base), T(vxxt,vxxt,v64t), S(0,1))
AO(rd_a1,    O(     ), E(Base), T(vxxt,vxxt,v64t), S(0,1))
AO(rd_a2,    O(     ), E(Base), T(vxxt,vxxt,v64t), S(0,1))
AO(rd_a3,    O(     ), E(Base), T(vxxt,vxxt,v64t), S(0,1))

/* (Remote) Mem unit value access (THIS cycle result) */
AO(rd_m0v0,  O(=0x4c), E(Base), T(vxxt,vxxt,v64t), S(0,1))
AO(rd_m0v1,  O(     ), E(Base), T(vxxt,vxxt,v64t), S(0,1))
AO(rd_m1v0,  O(     ), E(Base), T(vxxt,vxxt,v64t), S(0,1))
AO(rd_m1v1,  O(     ), E(Base), T(vxxt,vxxt,v64t), S(0,1))

/* Select using remote alu condition (THIS cycle value) */
AO(selz_a0,  O(=0x50), E(Base), T(v64t,v64t,v64t), S(2,1))
AO(selz_a1,  O(     ), E(Base), T(v64t,v64t,v64t), S(2,1))
AO(selz_a2,  O(     ), E(Base), T(v64t,v64t,v64t), S(2,1))
AO(selz_a3,  O(     ), E(Base), T(v64t,v64t,v64t), S(2,1))
AO(selnz_a0, O(     ), E(Base), T(v64t,v64t,v64t), S(2,1))
AO(selnz_a1, O(     ), E(Base), T(v64t,v64t,v64t), S(2,1))
AO(selnz_a2, O(     ), E(Base), T(v64t,v64t,v64t), S(2,1))
AO(selnz_a3, O(     ), E(Base), T(v64t,v64t,v64t), S(2,1))

/* Icache constants */

AO(conb0,    O(=0x60), E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conb1,    O(     ), E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conb2,    O(     ), E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conb3,    O(     ), E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conb4,    O(     ), E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conb5,    O(     ), E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conb6,    O(     ), E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conb7,    O(     ), E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conh0,    O(=0x68), E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conh1,    O(     ), E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conh2,    O(     ), E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conh3,    O(     ), E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conh4,    O(     ), E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conh5,    O(     ), E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conh6,    O(     ), E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conh7,    O(     ), E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conw0,    O(=0x70), E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conw1,    O(     ), E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conw2,    O(     ), E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conw3,    O(     ), E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conw4,    O(     ), E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conw5,    O(     ), E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conw6,    O(     ), E(Base), T(vxxt,vxxt,i64t), S(0,1))
AO(conw7,    O(     ), E(Base), T(vxxt,vxxt,i64t), S(0,1))

/* -------- MAM64 Extension -------- */

/* Integer Arithmetic 32-bit width */

AO(add8,     O(=0x80), E(64), T(vxxt,vxxt,vxxt), S(0,0))
AO(sub8,     O(     ), E(64), T(vxxt,vxxt,vxxt), S(0,0))

AO(addw,     O(=0x84), E(64), T(i32t,i32t,i32t), S(2,1))
AO(subw,     O(     ), E(64), T(i32t,i32t,i32t), S(2,1))
AO(rsubw,    O(     ), E(64), T(i32t,i32t,i32t), S(2,1))

/* Integer add with remote ALU tos (PREVIOUS cycle value) 32-bit width */

AO(addw_a0,  O(=0x88), E(64), T(i32t,vxxt,i32t), S(1,1))
AO(addw_a1,  O(     ), E(64), T(i32t,vxxt,i32t), S(1,1))
AO(addw_a2,  O(     ), E(64), T(i32t,vxxt,i32t), S(1,1))
AO(addw_a3,  O(     ), E(64), T(i32t,vxxt,i32t), S(1,1))

/* Shift Binary - 32-bit width */

AO(sllw,     O(=0x8c), E(64), T(i32t,i32t,i32t), S(2,1))
AO(srlw,     O(     ), E(64), T(i32t,i32t,i32t), S(2,1))
AO(sraw,     O(     ), E(64), T(i32t,i32t,i32t), S(2,1))

/* 64-bit Icache constants */
AO(cond0,    O(=0x90), E(64), T(vxxt,vxxt,i64t), S(0,1))
AO(cond1,    O(     ), E(64), T(vxxt,vxxt,i64t), S(0,1))
AO(cond2,    O(     ), E(64), T(vxxt,vxxt,i64t), S(0,1))
AO(cond3,    O(     ), E(64), T(vxxt,vxxt,i64t), S(0,1))
AO(cond4,    O(     ), E(64), T(vxxt,vxxt,i64t), S(0,1))
AO(cond5,    O(     ), E(64), T(vxxt,vxxt,i64t), S(0,1))
AO(cond6,    O(     ), E(64), T(vxxt,vxxt,i64t), S(0,1))
AO(cond7,    O(     ), E(64), T(vxxt,vxxt,i64t), S(0,1))

/* -------- Mul/Div Extension -------- */

AO(mul,      O(=0xa0), E(MulDiv), T(i64t,i64t,i64t), S(2,1))
AO(mulh,     O(     ), E(MulDiv), T(i64t,i64t,i64t), S(2,1))
AO(mulhsu,   O(     ), E(MulDiv), T(i64t,i64t,i64t), S(2,1))
AO(mulhu,    O(     ), E(MulDiv), T(i64t,i64t,i64t), S(2,1))
AO(div,      O(     ), E(MulDiv), T(i64t,i64t,i64t), S(2,1))
AO(rem,      O(     ), E(MulDiv), T(i64t,i64t,i64t), S(2,1))
AO(divu,     O(     ), E(MulDiv), T(i64t,i64t,i64t), S(2,1))
AO(remu,     O(     ), E(MulDiv), T(i64t,i64t,i64t), S(2,1))

/* -------- MAM64 + Mul/Div Extension -------- */

AO(mulw,     O(=0xa8), E(MulDiv64), T(i32t,i32t,i32t), S(2,1))
AO(divw,     O(     ), E(MulDiv64), T(i32t,i32t,i32t), S(2,1))
AO(remw,     O(     ), E(MulDiv64), T(i32t,i32t,i32t), S(2,1))
AO(remuw,    O(     ), E(MulDiv64), T(i32t,i32t,i32t), S(2,1))

