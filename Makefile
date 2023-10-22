BOOT_DIR = ./boot
KERNEL_DIR = ./kernel
DRIVERS_DIR = ./drivers

ASM_FILE = $(wildcard ${BOOT_DIR}/*.asm)
H_FILE = $(wildcard ${KERNEL_DIR}/*.h ${DRIVERS_DIR}/*.h)
C_FILE = $(wildcard ${KERNEL_DIR}/*.c ${DRIVERS_DIR}/*.c)

# Setting tools.
COMPILER = gcc
LINKER = ld
ASSEMBLER = nasm

# Kernel compile flags.
KERNEL_FLAG = -ffreestanding -nostdlib -nostdinc

run: ${KERNEL_DIR}/image.bin
	qemu-system-x86_64 -fda $^

${KERNEL_DIR}/image.bin: ${BOOT_DIR}/boot.o ${KERNEL_DIR}/kernel.bin
	wsl -e cat $^ > $@

${BOOT_DIR}/boot.o: ${ASM_FILE}
	${ASSEMBLER} ${BOOT_DIR}/boot.asm -o $@

${KERNEL_DIR}/kernel.bin: ${KERNEL_DIR}/kernel.tmp
	objcopy -O binary -j .text $^ $@

${KERNEL_DIR}/kernel.tmp: ${BOOT_DIR}/kernel_entry.o ${KERNEL_DIR}/kernel.o
	${LINKER} -m i386pe -o $@ -Ttext 0x1000 $^

${KERNEL_DIR}/kernel.o: ${KERNEL_DIR}/kernel.c ${C_FILE} ${H_FILE}
	${COMPILER} -m32 $< -o $@ ${KERNEL_FLAG}

${BOOT_DIR}/kernel_entry.o: ${BOOT_DIR}/kernel_entry.asm
	${ASSEMBLER} $^ -f elf32 -o $@
