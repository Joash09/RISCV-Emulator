#include "stdint.h"

#ifndef RISCV_HEADER
#define RISCV_HEADER

typedef struct riscv riscv_t;

riscv_t* initialize();

void load_register_value(riscv_t* riscv, uint32_t reg_index, uint32_t val);
uint32_t read_register(riscv_t* riscv, uint32_t reg_index);

uint32_t fetch(riscv_t* riscv);
void decode_execute(riscv_t* cpu, int instruction);

uint32_t fetch_pc(riscv_t* riscv);
void increment_pc(riscv_t* riscv);

void delete_riscv(riscv_t* riscv);

// For testing 
void load_instruction(riscv_t* riscv, uint32_t mem_index, uint32_t instr);

#endif
