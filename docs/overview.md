# Multi-Accumulator Machine

## Introduction

The multi-accumulator machine (*MAM*) is an machine- and *instruction set architecture* (ISA) that fits into the general category of explicitly-parallel VLIW machines. MAM goes somewhat further than typical VLIW architectures and ISA's by directly driving multiple mostly-independent execution units from execution-unit-specific (sub-)operations within a single *instruction*. Each (hardware) execution unit is driven by a specific *slot* in the (long) instruction. Each slot within the instruction 'word' is 8 bits; the instruction comprises a collection of these 8-bit operations and the semantics of instruction execution is that all (non-NOP) operations in the instruction word are executed in parallel.

In general a specific MAM *model* comprises a particular collection of execution units of various types - a typical model would include some number of *arithmetic* units, some *memory* (load/store) units and a *flow-control* (branch/call et al) unit.

In order to minimise machine code bloat the execution units and corresponding operation set(s) are exposed as *accumulator* machines - all operations use an implicit 'accumulator' register operand (and possibly one or more other implicit/explicit operands) and all results are written back to the implicit accumulator register. This architectural decision is made deliberately in order to fit a useful set of operations within 8 bits of per-execution-unit operand, allowing many separate execution units to be driven from a relatively reasonable 64-bit (up to 8 parallel execution units) or 128-bit (up to 16 parallel execution units) instruction word size.

In addition, MAM also goes further than typical VLIW architectures in that each execution unit is (almost) entirely self-contained and independent. For example each arithmentic execution unit includes its own register set, and execution unit state - registers, flags - are not directly visible from other execution units. Instead, values are explicitly transfered between execution units as and when required. While this does introduce some extra operations, as does the accumulator approach, the intent is to throw enough parallel execution units at the problem to achieve useful instruction/operation throughput.

As is typical with VLIW architectures, MAM strongly encourages conditional and/or speculative execution in preference to branching. MAM memory units support *conditional* and *speculative* memory loads and stores. Conditional reads and writes are exactly analogous to conditional (register) move instructions (or more generally ubiquitous conditional instruction sets like ARM32). On the other hand speculative memory loads (reads) allow memory load instructions to be hoisted above potentially conflicting (i.e. overwriting) memory store instructions, and speculative memory stores (writes) use a local write buffer to provide a special 'speculative' view of memory by one or some of the memory units, which can be discarded/abandoned subsequently if the speculative path is not actually taken. All of this will be elaborated substantially below.

On the other hand, MAM is intended to be (sensibly) implemented as a (very) shallow pipeline architecture - it is intended that almost all execution unit operations complete in a single clock cycle. Accordingly, all operations that do not complete in a single clock cycle are split into *start-op* and *complete-op* instruction operations. The *start-op* operations initiate an async operation - for example integer divide - and are non-blocking. On the other hand *complete-op* operations will stall until the operation result is actually available - note that this of course stalls the entire instruction stream so all execution units need to wait for the the stalling operation to complete. One special example of an *async* operation in the MAM architecture is memory load in the memory unit(s). Like other cases of multi-clock-cycle- or variable-clock-cycle operations, memory read operations in the memory unit(s) are split into *start-read* and *complete-read* instruction operations, where the semantics is that the *complete-read* operation defines the memory state viewpoint of the read. In this sense *start-read* is speculative and allows memory reads to be hoisted even above potentially conflicting/overwriting memory write operations in order to absorb the natural latency of the memory cache hierarchy. Again, this will be elaborated further below.

In summary, the Multi-Accumulator Machine (MAM) is an explicitly parallel very-wide VLIW implementation with very simple instruction decoding, (almost) independent execution units, no data/register hazards, a dense instruction encoding format even with very wide parallelism and deliberate support for conditional and speculative execution. As such it is intended to provide high general-purpose performance with a very simple and low power circuit design - no out-of-order, no register-rewriting, mostly-avoidance of branch prediction through speculative execution support. Like all explicitly-parallel architectures (and even explicitly-speculative architectures - are there any?), good compiler support is absolutely critical to effective performance in practice.

## MAM Instruction Encoding

