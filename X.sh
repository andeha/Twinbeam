#!/usr/bin/env /bin/zsh
builtin typeset BUNDLEID='ABCD1234'
builtin typeset TEAMID='4321DCBA'
builtin typeset signcode
while [[ $# -gt 0 ]]; do
  case $1 in
   -s | --codesign)
     shift
     signcode="yes"
     ;;
  esac
done
# ⬷ alternatively prompt> schema 'TEAMID=$S and BUNDLEID=$S'.
ninja -C Source -f build_armmac.ninja                               || exit 1
ninja -C Source -f build_pic32mz.ninja                              || exit 1
ninja -C Source -f build_pic32mm.ninja                              || exit 1
ninja -C Source -f build_intcmac.ninja                              || exit 1
lipo -create -output libTwinbeam_macos.a libTwinbeam-x86_64.a            \
 libTwinbeam_arm.a                                                  || exit 1
if [[ -n "$signcode" ]]; then
  codesign -s ${TEAMID} -f -o runtime --timestamp -i ${BUNDLEID} libTwinbeam_macos.a
# codesign -s - -f -o runtime --timestamp libTwinbeam_macos.a
fi
# ⬷ lipo -create ... as of Xcode 13.2 only for arm and intel and not mips.
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
# ⬷ see progress on --<🥽 assemble.cpp> and --<􀐒 retrospect.c>.
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
if [[ -n "$signcode" ]]; then
  codesign -f -s ${TEAMID} -o runtime --timestamp -i {BUNDLEID} ../Minimum/Minimum.app
fi
