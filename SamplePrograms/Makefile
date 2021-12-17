CXX=riscv32-unknown-elf-gcc
OBJCOPY=riscv32-unknown-elf-objcopy

sum-of-ten:
	$(CXX) -S sum_of_ten.c
	$(CXX) -Wl, -Ttext=0x0 -nostdlib -o sum_of_ten sum_of_ten.s
	$(OBJCOPY) -O binary sum_of_ten sum_of_ten.bin
