// RISCV Emulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdio.h";

typedef unsigned char U8;
typedef unsigned long int U32; // 64 bits wide unsigned

// const unsigned int MEMORY_SIZE = 1024 * 1024 * 128; // 16 MB
const unsigned int NUM_INSTRUCTIONS = 1;
const unsigned int MEMORY_SIZE = NUM_INSTRUCTIONS * 4;

struct Cpu {
    U32 registers[32];  // 32 registers 32 bits wide
    U32 program_counter;
    U8 dram[MEMORY_SIZE]; // Addressing memory as bytes
};

void initialize(Cpu* cpu);
void initialize_dram(Cpu* cpu); // For testing
int fetch(Cpu* cpu);
void execute(Cpu* cpu, int instruction);

int main()
{
    printf("Welcome to my RISCV emulator\n");

    // Initialize CPU
    Cpu cpu;

    // FETCH, DECODE, EXECUTE cycle
    while(cpu.program_counter < MEMORY_SIZE){

        // Jump to next instruction. 32 bits = 4 bytes
        cpu.program_counter = cpu.program_counter + 4;

        // FETCH

    }

    return 0;
}

void initialize(Cpu* cpu) {

    cpu->registers[0] = 0;
    cpu->registers[2] = MEMORY_SIZE;

}

void initialize_dram(Cpu* cpu) {

}

int fetch(Cpu* cpu) {

    // Read the 4 bytes which make up the instruction
    // Bytes are read in Little Endian format
    U32 index = cpu->program_counter;
    return cpu->dram[index] |
            cpu->dram[index + 1] << 8 |
            cpu->dram[index + 2] << 16 |
            cpu->dram[index + 3] << 24;

}

void execute(Cpu* cpu, int instruction) {


}
