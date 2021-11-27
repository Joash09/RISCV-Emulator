#include "dram.h"
#include "stdint.h"
#include "stdlib.h"

struct dram {
	uint8_t memory[8];
};

dram_t* initialize_dram() {
	return malloc(sizeof(struct dram));
}

void load_instruction(dram_t* dram, uint32_t mem_index, uint32_t instr) {
	dram->memory[mem_index*4] = instr & 0xFF;
	dram->memory[(mem_index*4)+1] = (instr>>8) & 0xFF;
	dram->memory[(mem_index*4)+2] = (instr>>16) & 0xFF;
	dram->memory[(mem_index*4)+3] = (instr>>24) & 0xFF;
}

uint32_t fetch_instruction(dram_t* dram, uint32_t pc) {
	return dram->memory[pc] |
		dram->memory[pc + 1] << 8 |
		dram->memory[pc + 2] << 16 |
		dram->memory[pc + 3] << 24;
}

void delete_dram(dram_t* dram) {
	free(dram);
}
