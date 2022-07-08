#!/usr/bin/env /bin/zsh

builtin typeset BUNDLEID='ABCD1234'
builtin typeset TEAMID='4321ABCD'

builtin typeset progname=$0
builtin typeset signcode

function usage
{
   cat << HEREDOC
   
   Usage: $progname [--sign]
   
   optional arguments
    -h, --help     show this message and exit
    --sign         sign code after compilation
   
HEREDOC
}

while [[ $# -gt 0 ]]; do
  case $1 in
   -s | --codesign)
     shift
     signcode="yes"
     ;;
   -help | --help | -h | --h \? )
     usage
     exit 1
     ;;
  esac
done

#  alternatively prompt> schema 'TEAMID=$S and BUNDLEID=$S'.

ninja -C Source -f build_armmac.ninja                               || exit 1
ninja -C Source -f build_pic32mz.ninja                              || exit 1
ninja -C Source -f build_pic32mm.ninja                              || exit 1
ninja -C Source -f build_intcmac.ninja                              || exit 1
lipo -create -output libTwinbeam_macos.a libTwinbeam-x86_64.a            \
 libTwinbeam_macarm.a                                               || exit 1
if [[ -n "$signcode" ]]; then
  codesign -s ${TEAMID} -f -o runtime --timestamp -i ${BUNDLEID} libTwinbeam_macos.a
# codesign -s - -f -o runtime --timestamp libTwinbeam_macarm.a
fi
#  lipo -create ... as of Xcode 13.2 only for arm and intel and not mips.
ninja -C Bootloader -f build-mm.ninja                               || exit 1
ninja -C Bootloader -f build-mzda.ninja                             || exit 1
# ninja -C macOS -f :work:.ninja.ninja /work/.ninja.ninja           || exit 1
ninja -C Sprinkle/pdb                                               || exit 1
#  see progress on --<􀖆 assemble.cpp> and --<􀐒 retrospect.c>.
# Examples: dbgout ledflash helloworld fpu bldc usb twinsh turbine radio
# flightcontroller attokernel sdhc
# ninja -C Examples/😐/
ninja -C exercise -f build.ninja                                    || exit 1
ninja -C ../helixsh build_macos.ninja                               || exit 1
builtin typeset -gx MINIMUMPLATFORM='-target arm64-apple-macos12 -D __armv8a__'
ninja -C ../Minimum -f build.ninja
mv ../Minimum/Minimum.app/Contents/MacOS/Minimum ../Minimum/Minimum.arm64
builtin typeset -gx MINIMUMPLATFORM='-target x86_64-apple-darwin21'
ninja -C ../Minimum -f build.ninja
mv ../Minimum/Minimum.app/Contents/MacOS/Minimum ../Minimum/Minimum.x86_64
lipo -create -output ../Minimum.app/Contents/MacOS/Minimum               \
 ../Minimum/Minimum.x86_64 ../Minimum/Minimum.arm64
if [[ -n "$signcode" ]]; then
  codesign -f -s ${TEAMID} -o runtime --timestamp -i {BUNDLEID} ../Minimum/Minimum.app
fi
