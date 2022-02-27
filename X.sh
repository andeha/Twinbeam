ninja -C Source -f build_macos.ninja                                || exit 1
ninja -C Source -f build_pic32mz.ninja                              || exit 1
ninja -C Source -f build_pic32mm.ninja
# ⬷ see progress on --<🥽 assemble.cpp> and --<􀐒 retrospect.c>. 
# lipo -create .. as of Xcode 12.2 only for arm and intel, not mips.
ninja -C Additions -f bld_mac.ninja                                 || exit 1
ninja -C Additions -f bld_mz.ninja                                  || exit 1
ninja -C Additions -f seismic-mac.ninja                             || exit 1
ninja -C Additions -f seismic-mz.ninja                              || exit 1
ninja -C Additions -f bld-o-mz.ninja                                || exit 1
ninja -C Additions -f bld-o-mac.ninja                               || exit 1
# ninja -C macOS -f :work:.ninja.ninja /work/.ninja.ninja           || exit 1
ninja -C Bootloader -f build-mm.ninja                               || exit 1
ninja -C Bootloader -f build-mzda.ninja                             || exit 1
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
ninja -C macOS -f harness-sv-1.ninja                                || exit 1
ninja -C macOS -f harness-1.ninja                                   || exit 1
ninja -C macOS -f harness-2.ninja                                   || exit 1
ninja -C macOS -f harness-add.ninja                                 || exit 1
ninja -C macOS -f harness-aux.ninja                                 || exit 1
ninja -C Additions -f bld-annex.ninja                               || exit 1
# ninja -C Additions/Storage -f dgate_mac.ninja                       || exit 1
# ninja -C Additions/Storage -f dgate_mz.ninja                        || exit 1
# ninja -C Additions/heavy-duty -f linear-mac.ninja                   || exit 1
# ninja -C Additions/grayzones -f miller_mac.ninja                    || exit 1
ninja -C ../helixsh build_macos.ninja                               || exit 1
ninja -C ../Minimum -f build.ninja

