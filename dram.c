#include "dram.h"
#include "stdint.h"
#include "stdlib.h"

struct dram {
	uint8_t memory[100];
};

dram_t* initialize_dram() {
	return malloc(sizeof(struct dram));
}

void store_word(dram_t* dram, uint32_t start_addr, uint32_t val) {
	dram->memory[start_addr] = val & 0xFF;
	dram->memory[start_addr+1] = (val>>8) & 0xFF;
	dram->memory[start_addr+2] = (val>>16) & 0xFF;
	dram->memory[start_addr+3] = (val>>24) & 0xFF;
}

void store_half_word(dram_t* dram, uint32_t start_addr, uint16_t val) {
	dram->memory[start_addr] = val & 0xFF;
	dram->memory[start_addr+1] = (val>>8);
}

void store_byte(dram_t* dram, uint32_t start_addr, uint8_t val) {
	dram->memory[start_addr] = val;
}

uint32_t load_word(dram_t* dram, uint32_t start_addr) {
	return dram->memory[start_addr] |
		dram->memory[start_addr + 1] << 8 |
		dram->memory[start_addr + 2] << 16 |
		dram->memory[start_addr + 3] << 24;
}

uint32_t load_half_word(dram_t* dram, uint32_t start_addr) {
	return dram->memory[start_addr] |
		dram->memory[start_addr + 1] << 8;
}

uint32_t load_byte(dram_t* dram, uint32_t start_addr) {
	return dram->memory[start_addr];
}

void delete_dram(dram_t* dram) {
	free(dram);
}
