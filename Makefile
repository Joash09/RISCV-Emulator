CC=g++
CFLAGS=
OBJS=RISCV-Emulator.o 

main: RISCV-Emulator.cpp
	${CC} ${CFLAGS} $? -o $@

.PHONY: clean
clean:
	rm main
