// RISCV Emulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include "riscv.h"

int main()
{
	printf("Welcome to my RISCV emulator\n");

	// Initialize CPU
	riscv_t* cpu;
	cpu = initialize();

	// Load registers
	load_register_value(cpu, 0xA, 5);
	load_register_value(cpu, 0xB, 3);
	
	printf("Register 10 value: %x\n", read_register(cpu, 0xA));
	printf("Register 11 value: %x\n", read_register(cpu, 0xB));
	printf("Register 12 value: %x\n", read_register(cpu, 0xC));

	// Initialize Load Instruction
	load_instruction(cpu, 0, 0x00B50633);

	// FETCH, DECODE, EXECUTE cycle
	while(fetch_pc(cpu) < 4){

		// FETCH
		uint32_t instruction = fetch(cpu);
		printf("Executing instruction: %x\n", fetch(cpu));

		// Decode and execute
		decode_execute(cpu, instruction);

		// Jump to next instruction. 32 bits = 4 bytes
		increment_pc(cpu);

	}

	printf("Register 12 value: %x\n", read_register(cpu, 0xC));

	delete_riscv(cpu);

	return 0;
}

