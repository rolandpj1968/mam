# Multi-Accumulator Machine

## Introduction

The multi-accumulator machine (*MAM*) is an machine- and *instruction set architecture* (ISA) that fits into the general category of explicitly-parallel VLIW machines. MAM goes somewhat further than typical VLIW architectures and ISA's by directly driving multiple mostly-independent execution units from execution-unit-specific (sub-)operations within a single *instruction*. Each (hardware) execution unit is driven by a specific *slot* in the (long) instruction. Each slot within the instruction 'word' is 8 bits; the instruction comprises a collection of these 8-bit operations and the semantics of instruction execution is that all (non-NOP) operands in the instruction word are executed in parallel.

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

The MAM arithmetic unit type provides support for general purpose arithmetic computation, including 64-bit integer arithmetic, and (64-bit) double-precision IEEE 754 floating point arithmetic. The MAM arithmetic unit operations follow an *accumulator* model - all operations use a distinguished *accumulator* register 'A' as source operand and result target. Although accumulator instruction set architectures suffer some instruction-count bloat compared to, for example, typical *RISC* instruction set architectures through the need to explicitly move values into- and out of the accumulator register, this is a deliberate decision in MAM in order to allow a very compact 8-bit operation encoding. MAM motivates and mitigates the decision of an accumulator architecture further by providing the oportunity for substantial parallelism across multiple arithmetic units, and also provides some further mitigation as described below.

### MAM Arithmetic Unit State

Each MAM arithmetic unit is more that a typical *ALU* or floating point unit - instead it encapsulates its own execution state including its own set of (64-bit) registers and flags. As described above, there is a distinguished *accumulator* register, *a*, which is used as the source and/or target of all operations. In addition each MAM arithmetic unit includes four (4) general purpose registers, *r0* through *r3*. The general purpose registers are used as scratch store for intermediate values, and are accessed in two ways - firstly explicit *move* instructions to and from the accumulator, and secondly as the second operand for binary operations like *add*, *xor*. Lastly there are two *accumulator backup* registers, *a1* and *a2* which are never explicitly written, but instead (always) contain the previous two values of the accumulator register. The accumulator backup registers are purely a mechanism to avoid explicit intermediate value save/restore operations to the general-purpose registers during relatively trivial operation sequences and as such are available only as the second operand for binary operations. All registers contain variously integer and double values and do not particular distinguish between them apart from the operations used on them.

All values stored in registers are augmented by a set of six flags which are set at the time that the value was originally calculated. Five of the flags correspond to common cross-architecture flags - *zero, copy, overflow, sign, parity* - that are used to evaluate human-meaningful conditions, e.g. signed less-than-or-equal. The sixth flag *error* supports *speculative* execution and indicates that the value in the register is invalid since it originated from an invalid memory read. The *error* flag is infectious - if any operand has its error flag set, then the operation result is also an *error*. According all of the arithmetic unit registers are 70-bit comprising 64 bits of value and 6 flag bits.

Lastly each MAM arithmetic unit includes a boolean *condition* register, which is used for conditional execution. The *condition* register is set explicitly from the accumulator register flags as will be described below, and is sticky until the next explicit condition register update operation. The condition register is used for condition register value moves to and from the accumulator register.

In summary, each MAM arithmetic unit is a self-contained relatively register-poor accumulator-based general-purpose arithmetic unit, with support for conditional execution.

### MAM Arithmetic Unit Operation Set



### MAM Memory Units

### MAM Control Unit

