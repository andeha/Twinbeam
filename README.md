# Twinbeam

Modern software for Intel x86-64 and PIC32/MIPS.

Contains details for utf-8, `Array`, `List`, `Ma-p` and `Chronology`. To use, include portions of the `Twinbeam.h` header and link with its corresponding `libTwinbeam_pic32mz_*.a` or `libTwinbeam_macOS_*.a` archive.

Requires [`llvm`](https://llvm.org), [`ninja`](https://ninja-build.org) and — for MIPS development — a pic32mz development board and at-least 'Textmate' and 'Sublime Text'.

## Entry points and topics

Digest the source tree starting from any of the topics listed in the index below:

| Topic | Where in tree |
| --- | --- |
| Calendar | [Twinbeam]--...--<[icati-irrevers.c](https://github.com/andeha/Twinbeam/blob/master/Source/icati-irrevers.c)> |
| Compiler | [Projects]--<[retros-compi.c](https://github.com/BlinkingEmotions/Fanfare/blob/main/%F4%80%90%92%20retros-compi.c)> |
| Coroutines | [Co-operative]--<[coro-builtin.c](https://github.com/andeha/Cox-route/blob/main/coro-builtin.c)> |
| Linked lists | [Project]--<[eff.c](https://github.com/BlinkingEmotions/Fanfare/blob/main/∎%7C∎%20eff.c)><br>and --<[radbanc.c](https://github.com/BlinkingEmotions/Fanfare/blob/main/∎%7C∎%20radbanc.c)> |
| Maths | [arctan](https://github.com/andeha/distorsion-projection/blob/main/sequent-sinuativ.c)&nbsp;[cos](https://github.com/andeha/distorsion-projection/blob/main/captu-radio.c)&nbsp;[ln](https://github.com/andeha/distorsion-projection/blob/main/abundan-invert.c)&nbsp;[sin](https://github.com/andeha/distorsion-projection/blob/main/captu-radio.c)&nbsp;[tan](https://github.com/andeha/distorsion-projection/blob/main/sequent-sinuativ.c)&nbsp;[tanh⁻¹](https://github.com/andeha/distorsion-projection/blob/main/circula-convers.c)&nbsp;[tanh](https://github.com/andeha/distorsion-projection/blob/main/circula-convers.c)|
| Presenting bits on terminal | [Pic32step-pdb]--<[present-out.c](https://github.com/andeha/Pic32step-pdb/blob/master/present-out.c)><br>and --<[regs-mm.c](https://github.com/andeha/Pic32step-pdb/blob/master/regs-mm.c)> |
| Red-black tree | [Project]--<[eff.c](https://github.com/BlinkingEmotions/Fanfare/blob/main/∎%7C∎%20eff.c)> |
| .table and .streck files | [Turbin-sublime]--<[balancesheet.table](https://github.com/andeha/Turbin-sublime/blob/main/balancesheet.table)><br>and --<[hello.streck](https://github.com/andeha/Turbin-sublime/blob/main/hello.streck)> |
| Typecase | [Twinbeam]--<[Typecase.hpp│h](https://github.com/andeha/Twinbeam/blob/master/Typecase.hpp│h)> |
| Uart logging | [Twinbeam]--...--<[serial-symbol.c](https://github.com/andeha/Twinbeam/blob/master/Source/serial-symbol.c)> | 
| Unicode parsing | [Projects]--<[turbin-normal.c](https://github.com/BlinkingEmotions/Fanfare/blob/main/%F4%80%96%86%20turbin-normal.c)> |
| View- and window controller | [Minimum]--<[histories.swift](https://github.com/andeha/Minimum/blob/main/histories.swift)> |

Do not forget to visit [`Examples`](https://github.com/BlinkingEmotions/Fanfare), the [llvm2pic32](https://raw.githubusercontent.com/wiki/andeha/Twinbeam/llvm2pic32.1.pdf)/[pdb](https://raw.githubusercontent.com/wiki/andeha/Twinbeam/pdb.1.pdf) manual pages and the Twinbeam [wiki](https://github.com/andeha/Twinbeam/wiki).

## Prebuilt

For Xcode 9 and llvm-6: [libTwinbeam_macOS.a](https://github.com/andeha/Twinbeam/releases/download/twinbeam_prerel4/libTwinbeam_macOS_75eb7d7.a), [libTwinbeam_pic32mz.a](https://github.com/andeha/Twinbeam/releases/download/twinbeam_prerel4/libTwinbeam_pic32mz_75eb7d7.a), [Twinbeam.h](https://github.com/andeha/Twinbeam/releases/download/twinbeam_prerel4/Twinbeam.h). (*Rev. `75eb7d7`, Friday, August 21, 2018.*)

Bootloader: [pic32mz.hex](https://github.com/andeha/Twinbeam/releases/download/twinbeam_prerel2/bootloader_mz_0f5fabc.hex) (*Rev. `0f5fabc`, Friday, August 3, 2018.*)

## To compile

1) Edit `small-runtime`, `host-big` and `tools-small` in `tools.ninja`.
2) Enter `cd Source` and `mkdir Releases`.
3) Build with `ninja -f build_intcmac.ninja` and `ninja -f build_armmac.ninja`.

## References

[1] The [Intel® 64 and IA-32 Architectures Software Developer Manual: Vol 3](https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-vol-3a-part-1-manual.pdf) document.

[2] The Microchip [PIC32MM0256GPM064](https://eu.mouser.com/datasheet/2/268/50002576a%20PIC32MM%20USB%20Curiosity%20Development%20Board%20-1113849.pdf), the [PIC32MX5XX/6XX/7XX](http://ww1.microchip.com/downloads/en/DeviceDoc/60001156J.pdf) Family Data Sheets.

[3] Low-cost [Motor Control](https://ww1.microchip.com/downloads/en/Appnotes/90003152a.pdf) application note.

[4] The [Intel Hex](https://en.wikipedia.org/wiki/Intel_HEX) format.
