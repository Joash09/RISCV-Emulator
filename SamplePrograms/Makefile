COMPILER_PATH=
CXX=riscv32-unknown-elf-gcc
OBJCOPY=riscv32-unknown-elf-objcopy

sum-of-ten:
	$(COMPILER_PATH)$(CXX) -S sum_of_ten.c
	$(COMPILER_PATH)$(CXX) -Wl,-V -Ttext=0x0 -nostdlib -o sum_of_ten sum_of_ten.s
	$(COMPILER_PATH)$(OBJCOPY) -O binary sum_of_ten sum_of_ten.bin
