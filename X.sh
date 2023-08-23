#!/usr/bin/env /bin/zsh

builtin typeset BUNDLEID='ABCD1234'
builtin typeset TEAMID='4321ABCD'
# \also prompt> schema 'TEAMID=$S and BUNDLEID=$S'.
builtin typeset progname=$0
builtin typeset dontsign=""

function usage
{
   cat << HEREDOC
   
   Usage: $progname [--dontsign]
   
   optional arguments
    -h, --help     show this message and exit
    --dontsign     do not sign code after compilation
   
HEREDOC
}

while [[ $# -gt 0 ]]; do
  case $1 in
   --nosign | --nocodesign | --dontsign )
     shift
     dontsign="yes"
     ;;
   -help | --help | -h | --h | \? )
     usage
     exit 1
     ;;
  esac
done

function compile_mathematics()
{
   builtin typeset -gx TOOLS_SMALL=''
   builtin typeset -gx MAPFILE=''
   builtin typeset -gx UNISON=''
   builtin typeset -gx PLATFLAGS=''
   ninja -C ../distorsion-projection/build_intc-and-arm.ninja
   builtin typeset -gx UNISON=''
   builtin typeset -gx PLATFLAGS=''
   ninja -C ../distorsion-projection/build_intc-and-arm.ninja
   builtin typeset -gx UNISON=''
   builtin typeset -gx PLATFLAGS=''
   ninja -C ../distorsion-projection/build_mz-and-mm.ninja
   builtin typeset -gx UNISON=''
   builtin typeset -gx PLATFLAGS=''
   ninja -C ../distorsion-projection/build_mz-and-mm.ninja
}

function compile_minimum()
{
   builtin typeset -gx MINIMUMPLATFORM='-target arm64-apple-macos12 -D __armv8a__'
   ninja -C ../Minimum -f build.ninja
   mv ../Minimum/Minimum.app/Contents/MacOS/Minimum ../Minimum/Minimum.arm64
   builtin typeset -gx MINIMUMPLATFORM='-target x86_64-apple-darwin21'
   ninja -C ../Minimum -f build.ninja
   mv ../Minimum/Minimum.app/Contents/MacOS/Minimum ../Minimum/Minimum.x86_64
   lipo -create -output ../Minimum.app/Contents/MacOS/Minimum             \
     ../Minimum/Minimum.x86_64 ../Minimum/Minimum.arm64
   if [[ -z "$dontsign" ]]; then
     codesign -f -s ${TEAMID} -o runtime --timestamp -i {BUNDLEID} ../Minimum/Minimum.app
   fi
}

ninja -C Source -f build_armmac.ninja                               || exit 1
ninja -C Source -f build_intcmac.ninja                              || exit 1
lipo -create -output Source/Releases/libTwinbeam_macos.a                  \
 Source/Releases/libTwinbeam-x86_64.a                                     \
 Source/Releases/libTwinbeam_macarm.a                               || exit 1
if [[ -z "$dontsign" ]]; then
  codesign -s ${TEAMID} -f -o runtime --timestamp -i ${BUNDLEID}          \
 Source/Releases/libTwinbeam_macos.a
# codesign -s - -f -o runtime --timestamp libTwinbeam_macarm.a
fi
# ninja -C Source -f build_pic32mz.ninja                              || exit 1
# ninja -C Source -f build_pic32mm.ninja                              || exit 1
# lipo -create ... as of Xcode 13.2 only for arm and intel and not mips.
# compile_mathematics
ninja -C exercise -f build.ninja                                    || exit 1
if [[ -n "$dontsign" ]]; then
  lldb exercise/twinbeam-units
else
  exercise/twinbeam-units
fi
# ninja -C macOS -f :work:.ninja.ninja /work/.ninja.ninja           || exit 1
# ninja -C Bootloader -f build-mm.ninja                               || exit 1
# ninja -C Bootloader -f build-mzda.ninja                             || exit 1
# ninja -C Sprinkle/pdb                                               || exit 1
#  see progress on --<􀖆 assemble.cpp> and --<􀐒 retrospect.c>.
# Examples: dbgout ledflash helloworld fpu bldc usb twinsh turbine radio
# flightcontroller attokernel sdhc
# ninja -C Examples/😐/
# ninja -C ../helixsh build_macos.ninja                               || exit 1
./../Projects/retro-mac.sh retros-compi
./../Projects/retro-mac.sh c-maskin
./../Projects/retro-mac.sh essence-turbin
./../Projects/retro-mac.sh parent-kabinett
# compile_minimum

