# Setting directories.
LIB_DIR = ./lib
BOOT_DIR = ./boot
KERNEL_DIR = ./kernel
DRIVERS_DIR = ./drivers

# Setting files.
ASM_FILE = $(wildcard ${BOOT_DIR}/*.asm)
H_FILE = $(wildcard ${KERNEL_DIR}/*.h ${DRIVERS_DIR}/*.h ${LIB_DIR}/*.h)
C_FILE = $(wildcard ${KERNEL_DIR}/*.c ${DRIVERS_DIR}/*.c ${LIB_DIR}/*.c)
O_FILE = ${C_FILE:.c=.o}

# Setting tools.
COMPILER = i686-elf-gcc
LINKER = i686-elf-ld
ASSEMBLER = nasm

# Kernel compile flags.
C_FLAG = -g -ffreestanding

all: run

${KERNEL_DIR}/image.bin: ${BOOT_DIR}/boot.bin ${KERNEL_DIR}/kernel.bin
	wsl -e cat $^ > $@

${KERNEL_DIR}/kernel.bin: ${BOOT_DIR}/kernel_entry.o ${O_FILE}
	${LINKER} -o $@ -Ttext 0x1000 $^ --oformat binary

${BOOT_DIR}/boot.bin: ${BOOT_DIR}/boot.asm
	${ASSEMBLER} $^ -f bin -o $@

${BOOT_DIR}/kernel_entry.o: ${BOOT_DIR}/kernel_entry.asm
	${ASSEMBLER} $^ -f elf -o $@

%.o: %.c ${H_FILE}
	${COMPILER} ${C_FLAG} -c $< -o $@

run: ${KERNEL_DIR}/image.bin
	qemu-system-i386 -fda $^

# You will need to switch to WSL to run this command.
clear:
	rm -rf ${KERNEL_DIR}/*.o ${KERNEL_DIR}/*.bin ${DRIVERS_DIR}/*.o ${LIB_DIR}/*.o ${BOOT_DIR}/*.o ${BOOT_DIR}/*.bin