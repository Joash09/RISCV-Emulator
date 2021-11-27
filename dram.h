#ifndef DRAM_HEADER
#define DRAM_HEADER

#include "stdint.h"

typedef struct dram dram_t;

dram_t* initialize_dram();

void store_word(dram_t* dram, uint32_t mem_index, uint32_t val);
void store_half_word(dram_t* dram_t, uint32_t mem_index, uint16_t val);
void store_byte(dram_t* dram_t, uint32_t mem_index, uint8_t val);

// Targeting 32 bit CPU registers
uint32_t load_word(dram_t* dram, uint32_t pc);
uint32_t load_half_word(dram_t* dram, uint32_t pc);
uint32_t load_byte(dram_t* dram, uint32_t pc);

void delete_dram(dram_t* dram);

#endif
