#include "dram.h"
#include "stdint.h"
#include "stdlib.h"

struct dram {
	uint8_t memory[8];
};

dram_t* initialize_dram() {
	return malloc(sizeof(struct dram));
}

void store_word(dram_t* dram, uint32_t mem_index, uint32_t val) {
	dram->memory[mem_index*4] = val & 0xFF;
	dram->memory[(mem_index*4)+1] = (val>>8) & 0xFF;
	dram->memory[(mem_index*4)+2] = (val>>16) & 0xFF;
	dram->memory[(mem_index*4)+3] = (val>>24) & 0xFF;
}

void store_half_word(dram_t* dram, uint32_t mem_index, uint16_t val) {
	dram->memory[mem_index*4] = val & 0xFF;
	dram->memory[(mem_index*4)+1] = (val>>8);
}

void store_byte(dram_t* dram, uint32_t mem_index, uint8_t val) {
	dram->memory[mem_index*4] = val;
}

uint32_t load_word(dram_t* dram, uint32_t pc) {
	return dram->memory[pc] |
		dram->memory[pc + 1] << 8 |
		dram->memory[pc + 2] << 16 |
		dram->memory[pc + 3] << 24;
}

uint32_t load_half_word(dram_t* dram, uint32_t pc) {
	return dram->memory[pc] |
		dram->memory[pc + 1] << 8;
}

uint32_t load_byte(dram_t* dram, uint32_t pc) {
	return dram->memory[pc];
}

void delete_dram(dram_t* dram) {
	free(dram);
}
