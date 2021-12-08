CC=gcc
FLAGS=
LDFLAGS=

SOURCES=dram.c riscv.c main.c
OBJS=$(SOURCES:.c=.o)
TARGET=main


$(TARGET): $(OBJS)
	$(CC) $(FLAGS) -o $@ $^ $(LDFLAGS)


.PHONY: clean
clean:
	@em $(TARGET) $(OBJS)
