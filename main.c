// RISCV Emulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"

#include "riscv.h"
#include "dram.h"

#define MEMORY_SIZE 1080*1080*128 // 128MiB

void print_help();
void print_debug_help();

int main()
{
	printf("Welcome to my RISCV emulator\n");

	// Initialize CPU
	riscv_t* cpu;
	cpu = initialize();

	// Initialize Memory
	dram_t* dram;
	dram = initialize_dram();
	int32_t memory_byte_counter = 0;

	print_help();
	char input;
	scanf(" %c", &input);
	while(input != 'q') {

		switch(input) {
			
			case 'p': // Print register table
				print_registers(cpu);
				break;
			
			case 'l': ; // Load Program
				char filename[50];
				printf("Enter filename for the binary (.bin) program:\t");
				scanf("%s", filename);
				int num_bytes_loaded = load_program(dram, filename);
				printf("%d bytes loaded\n", num_bytes_loaded);
				break;

			case 'e': ; // Execute one line of the program

								// FETCH
								uint32_t instruction = load_word(dram, fetch_pc(cpu));
								printf("Executing instruction: %x at %x\n", instruction, fetch_pc(cpu));

								// Decode and execute
								decode_execute(cpu, dram, instruction);

								// Jump to next instruction. 32 bits = 4 bytes
								increment_pc(cpu);		
								break;

			case 'r': ; // Run loaded program

								// Reset CPU program counter
								reset_pc(cpu);

								// FETCH, DECODE, EXECUTE cycle
								while(fetch_pc(cpu) < MEMORY_SIZE/4){ // Each instruction is 4 bytes long

									// FETCH
									uint32_t instruction = load_word(dram, fetch_pc(cpu));
									printf("Program Counter: %x\n", fetch_pc(cpu));
									printf("Executing instruction: %x\n", instruction);

									// Decode and execute
									decode_execute(cpu, dram, instruction);

									// Jump to next instruction. 32 bits = 4 bytes
									increment_pc(cpu);

								}							
								break;

			case 'd': ; // Debug menu
				print_debug_help();
				char debug_input;
				scanf(" %c", &debug_input);
				switch(debug_input) {
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
										store_word(dram, memory_byte_counter, dram_instruction);
										memory_byte_counter += 4;
										break;
				}
				break;
			
			default:
				printf("Unknown option");

		}
		print_help();
		scanf(" %c", &input);
	}

	// Clean up memory
	delete_riscv(cpu);
	delete_dram(dram);

	return 0;
}

void print_help() {
	printf("\n");
	printf("l.\tLoad Program\t\te.\tExecute First Instruction\n");
	printf("r.\tRun Program\t\td.\tDebug\n");
	printf("p.\tPrint Registers\t\tq.\tQuit\n");

}

void print_debug_help() {
	printf("\n");
	printf("r.\tLoad Register\tc.\tCreate Instruction\n");
}
