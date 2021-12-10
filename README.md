# RISCV-Emulator

When first Googling "RISC-V emulator," it was this project that inspired me to try make my own: 
https://book.rvemu.app/hardware-components/01-cpu.html

Everything you need to know on how the RISC-V core works is found here:
https://riscv.org/technical/specifications/

A prebuilt RISC-V toolchain can be found here (Ubuntu 20.04 x86):
https://github.com/stnolting/riscv-gcc-prebuilt

Alternatively you can build your own toolchain from source (takes some time):
https://github.com/riscv-collab/riscv-gnu-toolchain

## Some general notes

* Program emulates base RV32I ISA
* So far I thought is was a bit unnecessary to emulate some sort of bus interface between the processor and memory
* No overflow checks are made on arithemtic instructions as this can be accomplished in software using branch instructions

## Instructions Implemented

* ADDI, XORI, ORI, ANDI
* ADD, XOR, OR, AND
* LW (Load word), LH (Load half word), LB (Load byte)
* SW (Store word), SH (Store half word), SB (Store byte)
* JAL (Jump and Link)

## Examples of Encoded Instructions

0x00B50633 // Add r10 and r11 -> r12
0x81C50693 // Add 2076 to r10 -> r13
0x2703 // Load word at DRAM address 0x0 into r14
0x1783 // Load half word at DRAM addr 0x0 into r15

# Wishlist

* Integrate with sample program compiled with riscv toolchain
* Compile to WebAssembly and integrate it into a web app, possibly with PrimeNG's terminal
