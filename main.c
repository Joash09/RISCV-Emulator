// RISCV Emulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"

#include "riscv.h"
#include "dram.h"

int main()
{
	printf("Welcome to my RISCV emulator\n");

	// Initialize CPU
	riscv_t* cpu;
	cpu = initialize();

	// Initialize Memory
	dram_t* dram;
	dram = initialize_dram();

	// Load registers
	load_register_value(cpu, 0xA, 5);
	load_register_value(cpu, 0xB, 3);
	
	printf("Register 10 value: %x\n", read_register(cpu, 0xA));
	printf("Register 11 value: %x\n", read_register(cpu, 0xB));
	printf("Register 12 value: %x\n", read_register(cpu, 0xC));
	printf("Register 13 value: %x\n", read_register(cpu, 0xD));
	
	// Initialize Load Instructions
	load_instruction(dram, 0, 0x00B50633); // Add r10 and r11 -> r12
	load_instruction(dram, 1, 0x81C50693); // Add 2076 to r10 -> r13

	// FETCH, DECODE, EXECUTE cycle
	while(fetch_pc(cpu) < 8){

		// FETCH
		uint32_t instruction = fetch_instruction(dram, fetch_pc(cpu));
		printf("Executing instruction: %x\n", instruction);

		// Decode and execute
		decode_execute(cpu, instruction);

		// Jump to next instruction. 32 bits = 4 bytes
		increment_pc(cpu);

	}

	printf("Register 12 value: %d\n", read_register(cpu, 0xC));
	printf("Register 13 value: %d\n", read_register(cpu, 0xD));

	delete_riscv(cpu);
	delete_dram(dram);

	return 0;
}

