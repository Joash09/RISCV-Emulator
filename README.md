# RISCV-Emulator

When first Googling "RISC-V emulator," it was this project that inspired me to try make my own.
https://book.rvemu.app/hardware-components/01-cpu.html

Everything you need to know on how the RISC-V core works is found here:
https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf
https://riscv.org/technical/specifications/

## Some general notes

* Program emulates base RV32I ISA
* This has 4 core instruction formats, namely; R, I, S and U

* No overflow checks are made on arithemtic instructions as this can be accomplished in software using branch instructions

## Instructions Implemented

* ADDI
* ADD
* LW (Load word), LH (Load half word), LB (Load byte)

# Wishlist

* Integrate with sample program compiled with riscv toolchain
* Compile to WebAssembly and integrate it into a web app, possibly with PrimeNG's terminal
