#ifndef DRAM_HEADER
#define DRAM_HEADER

#include "stdint.h"

typedef struct dram dram_t;

dram_t* initialize_dram();
void load_instruction(dram_t* dram, uint32_t mem_index, uint32_t instr);
uint32_t fetch_instruction(dram_t* dram, uint32_t pc);
void delete_dram(dram_t* dram);

#endif
