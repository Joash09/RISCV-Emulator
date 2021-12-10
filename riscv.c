#include "riscv.h"
#include "dram.h"

#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"

#define REGISTERS 32

const uint32_t NUM_INSTRUCTIONS = 1;
const uint32_t MEMORY_SIZE = 1 * 4;

struct riscv {
	uint32_t registers[REGISTERS];  // 32 registers 32 bits wide
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

void decode_execute(riscv_t* riscv, dram_t* dram, int instruction) {

	// Using R type instruction as defined by the ISA
	// Use bit masking to separate parts of the instruction
	uint32_t op_code = instruction & 0x7f;
	uint32_t rd = (instruction >> 7) & 0x1f;
	uint32_t fn3 = (instruction >> 12) & 0x7;
	uint32_t r1 = (instruction >> 15) & 0x1f;
	uint32_t r2 = (instruction >> 20) & 0x1f;

	switch(op_code) {

		case 0x03: { // Load instructions 
				   uint32_t imm = ((instruction & 0xfff00000) >> 20);
				   uint32_t addr = r1 + imm;

				   switch(fn3) {
					   case 0x0: { // Load byte
							     riscv->registers[rd] = load_byte(dram, addr);
							     break;
						     }
					   case 0x1: { // Load half word
							     riscv->registers[rd] = load_half_word(dram, addr);
							     break;
						     }
					   case 0x2: { // Load word
							     riscv->registers[rd] = load_word(dram, addr);
							     break;
						     }

					   default:
						     printf("Instruction not yet implemented\n");
						     break;
				   }
				   break;

			   }
		case 0x23: { // Store instructions
				   uint32_t imm = ((instruction & 0xfff00000)>>12) | rd;

				   switch(fn3) {
					   case 0x0: { // Store byte
							     store_byte(dram, imm, r2);
							     break;
						     }
					   case 0x1: { // Store half word
							     store_half_word(dram, imm, r2);
							     break;
						     }
					   case 0x2: { // Store word
							     store_word(dram, imm, r2);
							     break;
						     }
					   default: 
						     printf("Instruction not yet implemented\n");
						     break;
				   }
				   break;
			   }
		case 0x13: { // Immediate instructions

				   uint32_t imm = ((instruction & 0xfff00000) >> 20);
				   switch(fn3) {
					   case 0x0: { // ADDI
							     riscv->registers[rd] = imm + riscv->registers[r1];
							     break;
						     }
					   case 0x4: { // XORI
							     riscv->registers[rd] = imm ^ riscv->registers[r1];
							     break;
						     }
					   case 0x6: { // ORI
							     riscv->registers[rd] = imm | riscv->registers[r1];
							     break;

						     }
					   case 0x7: { // ANDI
							     riscv->registers[rd] = imm & riscv->registers[r1];
							     break;
						     }
				   }
				   break;
			   }
		case 0x33: { // Perform operation on two registers and store value in rd

				   switch(fn3) {

					   case 0x0: { // ADD
							riscv->registers[rd] = riscv->registers[r1] + riscv->registers[r2];
							break;
						     }
					   case 0x4: { // XOR
							riscv->registers[rd] = riscv->registers[r1] ^ riscv->registers[r2];
							break;
						     }
					   case 0x6: { // OR
							riscv->registers[rd] = riscv->registers[r1] | riscv->registers[r2];
							break;
						     }
					   case 0x7: {	// AND
							riscv->registers[rd] = riscv->registers[r1] & riscv->registers[r2];
							break;
						     }
				   }
				   break;
			   }
		case 0x6F: { // JAL
				   // Immediate is sign extened
				   int32_t imm = 
					   ((instruction>>31) & 0x1) << 20 |
					   ((instruction>>21) & 0x8) << 12 |
					   ((instruction>>20) & 0x1) << 11 | 
					   ((instruction>>21) & 0xA);
				   riscv->increment_pc();
				   int32_t pc_signed = (int32_t) riscv->fetch_pc;
				   riscv->registers[rd] = (uint32_t) (pc_signed + imm);
				   break;
			   }
		default:
			   printf("Instruction not yet implemented\n");
			   break;
	}

}

uint32_t fetch_pc(riscv_t* riscv) {
	return riscv->program_counter;
}

void increment_pc(riscv_t* riscv) {
	riscv->program_counter = riscv->program_counter + 4;
}

void print_registers(riscv_t* riscv) {

	for(int i = 0; i < REGISTERS/2; i++) {
		printf("Register %d:\t%x\tRegister %d:\t%x\n", i, riscv->registers[i], i+(REGISTERS/2), riscv->registers[i+(REGISTERS/2)]);
	}
}

void delete_riscv(riscv_t* riscv) {
	free(riscv);
}
