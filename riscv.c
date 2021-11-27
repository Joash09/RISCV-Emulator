#include "riscv.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"

const uint32_t NUM_INSTRUCTIONS = 1;
const uint32_t MEMORY_SIZE = 1 * 4;

struct riscv {
	uint32_t registers[32];  // 32 registers 32 bits wide
	uint32_t program_counter;
};

riscv_t* initialize() {
	
	riscv_t* riscv;
	riscv = malloc(sizeof(struct riscv));

	riscv->program_counter = 0;
	riscv->registers[0] = 0;
	riscv->registers[2] = MEMORY_SIZE; // Init dram first then get mem size?

	return riscv;

}

void load_register_value(riscv_t* riscv, uint32_t reg_index, uint32_t val) {
	riscv->registers[reg_index] = val;
}

uint32_t read_register(riscv_t* riscv, uint32_t reg_index) {
	return riscv->registers[reg_index];
}

void decode_execute(riscv_t* riscv, int instruction) {

	// Using R type instruction as defined by the ISA
	// Use bit masking to separate parts of the instruction
	uint32_t opcode = instruction & 0x7f;

	uint32_t rd = (instruction >> 7) & 0x1f;
	uint32_t r1 = (instruction >> 15) & 0x1f;
	uint32_t r2 = (instruction >> 20) & 0x1f;

	switch(opcode) {

		case 0x13: { // Add immediate value to register with address rd
								 uint32_t imm = ((instruction & 0xfff00000) >> 20);
								 riscv->registers[rd] = imm + riscv->registers[r1];
								 break;
							 }
		case 0x33: { // Add numbers found in addresses r1 and r2 to rd
								 riscv->registers[rd] = riscv->registers[r1] + riscv->registers[r2];
								 break;
							 }
		default:
							 printf("Instruction not yet implemented");
	}

}

uint32_t fetch_pc(riscv_t* riscv) {
	return riscv->program_counter;
}

void increment_pc(riscv_t* riscv) {
	riscv->program_counter = riscv->program_counter + 4;
}

void delete_riscv(riscv_t* riscv) {
	free(riscv);
}
