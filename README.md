# Twinbeam

Modern C++ software development for Intel x86-64 and PIC32/MIPS.

Contains indispensables: Unicode, `Memory`*, `Vector`, `Map` and `Chronology`.

To use the library, include the `Twinbeam.h` header and link with its corresponding 
`libTwinbeam_PIC32MZ` or `libTwinbeam_macOS` archive.

Examples are soon available in the `Examples` directory.

## Embedded Development with MIPS

To compile a program, normally you just type ninja to run something similar to

    terminal$ clang-6.0 -g -target mipsel -mips32r2 -fno-rtti -fno-exceptions -fblocks --std=c++17 -c main.cpp -o main.o
    
    terminal$ ld.lld -T ./pic32.ld -o mykernel main.o
    
    terminal$ llvm2pic32 -b bootloader.hex mykernel.elf > mykernel.hex

To query where in the virtual address space a symbol is defined, enter:

    terminal$ alias q='ninja syms | egrep'
    terminal$ q main
    bfc01dbc T main

To get insights into the current memory consumption, write:

    terminal$ ninja size
    text      data    bss   dec      hex filename
    11056     400   16640   28096    6dc0monitor_pic32mx795F512L

To list the sections created by the linker, enter:

    terminal$ ninja sect 

To view all symbols in your program, write:

    terminal$ alias syms='ninja syms'
    terminal$ syms 

To debug your application, write:

    terminal$ alias src='ninja source | less '
    terminal$ src
    terminal$ mdb ...
    llvm2pic32

Tool converting a llvm-generated MIPS executable file into an Intel Hex file.

### Synopsis

    lvm2pic32 [-b <bootloader.hex file>] <elf32 file>

### Description

The `llvm2pic32` utility converts the `.bss`, `.data` and `.text` sections in an Executable 
and Linkable Format file into a text-based Intel Hex file.

Virtual addresses are automatically converted into its physical counterpart.

The optional argument `-b` allows for the inclusion of a boot loader into the final image.

### Exit Status

The `llvm2pic32` utility exits `0` on success and non-zero otherwise.

### Bugs

Compile the program with `clang -o llvm2pic32 -std=c++1z main.cpp`.

### The Pic32mz Bootloader

The bootloader expects the interrupt service routine to start on the virtual address 
`0xBD000000` and that the `__start` symbol is placed on `0xBD001000`.
