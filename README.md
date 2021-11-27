# RISCV-Emulator

When first Googling "RISC-V emulator," it was this project that inspired me to try make my own.
https://book.rvemu.app/hardware-components/01-cpu.html

Everything you need to know on how the RISC-V core works is found here:
https://riscv.org/technical/specifications/

## Some general notes

* Program emulates base RV32I ISA
* This has 4 core instruction formats, namely; R, I, S and U

* No overflow checks are made on arithemtic instructions as this can be accomplished in software using branch instructions

## Instructions Implemented

* ADDI
* ADD
