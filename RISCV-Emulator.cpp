// RISCV Emulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdio.h"
#include "stdint.h"

// const unsigned int MEMORY_SIZE = 1024 * 1024 * 128; // 16 MB
const uint32_t NUM_INSTRUCTIONS = 1;
const uint32_t MEMORY_SIZE = NUM_INSTRUCTIONS * 4;

typedef struct Cpu {
	uint32_t registers[32];  // 32 registers 32 bits wide
	uint32_t program_counter;
	uint8_t dram[MEMORY_SIZE]; // Addressing memory as bytes
} Cpu;

void initialize(Cpu* cpu);
void initialize_dram(Cpu* cpu); // For testing
int fetch(Cpu* cpu);
void execute(Cpu* cpu, int instruction);

int main()
{
	printf("Welcome to my RISCV emulator\n");

	// Initialize CPU
	Cpu cpu = {
		{},
		0,
		{}
	};
	initialize(&cpu);

	// Initialize DRAM memory
	initialize_dram(&cpu);

	// FETCH, DECODE, EXECUTE cycle
	while(cpu.program_counter < MEMORY_SIZE){

		// FETCH
		printf("%x\n", fetch(&cpu));

		// Jump to next instruction. 32 bits = 4 bytes
		cpu.program_counter = cpu.program_counter + 4;

	}

	return 0;
}

void initialize(Cpu* cpu) {

	cpu->program_counter = 0;
	cpu->registers[0] = 0;
	cpu->registers[2] = MEMORY_SIZE;

}

void initialize_dram(Cpu* cpu) {
	cpu->dram[0] = 0xFA;
	cpu->dram[1] = 0xAB;
	cpu->dram[2] = 0x55;
	cpu->dram[3] = 0x00;

	for (int i = 0; i < 4; i++) {
		printf("%x\t", cpu->dram[i]);
	}
}

int fetch(Cpu* cpu) {

	// Read the 4 bytes which make up the instruction
	// Bytes are read in Little Endian format
	uint32_t index = cpu->program_counter;
	printf("\n%d\n", index);
	return cpu->dram[index] |
		cpu->dram[index + 1] << 8 |
		cpu->dram[index + 2] << 16 |
		cpu->dram[index + 3] << 24;

}

void execute(Cpu* cpu, int instruction) {


}