As described in the [Introduction](#introduction), each MAM instruction comprises an ordered collection of operations including one operation for each execution unit of the specific MAM *model*. For expository purposes we will assume a MAM model comprising eight (8) *arithmetic units*, four (4) *memory units* and a single *control unit* for a total of thirteen (13) execution units. This choice of execution units is somewhat deliberate as will become clearer in the following. It should be clear that the MAM specification is not prescriptive about possible models - in this sense MAM can be seen as a framework for defining a family of related CPU architectures. For example, we could also choose to implement a minimal MAM model comprising one (1) arithmetic unit, one (1) memory unit and one (1) control unit. In general a MAM model *MUST* include at least one arithmetic unit, at least one memory unit and exactly one control unit.

Although the MAM specification is not prescriptive, a MAM model can include idle *padding units* in the instruction format in order that the instruction word length is aligned to natural machine word lengths - typically a power of two. For our expository example comprising thirteen execution units in total we will choose to pad each instruction to exactly sixteen slots. Note that each slot is eight bits wide, hence our instruction word is 128-bits. We can denote this MAM model as *MAM/8a/4m/16* for short - it is not necessary to include the control unit since there is always exactly one in all (valid or useful) MAM models.

Again to reiterate, each byte of the instruction word contains an operation for a specific execution unit where there is fixed mapping from byte index in the instruction word to execution unit. Phrased differently, a specific byte position in any MAM instruction will always drive the same execution unit. As mentioned previously each byte position is alternatively known as a(n instruction) *slot* and slightly more loosely the *slot* number will refer to the instruction operation position as well as the corresponding execution unit. Taking our expository MAM/8a/4m/16 model, in order to exactly characterise the model we additionally need to specify exactly which execution unit is driven by each slot. For reasons that will become more apparent in the following we will choose to lay out our slots so that the first half of the instruction word comprises exactly four (4) arithmetic units, two (2) memory units, the control unit and a padding unit. Hence slots zero - note zero based numbering - through three will be arithmetic units, slots four and five are memory units, slot six is the control unit and slot seven is an idle padding slot. The remaining execution units are then assigned to slots eight through eleven (remaining arithmetic units), slots twelve and thirteen (memory units) and two remaining padding slots, fourteen and fifteen. We will similarly denote this specific slot layout choice as *MAM/4a/2m/c/./4a/2m/2./16*. Note that we have described our MAM model as both MAM/8a/4m/16 and MAM/4a/2m/c/./4a/2m/2./16 and it is assumed that context will make it clear whether the model characterisation includes slot layout or not.

Finally, although we have not yet elaborated the 8-bit operation sets for each kind of execution unit, it should be clear that the (binary) machine code instruction format is simply the per-slot 8-bit operations collected into a long instruction word. Slot 0 is driven by the lowest memory-address byte of the instruction, slot 1 is driven by the second lowest memory-address byte, etc. - in other words the instruction encoding follows the architecture's endianness. Padding units *SHOULD* always use 0x00, the zero byte, as their slot operation; similarly the zero byte 0x00 is used in all active execution unit types as the *no-operation* (NOP) operation code. As is common practice in machine code text representation we use a sequence of hexadecimal byte values to represent a MAM instruction in order from slot 0 upwards.

For example, here is a typical machine code representation of an instruction sequence for our *MAM/4a/2m/c/./4a/2m/2./16* model, with memory address on the left:

```
0x0000100000: 01 FA 00 3D 00 3B 00 00 E2 00 00 00 00 12 00 00
0x0000100010: 02 3A 00 00 2B 00 00 00 00 00 00 00 00 00 00 00
0x0000100020: 23 3A 00 00 2A 00 F0 00 00 00 00 00 00 00 00 00
```

At this point of the document we have not defined op-codes other than NOP (00) for any of the execution unit types. However, we can make some high-level observations about the various execution units' activity in this sequence of instructions. Firstly slots 0 to 3 (leftmost bytes in each instruction) are arithmetic units per the model. Arithmetic units/slots 0 and 1 are active in each instruction, arithmetic unit/slot 2 is idle throughout, and arithmetic unit/slot 3 is active in the first instruction and otherwise idle. Slots 7, 14 and 15 are padding/idle slots and contain the NOP operation 00 throughout. Memory units/slots 4, 5 and 13 are mostly idle and memory unit/slot 12 is completely idle. The control unit is idle in the first two instructions and then has an active op in the 3rd instruction, perhaps a branch.

### MAM Instruction Assembler Mnemonics

MAM instructions comprise a set of operations, one operation for each execution unit or slot. As is standard practice the operations implemented by the various execution unit types have human-readable *assembler* mnemonics. The human-readable assembler mnemonic for a MAM instruction is simply the comma-separated collection of operations of all of the execution units/slots, where each slot operation is labeled by its slot number and execution unit type for clarity. Although we have not yet defined the operations implemented by each execution unit type, nor their mnemonics, the sample instruction machine code sequence above is represented mnemonically as follows:

```
0x0000100000: 0a.neg, 1a.add r2, 2a.nop, 3a.add a2, 4m.nop, 5m.ld8 r2, 6c.nop, 7p.nop, 8a.nop, 9a.sub r2, 10a.nop 11a.nop, 12m.nop 13m.st64s, 14p.nop, 15p.nop
0x0000100010: 0a.mask16, 1a.sub r2, 2a.nop 3a.nop, 4m.rd r3, 5m.nop 6c.nop 7p.nop 8a.nop, 9a.nop 10a.nop 11a.nop 12m.nop, 13m.nop, 14p.nop, 15p.nop
0x0000100020: 0a.save r3, 1a.sub r2, 2a.nop, 3a.nop, 4m.rd r2, 5m.nop, 6c.br 7p.nop, 8a.nop, 9a.nop, 10a.nop, 11a.nop, 12m.nop, 13m.nop, 14p.nop, 15p.nop
```

It is standard practice to omit all nop's from the assembler mnemonics, so the above assembler is typically abbreviated to the following:

```
0x0000100000: 0a.neg, 1a.add r2, 3a.add a2, 5m.ld8 r2, 9a.sub r2, 13m.st64s
0x0000100010: 0a.mask16, 1a.sub r2, 4m.rd r3
0x0000100020: 0a.save r3, 1a.sub r2, 4m.rd r2, 6c.br
```

### MAM Compact Instruction Encoding Format

The raw MAM instruction encoding described above suffers from typical VLIW *code bloat* of idle execution units consuming a full byte of instruction memory for no useful purpose. MAM architecture includes an alternative instruction encoding that is intended to mitigate the problem of machine code bloat. This *compact instruction encoding* is part of the MAM architecture and hence supported in hardware, typically as an extra instruction decode stage in the cpu pipeline. As such, a MAM hardware chip is capable of executing both raw instruction encoding and compact instruction encoding; the instruction format currently being executed is part of the hardware execution state, and transitions between raw and compact instruction encoding are enforced by explicit control unit instructions, or sometimes implicit mode change on return from function-call, or operating-system *trap*.

MAM compact instruction encoding comprises a *header* which defines which execution units are active in the instruction, and a *body* which includes the operation codes of only the active execution units. The compact instruction encoding *header* is a variable-length bitmap of active execution units. Each byte (8 bits) of the *header* includes an *active/inactive* bit for seven (7) of the execution units, and a *continuation* bit which indicates, when set, that there is at least one additional *header* byte. The *continuation* bit is the high bit of the header - i.e. bit 0x80; the low seven bits represent the *active/inactive* bits for seven execution units, from low (0x01) bit to highest (0x40) bit in execution unit/slot order.

Following the *header*, the active slot operations follow in slot order to form the *body* - it should be fairly clear the the body length in bytes corresponds exactly to the number of active (i.e. non-nop) operations in the instruction.

Let's take the example MAM instruction sequence above and represent it as *MAM compact instruction encoding* machine code format. Note that we have three instructions. The first instruction has six active execution units, namely 0a, 1a, 3a, 5m, 8a and 13m. Note that the first four active slots are covered by the first *header* byte; however we need an additional header byte to cover active units 8a and 14m. Accordingly the header comprises two bytes where the first byte has the continuation bit (0x80) set, and then also has bits 0 (0x01), 1 (0x02), 3 (0x08), and 5 (0x20) set, giving us a first header byte of 0xab, or more clearly as the binary 0b10101011. The second header byte covers execution units eight (8) through thirteen (13) which covers the remaining two active slots, 8a and 13m. Accordingly the second header byte has its *continuation* bit clear and has bit 0 (0x01) and bit 6 (0x40) set to represent the active slots, giving us a second header byte value of 0x41, or binary 0b01000001.

The compact encoding body then comprises only the active slot operations, giving us the following machine code representation:

```
0x000020000000 AB 41 01 FA 3D 3B E2 12
0x000020000008 ...
```

The remaining two instructions have active slots only in the first seven execution units and hence require just a single header byte. Here is the full compact machine code for the three instructions:

```
0x000020000000 AB 41 01 FA 3D 3B E2 12
0x000020000008 13 02 3A 2B
0x00002000000C 93 23 3A 2A F0
0x000020000011 ...
```

Note that the raw machine code encoding requires 48 bytes, whereas the compact machine code encoding requires only 17 bytes.

MAM assembler mnemonic representation uses the same presentation for both raw machine code and compact machine code - it is typically obvious from the context which machine code format is being used.

Lastly the specific choices for execution unit slots in the MAM model *MAM/4a/2m/c/./4a/2m/2./16* should now be clear. In particular we have a full set of execution unit types in the first seven slots, so non-dense code can mostly be compactly represented with a single header byte. Of course it is up to the code compiler to emit machine code that mostly uses only the first seven slots in order to achieve the most compact machine code with compact machine code encoding.

## MAM Execution Units

As described above a MAM *model* comprises a specific collection of execution units, each of which is driven explicitly and independently by each instruction. The MAM specification defines three types of execution unit types, each of which is required in a particular MAM model to provide a functional general-purpose CPU. The MAM architecture and instruction encoding naturally supports custom extension to additional types of execution units; however this document focuses on the core MAM execution units only.

In general, each execution unit of a MAM model is self-contained. Internal state of each execution unit, including for example registers, is not directly visible to other execution units. Data exchange between execution units is effected by explicit transfer instructions, as will be described below.

### MAM Arithmetic Units

The MAM arithmetic unit type provides support for general purpose arithmetic and bitwise computation, including 64-bit integer arithmetic, and (64-bit) double-precision IEEE 754 floating point arithmetic. MAM arithmetic units are responsible not only for general arithmetic and bit-wise computation, but also for the generation of data addresses used by the MAM memory units. It is expected that some MAM implementations will omit support for floating point operations. Accordingly in the formal MAM specification integer operations are defined as part of the mandatory *MAM core* specification, whereas floating point support is defined as part of an optional *MAM extension* specification. In the following high level overview it will be assumed that floating point support is present.

The MAM arithmetic unit operations follow an *accumulator* model - all operations use a distinguished *accumulator* register 'A' as source operand and result target. Although accumulator instruction set architectures suffer some instruction-count bloat compared to, for example, typical *RISC* instruction set architectures through the need to explicitly move values into- and out of the accumulator register, this is a deliberate decision in MAM in order to allow a very compact 8-bit operation encoding. MAM motivates and mitigates the decision of an accumulator architecture further by providing the oportunity for substantial parallelism across multiple arithmetic units, and also provides some further mitigation as described below.

#### MAM Arithmetic Unit State

Each MAM arithmetic unit is more that a typical *ALU* or floating point unit - instead it encapsulates its own execution state including its own set of (64-bit) registers and flags. As described above, there is a distinguished *accumulator* register, *a*, which is used as the source and/or target of all operations. In addition each MAM arithmetic unit includes four (4) general purpose registers, *r0* through *r3*. The general purpose registers are used as scratch store for intermediate values, and are accessed in two ways - firstly explicit *move* instructions to and from the accumulator, and secondly as the second operand for binary operations like *add*, *xor*. Lastly there are two *accumulator backup* registers, *a1* and *a2* which are never explicitly written, but instead (always) contain the previous two values of the accumulator register. The accumulator backup registers are purely a mechanism to avoid explicit intermediate value save/restore operations to the general-purpose registers during relatively trivial operation sequences and as such are available only as the second operand for binary operations. All registers contain variously integer and double values and do not particular distinguish between them apart from the operations used on them.

All register values are augmented by a set of six flags which are set at the time that the value was originally calculated. Five of the flags correspond to common cross-architecture flags - *zero, copy, overflow, sign, parity* - that are used to evaluate human-meaningful conditions, e.g. signed less-than-or-equal. The sixth flag *error* supports *speculative* execution and indicates that the value in the register is invalid since it originated from an invalid memory read. The *error* flag is infectious - if any operand has its error flag set, then the operation result is also an *error*. According all of the arithmetic unit registers are 70-bit comprising 64 bits of value and 6 flag bits.

Lastly each MAM arithmetic unit includes a boolean *condition* register, which is used for conditional execution. The *condition* register is set explicitly from the accumulator register flags as will be described below, and is sticky until the next explicit condition register update operation. The condition register is used for condition register value moves to and from the accumulator register.

In summary, each MAM arithmetic unit is a self-contained relatively register-poor accumulator-based general-purpose arithmetic unit, with support for conditional execution.

#### MAM Arithmetic Unit Operation Set

As described above, a MAM arithmetic unit implements an operation set according using an accumulator model. In brief the MAM arithmetic unit operation set includes typical nullary, unary and binary operations which always update the accumulator register *a*, optionally-conditional register move instructions to and from the accumulator *a*, an operation for fetching the current accumulator value from other execution units, including other arithmetic units, and operations for setting the *condition* register. These will be elaborated below.

In general any operation that writes back to the acummulator *a* has the *implicit* side-effect of updating the *accumulator back-up* registers *a1* and *a2* - in short *a2* <- *a1*, *a1* <- *a*, *a* <- new-value - and the previous value of *a2* is dropped. In brief all operations update the accumulator *except* for registers moves *out of* the accumulator, and *condition* register update.

The MAM arithmetic unit operation set distinguishes explicitly between single-cycle operations and multi- or variable-cycle operations. All integer operations except for integer multiply and divide are considered single-cycle. All floating-point operations, on the other hand, are deemed multi-cycle operations. All single-cycle operations are encoded as a single operation; on the other hand all multi- or variable-cycle operations are split into two operations - a *start* operation, and a *complete* operation. The *start* operation initiates an asynchronous computation in the corresponding hardware functional unit, either integer (multiply/divide) or floating-point (all operations). There *MUST* be only one asynchronous operation active at any point in time in either the asynchronous integer unit or the floating-point functional unit; however there can be one integer asynchronous operation and one floating-point asynchronous operation active concurrently. The *complete* operation for both asynchronous units is potentially *stalling* - the entire MAM instruction pipeline across all execution units will be stalled until the result is available. Note that all asynchronous *start* operations are not *accumulator-writing* since the result is not immediately available - as such they do not update *a*, *a1*, or *a2*. On the other hand the *complete* operation possibly stalls, and then eventually writes the result back to the accumulator *a* and updates *a1* and *a2* accordingly.

Single-cycle binary operations typically allow the second operand to be specified in the operation itself as any of the general-purpose registers or accumulator back-up registers. On the other hand, asynchronous operations typically use ***a*** and ***a1*** as operands - this is purely to reduce the operation set size with the philospohy that single-cycle operations should be represented as efficiently as possible in the instruction stream, but asynchronous operations, being inherently multi-cycle and rarer do not require particular focus on operation-chaining efficiency.

##### Nullary Arithmetic Operations

Small constant generation in the range (-64, 64):
- ***const N*** - the exact set of available small constants is described in the [MAM Operation Set Specification](TODO). Operation ***const N*** places the constant N into the accumulator *a* (and updates *a1*, *a2* implicitly), setting the flags accordingly - only the *zero* flag is interesting.

Note that the MAM architecture includes support for obtaining arbitrary large constant values through a memory-based *constants dictionary* typically embedded in the executable image - this will be elaborated further in the description of the [MAM Memory Units](#mam-memory-units):

- ***dict*** - place the address of the active *constants dictionary* into the accumulator

Access to sundry architectural registers (TODO elaborate):

- ***ip***, ***sp***, ***cntl*** - place the value of various global architecture registers into the accumulator

##### Unary Arithmetic Operations

Unary arithmetic operations supported by a MAM arithmetic unit can be partitioned into integer operations and floating-point operations. We will start with integer operations. Note again that all unary operations operate on the accumulator and write back to the accumulator *a*. It is standard practice to omit the implicit register *a* in all operation menemonics.

Standard integer unary operations:

- ***not*** - bitwise inversion
- ***neg*** - arithmetic negation, two's-complement

Bit fiddling:

- ***bcnt***, ***lsb***, ***msb*** - count 1 bits, least significant 1-bit, most significant 1-bit

Operations supporting smaller - 8-bit, 16-bit, 32-bit signed and unsigned integer arithmetic:

- ***sext[8|16|32]*** - sign-extend from the 7th, 15th and 31st bit, respectively
- ***trim[8|16|32]*** - zero all bits except the lowest 8, 16 and 32 bits, respectively

Special floating-point function support. Note that these are all asynchronous *start* operations and do not update the *accumulator*. There *MUST* be a subsequent ***fcomplete*** instruction to wait for and write back the result to the accumulator *a*:

- ***inv***
- ***sqrt***
- ***sin***, ***cos***, ***tan***

##### Binary Arithmetic Operations

Binary arithmetic operations supported by a MAM arithmetic unit can be partitioned into integer operations and floating-point operations. We will start with integer operations. Note again that the first operand of all binary instructions is the accumulator *a*, and the second operand is explicit in the operation as one of the general-purpose registers, *r0* through *r3* or accumulator back-up registers *a1* or *a2*. We do not include the normal *compare* or *test* instructions from typical ISA's since they are essentially just ***sub*** and ***xor*** that set condition flags - in the MAM arithmetic unit *all* operations set the flags and flags are carried with all values even through register move operations.

Standard integer bitwise operations:

- ***and***, ***or***, ***xor*** ***[rN|aM]***

Single-cycle integer arithmetic:

- ***add***, ***sub***, ***rsb*** ***[rN|aM]*** - note ***rsb*** is reverse-subtract, i.e. ***a*** <- *op2* - ***a***

Bitwise integer shift operations:

- ***shl***, ***shrl***, ***shra*** ***[rN|aM]*** - shift-left, shift-right-logical (i.e. 0-fill) and shift-right-arithmetic (i.e. sign-fill).

Asynchronous integer operations - note that these are all asynchronous *start* operations and do not update the *accumulator*. There *MUST* be a subsequent ***icomplete*** instruction to wait for and write back the result to the accumulator *a*:

- ***umul***, ***imul***, ***udiv***, ***idiv*** - note ***a*** and ***a1*** are the operands

Floating point operations - note that these are all asynchronous *start* operations and do not update the *accumulator*. There *MUST* be a subsequent ***fcomplete*** instruction to wait for and write back the result to the accumulator *a*:

- ***fadd***, ***fsub***, ***fmul***, ***fdiv*** - note ***a*** and ***a1*** are the operands

##### Ternary Arithmetic Operations

- ***fmuladd** - computes ***a*** x ***a1*** + ***a2*** as a single asynchronus floating-point computation

##### Async Completion

Asynchronous integer- and floating-point unit complete operations - see above for context. Note that these are potentially stalling operations:
- ***icomplete***
- ***fcomplete***

##### Condition Flag Update

Set the *condition register* and copy the boolean value (zero or one) of the condition into the accumulator - i.e. this is really a unary operator. As noted before, the condition register value is sticky until the next explicit condition flag update:

- ***if[ul|ule|uge|ug|il|ile|ige|ig|zero|nonzero|parityeven|parityodd|carry|nocarry|error|noerror]*** - including unsigned and signed comparison; note ***ifnonzero** for example can be used to set the condition register to arbitrary precomputed boolean values

Read the *condition register* into the accumulator value as a 0 or 1:

- ***cond***

##### Register Moves

All register moves are to and from the accumulator register. Register moves are optionally conditional on the *condition register* supporting conditional computation.

Accumulator save to general-purpose-register - note, non-accumulator-writing:

- ***save[if|ifnot]*** ***rN***

Accumulator read from general-purpose or accumulator back-up register - note conditional restores are always considered accumulator-writing:

- ***restore[if|ifnot]*** ***[rN|aM]***

##### Fetch Accumulator from Remote Execution Units

Note that the semantics here is that the value computed *in this instruction* in the remote execution unit is written to the (local) accumulator, allowing efficient chaining of computation between execution units. This is an accumulator-writing operation, so *a1* and *a2* are updated:

- ***fetch uN*** - where *N* is the slot number - if *N* is this slot then the local accumulator value is duplicated

##### Other Operations

Zeroing of registers - some or all general-purpose registers can be zero'ed in a single operation - this will be motivated and described further in the discussion of function-call and trap support in the *MAM control unit*:

- ***zeroregs*** - the accumulator value ***a*** is used as a 7-bit mask where set bits define which ***rN** (low 4 bits) and ***a**, ***aM*** to zero

### MAM Memory Units

MAM memory units are responsible for data transfers to and from DRAM through the normal L1/L2/LLC memory cache hierarchy. In addition to standard memory reads and writes, the MAM memory until provides explicit support for *speculative* memory access - for example memory *reads* can be hoisted above subsequent possibly-overwriting memory writes while still obeying *read-after-write* (RaW) data dependencies, as will be elaborated further below. In addition, memory *writes* can be tagged as *speculative*, in which case the memory state defined by the speculative write values is (optionally) visible only to read operations executed in the same memory unit; equivalently, speculative writes will not be visible to (any) memory read operations executed in other memory units.

As is the case with register transfers in the MAM arithmetic units, both memory reads and memory writes in the MAM memory units are optionally *conditional*, according to the *condition register* of the MAM memory unit. A conditional write is a NOP if the *condition register* is 0; a conditional read on the other hand immedidately generates the *error* value if the *condition register* is 0, avoiding any memory (cache) activity. In additional, conditional memory operations are guaranteed to *not* generate page faults if the condition register is 0. Unlike the MAM arithmetic unit which has operations to set the condition register explicitly, MAM memory units set their condition register by fetching the condition register from another MAM execution unit. Conditional memory reads and writes will be elaborated in more detail below.

As is the case with all MAM execution units, the MAM memory unit uses an *accumulator* model; there is a distinguished 64-bit *accumulator register*, ***a***, which is used implicitly as the memory address for both memory read and write operations. In addition, there is a single *accumulator back-up register*, ***a1***, which is used as the data value for memory writes, as well as for some additional special-purpose instructions. As is typical practice in MAM, the accumulator back-up regiter ***a1*** always implicitly contains the previous value of the accumulator register ***a***. MAM memory units do not typically generate address and write data values themselves. Instead, memory addresses and write data values are generated by MAM arithmetic units and transferred to the MAM memory unit using ***fetch*** instructions. Write operations, for example, are prepared by a sequence of two ***fetch*** instructions - the first ***fetch** retrieves the data value to be written, and the second ***fetch*** retrieves the write value.

Note that this section provides a high-level overview focused on memory read and write operation semantics within a single MAM processor. The broader topics of virtual memory (paging) support and memory *coherency* semantics in a multi-processing shared-memory environment are beyond the scope of this section, and are elaborated separately in [TODO].

[TODO - define alignment constraints of memory operations]

#### MAM Memory Read Achitecture

Each MAM memory unit includes two (2) read ports/registers - we will use the terms *read port* and *read register* interchangeably in the following, although it should be noted that MAM read port/register infrastructure is more complex than what is normally understood by either term. Memory read in MAM architecture is an asynchronous operation, separated into explicit *start read* and *complete read* instructions. Accordingly, each read register supports the necessary state to support an in-progress asynchronous read operation, namely the memory address, read width, read completion status, read value and boolean state indicating whether the read should take note of interim speculative memory writes.

A memory read is initiated by a(n optionally conditional) *start read* instruction which indicates the width of the read - 8, 16, 32 or 64 bits, and whether the read operation should take account of subsequent *speculative* writes. In-progress read operations *always* take account of, or *snoop*, subsequent non-speculative writes issued by any of the MAM memory units - any write that overlaps the read port's address will be noticed by the read port and be included in the (eventual) read result. As such, the MAM architecture allows reads in general to be hoisted above writes in order to mitigate the latency associated with read cache misses in general.

Memory reads are *completed* with a specific *read complete* operation. The *read complete* instruction defines the memory state *seen* by the asynchronous read operation, and excludes concurrent writes executed by other MAM memory units in the same instruction. The *read complete* operation is (potentially) stalling like all MAM *completion* operations - if the read value is not yet available in the read port, typically due to memory cache misses, the entire instruction stream will be stalled until the read value is available. The *read complete* operation copies the final read result into the MAM memory unit *accumulator* from where it can be retrieved by other MAM execution units with a ***fetch*** operation. In addition, if the memory read failed due to an invalid address, the *read complete* operation signals a page fault as will be described in more detail below.

Once the read operation has been *completed*, the read port maintains the final read state, including the completed read value, until another read operation is initiated in the read port. Any further *read complete* operations on the read port will simply transfer the already complete read value into the *accumulator* ***a***.

In summary, each MAM memory unit supports two asynchronous and intrinsically speculative memory reads. In-progress, i.e. incomplete, reads will take account of subsequent non-speculative write operations in any of the MAM memory units, thereby allowing memory reads to be hoisted above memory writes in order to mitigate the overall latency impact and typical instruction serialising of *read-after-write* (RAW) data *hazards*. In addition, MAM memory units support *speculative memory writes* which allow each memory unit to have a special memory-unit-local view of memory state, as will be elaborated further below. MAM memory reads can optionally also take account of, i.e. snoop, speculative writes in the same MAM memory unit.

#### MAM Memory Write Achitecture

Apart from standard write operations, MAM memory units provide a facility for *speculative writes*. The effects of speculative writes are (optionally) visibile to reads performed in the same MAM memory unit, and only if a read operations explicitly opts in to the *speculative* memory view. Architecturally, speculative writes are supported by a MAM memory unit local speculative write buffer, which contains at most four (4) memory writes. Speculative writes are eventually either dropped or committed with an explicit conditional operation. When specualtive writes are dropped, they are no longer visible to the local MAM memory unit, nor with they ever be visible elsewhere. On the other hand, when speculative writes are committed, they become immediately visible to other MAM memory units and *will* be written to DRAM through the cache hierarchy as per non-speculative reads.

In general memory write semantics in MAM dictate that a memory write is not visible to read operations completed in the same instruction cycle as the memory write, and/but are visible to all MAM memory units completed in the following instruction cycle or later in the instruction sequence.

#### MAM Memory Unit Page Fault Behaviour

Although virtual memory support is not described in this section, MAM architecture supports virtual memory and memory protection via *paging* as is typical with modern processor architectures. Accordingly, *page-faults* are triggered by memory operations whose addresses are invalid or protected. In general page-faults are triggered asynchronously and may be raised some time after the initiating read or write operation. However, in the case of memory reads, page faults are guaranteed to be raised at or before a read completion operation, and *complete read* operations are blocking in this sense. On the other hand, memory write operations may, in general, raise corresponding page faults some time after the initiating *write* instruction, although the *snooping* semantics of incomplete reads and concurrent writes still applies. It is up to the hardware MAM implementation to choose how to implement memory semantics correctly in this respect, for example by using read completion operations as a barrier instruction for outstanding asynchronous write page faults.

Page-fault behaviour under speculative execution is particularly tricky since in general spurious page faults change a program/task's execution semantics and in general speculative execution must not result in externally visible program behaviour different to the program semantics. In order to allow for correct execution semantics in the presence of speculative reads, MAM allows read operations to optionally specify that page-faults should be delayed until read completion time - unlike normal MAM read port behaviour where page faults can be raised as early as possible. In addition MAM memory unit *complete read* operations can specify that no page fault should be raised - instead, in cases where the read address is invalid or protected the *error* value is generated as the result of the read.

In general speculative reads should be approached as follows in order to avoid spurious page-faults. In general, speculative reads (and writes) are used to pre-execute code paths that might not be executed by the program/task. In most cases the speculative path will be gated by a conditional logic branch in the original program code, and speculative execution is used to make progress before the branching condition is known. Accordingly, one way to ensure correct program semantics with speculative execution is to initiate reads in speculative mode - i.e. non-page-fault raising, compute the condition gating the speculative path while the speculative read is still in-progress, and then use a conditional *complete read* operation to complete the read. In this way the potential externally visible artifact of a read page fault is only visible once the speculative path is known to be taken in fact. A trivial example of this is the very common code pattern of *null-pointer* checks gating actual use of a pointer. In MAM a speculative-mode, i.e. non-page-fault raising, read can be initiated before the null pointer check is performed. Then, the read can be conditionlly completed according to the null pointer check outcome.

Alternatively, in cases where it is disadvantageous to compute the speculative branch condition prior to speculative read completion, a non-page-fault generating *complete read* should be used. However, in this aproach, where an error value typically propogates into further speculative execution, further *compensation* code is required to redrive the speculative code path, in order that program semantics are correctly maintained. In general compensation code will execute once the speculative condition is know, check for potential error values from previous speculative reads, and re-run the corresponding logic in non-speculative mode.

Lastly, there are cases where it can be statically proven that reads are page-fault free - for example where a speculative read follows a non-speculative read on the same memory page. In this case speculative code paths are safe to execute in non-speculative mode, since there cannot be any externally-visible spurious behaviour, even if the speculative code path is not taken in fact.

#### MAM Memory Unit Special Operations

Apart from standard memory read/write support, MAM memory units also support a handful of special purpose instructions, some of which are relatively standard in modern architectures and some of which - pointer-following reads, for example, are relatively unusual. MAM does not have special support for memory prefetch, which is relatively standard in modern architectures; instead that dummy *start read* instructions suffice for the purpose of memory prefetch in MAM, particularly since in MAM *all* memory reads are asynchronous and non-stalling until the corresponding *read complete* operation, which can be completely omitted for *prefetch* purposes.

##### MAM Atomic Memory Access

MAM memory units support atomic memory operations in a multi-processing environment through *compare-and-swap* (CAS). This will not be further elaborated here - refer to [TODO] for a further elaboration of memory coherency semantics in a multi-processing shared memory environment.

##### MAM Non-Temporal Memory Write

Like most modern architectures, MAM supports *non-temporal* writes which bypass the memory cache hierarchy as far as possible. In short a non-temporal write will not itself cause its cache-line to be brought into any of the memory cache hierarchy levels, instead *writing behind* to the more distant cache hierarchy. On the other hand if the cache line associated with the non-temporal write is already in some level of cache, the memory write will complete in the corresponding cache level - essentially the non-temporal write will complete in the closest memory cache level containing the memory address cache line, or DRAM itself.

##### MAM Pointer-Following Read

MAM memory units provide spcial asynchronous support for a sequence of *pointer-following* memory reads, where subsequent reads in the sequence use the result of the previous read as a (base) memory pointer - for example when traversing a hierarchical or recursive data structure like a linked-list. Like with all MAM memory unit reads, pointer-following reads proceed asynchronously. However, instead of a single memory read at the specified address, pointer-following reads allow up to three (3) additional memory reads to proceed asynchonously, each further read at a fixed 16-bit signed offset from the previous read's result. Both of the memory ports in a MAM memory unit support independent concurrent pointer-following reads and hence each have four (4) value registers, one for each read of the pointer-follwing sequence. Pointer-following reads are necessarily 64-bit, since each interim value is used as the (base) memory address of the following memory read in the pointer-following sequence.

The motivation for pointer-following reads is to minimise the latency overhead of explicit *complete read* operations. Instead, as soon as any memory read in a pointer-following sequence completes, the memory port immediately initiates the next memory read in the sequence independent of the instruction sequence.

Like with normal *complete read* instructions, any of the (up to four) read results can be completed at any point in the instruction sequence, not necessarily in strict order of read results. Completion of any of the read results is a stalling operation and implicitly effects completion of any earlier reads in the pointer-following chain. Pointer-following reads are always executed in *page-fault-free* semantics - in other words page faults are not generated early, but are only raised at the time of the corresponding explicit *read complete* operation. As such, a *pointer-following* read will stall at the first invalid or protected memory address in the sequence, until a corresponding *complete read* allows further progress, for example via page-fault handling.

Pointer-follwing read operations take two arguments. The first argument in the accumulator ***a*** is the first (base) memory address, as with other read operations. The second parameter to a pointer-following read, in the accumulator backup register ***a1***, is a 64-bit value containing four (4) signed 16-bit offsets. The pointer following read starts by adding the first (lowest bits) 16-bit offset to the (first) address and initiates a 64-bit memory read at that address. As soon as that (first) read completes, the result is used as a base address for the second read. The second memory address is then computed as that first read result plus the second 16-bit offset. The read port then initiates the second read immediately, without waiting for a *read complete* operation on the first read. The same process then continues for subsequent reads until the pointer-following read sequence is complete, or is stalled by an invalid or protected memory address.

The special offset value 0x8000 is used as a marker for the end of the pointer-following read sequence. As soon as the value 0x8000 is seen as the next offset value, the pointer-folowing read is considered complete and no further reads are performed. For example a 64-bit pointer-following offset value of 0x00008000fff80008 specifies a sequence of two (2) pointer-following reads, where the first offset is 8, and the second offset is -8.

Like normal asynchronous reads, pointer-following reads also *snoop* write activity in any of the MAM memory units, until the read has been explicitly completed through a *complete read* operation. If any write operation in any MAM memory unit overlaps with any of the addresses used for one of the sequence of pointer-following reads, the pointer-following read is replayed again from the overwritten address, even if additional reads in the sequence have already been completed. In this manner the *complete read* for any one of the sequence of pointer-following reads defines the memory state of the read operation, just as is the case with simple read operations. Similarly the *read complete* operation defines the point at which page faults are raised. The only subtlety with read completion of a pointer-following read (sequence) is that it is legal to execute a *complete read* on any of the reads in the sequence at any time. If earlier reads in the sequence have not been explicitly completed at that time, then the read complete of the later read in the sequence explicitly first completes any incomplete earlier reads in the sequence, which of course could generate page faults for the earlier reads.

In terms of hardware implementation of pointer-following reads, it is expected that at a minimum a MAM implementation will asynchronously continue execution of pointer-following reads, in the absence of explicit read completion. However, it is also anticipated that further hardware optimisations are possible, including pushing pointer/offset following logic into the memory cache layers and even the DRAM controller, in order to avoid entirely sequential communications between the processor and more distant and relatively high-latency cache layers and even DRAM itself. Such optimisations are expected to significantly improve performance of *graph query* applications.

##### MAM Memory Cache Line Zero

MAM memory units support zeroing of an entire cache line (64-bytes) in a single instruction. Cache line zero behaviour is non-temporal in that it will not unnecessarily pollute or otherwise involve near-line cache levels.

Cache-line clear operations are intended to support fast non-temporal zeroing of large memory address ranges, as is typical with in virtual memory (pge) management and managed language environment garbage collection. It is expected that a MAM implementation will optimise cache-line zeroing through the entire memory cache hierarchy and DRAM controller.

#### MAM Memory Unit Operations

[TODO]

### MAM Control Unit

