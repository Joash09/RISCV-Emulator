#include "dram.h"

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

#define MEMORY_SIZE 1080*1080*128 // 128MiB

struct dram {
	uint8_t memory[MEMORY_SIZE];
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

int load_program(dram_t* dram, char* filename) {

	// Open file
	FILE* file = fopen(filename, "rb");
	if (file == NULL) {
		perror("Cannot open program file\n");
		exit(EXIT_FAILURE);
	}

	// For each byte in file store byte in memory
	char program_byte = fgetc(file);
	int memory_counter = 0;
	while(program_byte != EOF) {

		printf("%x\n", program_byte);
		dram->memory[memory_counter] = program_byte;
		memory_counter++;
		program_byte = fgetc(file);
	}
	
	// Close file
	fclose(file);

	return memory_counter;

}

void delete_dram(dram_t* dram) {
	free(dram);
}
