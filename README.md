# HOS

## Requierments

- Windows 11 (x86)
- NASM
- i686 Cross Compiler
- make
- WSL
- QEMU (64-bits)

## Usage

This Makefile is for Windows 11.

```sh
make
```

## Cross Compiler

- [i686-elf-tools](https://github.com/lordmilko/i686-elf-tools)

## Reference

- [os-tutorial](https://github.com/cfenollosa/os-tutorial)

## Issues

- [Compiling C to ELF32 on Windows](https://stackoverflow.com/questions/65752272/compiling-c-to-elf32-on-windows)
- [C header issue: #include and "undefined reference"](https://stackoverflow.com/questions/10357117/c-header-issue-include-and-undefined-reference)
- [implicit declaration of function](https://qiita.com/yano0v0/items/52026aa6f4a424aa2331)
- [16-video-driver can't pass string](https://github.com/cfenollosa/os-tutorial/issues/31) (The screen is blinking when the function `kprint` is called.)