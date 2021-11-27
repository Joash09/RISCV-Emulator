CC=gcc
CFLAGS=
OBJS=main.o riscv.o

main: main.c riscv.c
	${CC} ${CFLAGS} $? -o $@

.PHONY: clean
clean:
	rm main
