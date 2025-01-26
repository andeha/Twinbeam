#!/usr/bin/env /bin/zsh

builtin typeset TEAMID='A12B34C5DE'
# \also prompt> schema 'TEAMID=$S and BUNDLEID=$S'.
builtin typeset progname=$0
builtin typeset artefact="Release"
builtin typeset dontsign=""

builtin typeset sha1git=`git log -1 '--pretty=format:%h'`

function usage 
{
   cat << HEREDOC
   
   Usage $progname [--dontsign]
   
   optional parameters
    -h, --help     show this message and exit
    --dontsign     do not sign code after compilation 
   
HEREDOC
}

while [[ $# -gt 0 ]]; do 
  case $1 in 
   --nosign | --nocodesign | dontsign )
     shift
     dontsign="yes"
     ;;
   -help | --help | -h | --h | \? )
     usage
     exit 1
     ;;
   esac
done

if [[ ! -d $artefact ]]; then 
  mkdir $artefact
fi

function compile_twinbeam 
{
   local material=(
  "Source/impress-length.c"
  "Source/institut-macos.c"
  "Source/pamphlet-symbol.c"
  "Source/serial-symbol.c"
  "Source/stochast-symbol.c"
  "Source/unstall-coalesc.c"
  "../distorsion-projection/abundan-invert.c"
  "../distorsion-projection/captu-radio.c"
  "../distorsion-projection/circula-convers.c"
  "../distorsion-projection/iumoid-twothree.c"
  "../distorsion-projection/napier-exponen.c"
  "../distorsion-projection/satur-calculat.c"
  "../distorsion-projection/sequent-sinuativ.c"
   )
   for file in $material
   do
     /usr/bin/clang -I . -target $2 -DSHA1GIT=\"$sha1git\" -c $file          \
      -o $artefact/$file:t:r.o
   done
   ar rcs $artefact/$1                                                       \
    $artefact/impress-length.o $artefact/institut-macos.o                    \
    $artefact/pamphlet-symbol.o $artefact/serial-symbol.o                    \
    $artefact/stochast-symbol.o $artefact/unstall-coalesc.o                  \
    $artefact/abundan-invert.o $artefact/captu-radio.o                       \
    $artefact/circula-convers.o $artefact/iumoid-twothree.o                  \
    $artefact/napier-exponen.o $artefact/satur-calculat.o                    \
    $artefact/sequent-sinuativ.o
   rm Release/impress-length.o Release/institut-macos.o                      \
    Release/pamphlet-symbol.o Release/serial-symbol.o                        \
    Release/stochast-symbol.o Release/unstall-coalesc.o                      \
    Release/abundan-invert.o Release/captu-radio.o                           \
    Release/circula-convers.o Release/iumoid-twothree.o                      \
    Release/napier-exponen.o Release/satur-calculat.o                        \
    Release/sequent-sinuativ.o
   
}

compile_twinbeam libTwinbeam-x86_64.a x86_64-apple-darwin21
compile_twinbeam libTwinbeam-macarm.a arm64-apple-macos12

lipo -create -output $artefact/libTwinbeam-macos.a                           \
 $artefact/libTwinbeam-x86_64.a                                              \
 $artefact/libTwinbeam-macarm.a                                       || exit 1

rm $artefact/libTwinbeam-x86_64.a $artefact/libTwinbeam-macarm.a

if [[ -z "$dontsign" ]]; then 
  codesign -s ${TEAMID} -f -o runtime --timestamp $artefact/libTwinbeam-macos.a
fi



