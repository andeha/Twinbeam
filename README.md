# Twinbeam

Modern C++ software development for Intel x86-64 and PIC32/MIPS.

Contains necessities: Utf-8, `Vector`, `Map` and `Chronology`.

To use, include the `Twinbeam.h` header and link with its corresponding `libTwinbeam_pic32mz_*.a` or `libTwinbeam_macOS_*.a` archive.

Requires [`ninja`](https://ninja-build.org), [`llvm`](https://llvm.org) and — for MIPS development — a pic32mz development board.

More details are given in [`Examples`](https://github.com/andeha/Twinbeam/tree/master/Examples) and on the Twinbeam [wiki](https://github.com/andeha/Twinbeam/wiki).

## Prebuilt

Core: libTwinbeam_macOS.a, libTwinbeam_pic32mz.a, Twinbeam.h. (For Xcode 9 and llvm-6.0.)

Bootloader: [pic32mz](https://github.com/andeha/Twinbeam/releases/download/boot_v1.0/bootloader_mz_eec0c30.hex) (eec0c30)

## References

[1] The [Intel® 64 and IA-32 Architectures Software Developer Manual: Vol 3](https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-vol-3a-part-1-manual.pdf) document.

[2] The Microchip [PIC32MX5XX/6XX/7XX](http://ww1.microchip.com/downloads/en/DeviceDoc/60001156J.pdf) Family Data Sheets.

[3] The [Intel Hex](https://en.wikipedia.org/wiki/Intel_HEX) format.
