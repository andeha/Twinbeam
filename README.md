# Twinbeam

Modern C++ software development for Intel x86-64 and PIC32/MIPS.

Contains indispensables: Utf-8, `Vector`, `Map` and `Chronology`.

To use the library, include the `Twinbeam.h` header and link with its corresponding `libTwinbeam_pic32mz_*.a` or `libTwinbeam_macOS_*.a` archive.

Requires [`ninja`](https://ninja-build.org), [`llvm`](https://llvm.org) and — for MIPS development — a pic32mz development board.  

Examples are available in the [`Examples`](https://github.com/andeha/Twinbeam/tree/master/Examples) directory.

## Embedded Development with MIPS

To compile a program, normally you just type `ninja` to run something similar to:
    
    terminal$ clang-6.0 -g -target mipsel -mips32r2 -fno-rtti -fno-exceptions -fblocks --std=c++17 -c main.cpp -o main.o
    
    terminal$ ld.lld -T ./pic32.ld -o mykernel main.o
    
    terminal$ llvm2pic32 -b bootloader.hex mykernel.elf > mykernel.hex
    
To query where in the virtual address space a symbol is defined, enter:
    
    terminal$ alias q='ninja syms | egrep'
    terminal$ q main
    bfc01dbc T main
    
To get insights into your current memory consumption, write:
    
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
    
To convert an llvm-generated MIPS executable file into a `.hex` file, use [`llvm2pic32`](https://github.com/andeha/Twinbeam/tree/master/llvm2pic32/main.cpp). (For details, see [Intel Hex](https://en.wikipedia.org/wiki/Intel_HEX) and other documents on Internet.)

### Synopsis
    
    lvm2pic32 [-b <bootloader.hex file>] <elf32 file>
    
### Description

The `llvm2pic32` utility converts the `.bss`, `.data` and `.text` sections in an *Executable and Linkable Format* file into a text-based Intel Hex file.

Virtual addresses are automatically converted into its physical counterpart.

The optional argument `-b` injects a boot loader into the final image. If no `-b` is given, output suitable for inclusion via `-b` is emitted.

### Exit Status

The `llvm2pic32` utility exits `0` on success and non-zero otherwise.

### Bugs

Compile `llvm2pic32` with `clang -o llvm2pic32 -std=c++1z main.cpp`.

## Booting a Chip

The bootloader [bootloader_MZ](bootloader_MZ_xxxxxxx) lives at `0xBFC00000` and expects your kernels' interrupt service routine to start on the virtual address `0xBD000000` and that your `__start` symbol is placed on `0xBD001000`. See [`helloworld`](https://github.com/andeha/Twinbeam/tree/master/Examples/helloworld) for details.

[bootloader_MZ_xxxxxxx]: https://github.com/andeha/Twinbeam/bootloader_MZ_xxxxxxx.hex

## References

[1] The [Intel® 64 and IA-32 Architectures Software Developer Manual: Vol 3](https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-vol-3a-part-1-manual.pdf) document.

[2] The Microchip [PIC32MX5XX/6XX/7XX](http://ww1.microchip.com/downloads/en/DeviceDoc/60001156J.pdf) Family Data Sheets.

[3] The [Intel Hex](https://en.wikipedia.org/wiki/Intel_HEX) format.
