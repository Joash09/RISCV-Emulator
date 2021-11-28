CC=gcc
CFLAGS=-g
OBJS=main.o riscv.o dram.o

main: main.c riscv.c dram.c
	${CC} ${CFLAGS} $? -o $@

.PHONY: clean
clean:
	rm main
