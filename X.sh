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
   local mathfiles=(
  "../distorsion-projection/abundan-invert.c"
  "../distorsion-projection/captu-radio.c"
  "../distorsion-projection/circula-convers.c"
  "../distorsion-projection/iumoid-twothree.c"
  "../distorsion-projection/napier-exponen.c"
  "../distorsion-projection/satur-calculat.c"
  "../distorsion-projection/sequent-sinuativ.c"
   )
   for file in $mathfiles
   do
     xcrun clang -I . -target x86_64-apple-darwin21 -c $file -o /tmp/$file:t:r.o
   done
   ar rcs ./Source/Releases/libTwinbeam-x86_64.a                            \
     /tmp/abundan-invert.o  /tmp/captu-radio.o    /tmp/circula-convers.o    \
     /tmp/iumoid-twothree.o /tmp/napier-exponen.o /tmp/satur-calculat.o     \
     /tmp/sequent-sinuativ.o
#   builtin typeset sha1git=`git log -1 '--pretty=format:%h'`
#   builtin typeset armcpu="lib${UNISON}_$sha1git.a"
   rm /tmp/abundan-invert.o  /tmp/captu-radio.o    /tmp/circula-convers.o
   rm /tmp/iumoid-twothree.o /tmp/napier-exponen.o /tmp/satur-calculat.o
   rm /tmp/sequent-sinuativ.o
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

compile_mathematics

lipo -create -output Source/Releases/libTwinbeam-macos.a                  \
 Source/Releases/libTwinbeam-x86_64.a                                     \
 Source/Releases/libTwinbeam_macarm.a                               || exit 1

if [[ -z "$dontsign" ]]; then
  codesign -s ${TEAMID} -f -o runtime --timestamp -i ${BUNDLEID}          \
 Source/Releases/libTwinbeam-macos.a
# codesign -s - -f -o runtime --timestamp libTwinbeam_macarm.a
fi
# ninja -C Source -f build_pic32mz.ninja                              || exit 1
# ninja -C Source -f build_pic32mm.ninja                              || exit 1
# lipo -create ... as of Xcode 13.2 only for arm and intel and not mips.
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

