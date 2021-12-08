// RISCV Emulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"

#include "riscv.h"
#include "dram.h"

void print_help();

int main()
{
	printf("Welcome to my RISCV emulator\n");

	// Initialize CPU
	riscv_t* cpu;
	cpu = initialize();

	// Initialize Memory
	dram_t* dram;
	dram = initialize_dram();
	int32_t instruction_counter = 0;

	print_help();
	char input;
	scanf(" %c", &input);
	while(input != 'q') {

		switch(input) {
			case 'p': // Print register table
				print_registers(cpu);
				break;
			case 'r': ; // Manually load register value
				int32_t reg_addr, value;
				printf("Enter register address:\t");
				scanf("%x", &reg_addr);
				printf("Enter register value:\t");
				scanf("%x", &value);
				load_register_value(cpu, reg_addr, value);
				break;
			case 'c': ;
				int32_t dram_instruction;
				scanf(" %x", &dram_instruction);
				store_word(dram, instruction_counter, dram_instruction);
				instruction_counter += 4;
				break;
			default:
				printf("Unknown option");

		}
		print_help();
		scanf(" %c", &input);
	}

	// FETCH, DECODE, EXECUTE cycle
	while(fetch_pc(cpu) < instruction_counter/4){ // Each instruction is 4 bytes long

		// FETCH
		uint32_t instruction = load_word(dram, fetch_pc(cpu));
		printf("Executing instruction: %x\n", instruction);

		// Decode and execute
		decode_execute(cpu, dram, instruction);

		// Jump to next instruction. 32 bits = 4 bytes
		increment_pc(cpu);

	}

	print_registers(cpu);

	delete_riscv(cpu);
	delete_dram(dram);

	return 0;
}

void print_help() {

	printf("\n");
	printf("p.\tPrint Registers\t\tr.\tLoad Register\n");
	printf("c.\tCreate Instruction\te.\tExecute Instruction\n");
	printf("l.\tLoad Program\t\tq.\tQuit\n");
}

