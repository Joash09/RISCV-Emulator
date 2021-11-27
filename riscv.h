#ifndef RISCV_HEADER
#define RISCV_HEADER

#include "stdint.h"
#include "dram.h"

typedef struct riscv riscv_t;

riscv_t* initialize();

void load_register_value(riscv_t* riscv, uint32_t reg_index, uint32_t val);
uint32_t read_register(riscv_t* riscv, uint32_t reg_index);

void decode_execute(riscv_t* cpu, dram_t* dram, int instruction);

uint32_t fetch_pc(riscv_t* riscv);
void increment_pc(riscv_t* riscv);

void delete_riscv(riscv_t* riscv);

#endif
