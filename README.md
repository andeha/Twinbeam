# Twinbeam

Modern C++ software development for Intel x86-64 and PIC32/MIPS.

Contains necessities for utf-8, `Vector`, `Map` and `Chronology`.

To use, include the `Twinbeam.h` header and link with its corresponding `libTwinbeam_pic32mz_*.a` or `libTwinbeam_macOS_*.a` archive.

Requires [`ninja`](https://ninja-build.org), [`llvm`](https://llvm.org) and — for MIPS development — a pic32mz development board. Also [Knot.h](https://raw.githubusercontent.com/wiki/andeha/Twinbeam/PDFs/Knot.🔥.h.pdf) and [Tändhatt.cpp](https://raw.githubusercontent.com/wiki/andeha/Twinbeam/PDFs/Tändhatt.pdf) and similar to Textmate.

Do not forget to visit [`Examples`](https://github.com/andeha/Twinbeam/tree/master/Examples), the [llvm2pic32](https://raw.githubusercontent.com/wiki/andeha/Twinbeam/llvm2pic32.1.pdf)/[pdb](https://raw.githubusercontent.com/wiki/andeha/Twinbeam/pdb.1.pdf) manual pages
 and the Twinbeam [wiki](https://github.com/andeha/Twinbeam/wiki).

## Prebuilt

For Xcode 9 and llvm-6: [libTwinbeam_macOS.a](https://github.com/andeha/Twinbeam/releases/download/twinbeam_prerel4/libTwinbeam_macOS_75eb7d7.a), [libTwinbeam_pic32mz.a](https://github.com/andeha/Twinbeam/releases/download/twinbeam_prerel4/libTwinbeam_pic32mz_75eb7d7.a), [Twinbeam.h](https://github.com/andeha/Twinbeam/releases/download/twinbeam_prerel4/Twinbeam.h). (*Rev. `75eb7d7`, Friday, August 21, 2018.*)

Bootloader: [pic32mz.hex](https://github.com/andeha/Twinbeam/releases/download/twinbeam_prerel2/bootloader_mz_0f5fabc.hex) (*Rev. `0f5fabc`, Friday, August 3, 2018.*)

## References

[1] The [Intel® 64 and IA-32 Architectures Software Developer Manual: Vol 3](https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-vol-3a-part-1-manual.pdf) document.

[2] The Microchip [PIC32MM0256GPM064](https://eu.mouser.com/datasheet/2/268/50002576a%20PIC32MM%20USB%20Curiosity%20Development%20Board%20-1113849.pdf), the [PIC32MX5XX/6XX/7XX](http://ww1.microchip.com/downloads/en/DeviceDoc/60001156J.pdf) Family Data Sheets.

[3] The [Intel Hex](https://en.wikipedia.org/wiki/Intel_HEX) format.
