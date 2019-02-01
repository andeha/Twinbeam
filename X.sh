ninja -C Source -f build_pic32mz.ninja                              || exit 1
ninja -C Source -f build_macOS.ninja                                || exit 1
ninja -C macOS -f harness.ninja                                     || exit 1
ninja -C Bootloader                                                 || exit 1
ninja -C Sprinkle/pdb                                               || exit 1
ninja -C Examples/dbgout
ninja -C Examples/ledflash
ninja -C Examples/helloworld
ninja -C Examples/fpu
# ninja -C Examples/bldc
ninja -C Examples/usb
# ninja -C Examples/twinsh
# ninja -C Examples/turbine
ninja -C Examples/radio
# ninja -C Examples/flightcontroller
# ninja -C Examples/attokernel
# ninja -C Examples/😐/
ninja -C Examples/sdhc
ninja -C Additions -f build_macOS.ninja                             || exit 1
ninja -C Additions -f build_pic32mz.ninja                           || exit 1

