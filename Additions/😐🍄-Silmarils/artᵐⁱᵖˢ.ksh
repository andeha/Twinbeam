#!/usr/bin/env /bin/ksh

# The script is 'read' by 'a shell' and a binary is 'loaded' followed by 
# 'executed'. Following Unix, for details on execution, enter 'man dyld' at 
# prompt for details. Also reconsider the abstraction `bee-keeper`. Time 
# while in run; relative time in model.

dryrun=""
verbose=""
simulator=""

# trap 'print "You hitted ctrl-c"'                    INT
# trap 'print "You tried to kill me!"'               TERM
# trap 'print "...and changed the window size"      WINCH # Width:text
# trap 'print "I am not universally accepted"' 𝟺kbWritten
# trap 'call usage()'                             COMPOSE
# ...another language:
# untrap                                        INT, TERM
# trap -                                         INT TERM
# ...so:
# untrap                                         INT TERM
# de/retrap                                      INT TERM

function usage
{
   cat << HEREDOC
   
   Usage: $progname [-s] project-infix
   
   optional arguments:
     -h, --help           show this help message and exit
     -s, --simulator      succumb to inexact sw simulation
     -v, --verbose        increase the verbosity of script
     --dry-run            restrain to find; not execute
   
HEREDOC
}

while [ $# -gt 0 ]; do
  case $1 in
    -s | --simulator)
      shift
      simulator="yes"
      ;;
    -v | --verbose)
      shift
      verbose="yes"
      ;;
    -dry-run)
      shift
      dryrun="yes"
      ;;
    -help | --help | -h | --h | -\? )
      usage
      exit 0
      ;;
    * )
      fullfilename="🥽 $1.cpp"
      fname="$1"
      ;;
  esac
  shift
done

tools=~/Projects/mips-tools/10.0.0/
glue=~/Projects/mips-tools
MDBPATH=/Applications/microchip/mplabx/v5.20/mplab_platform/bin/
PIC32DEVICE=PIC32MZ2064DAB288
pdb=../../Sprinkle/pdb/pdb
script=../../pic32rt/pic32one.ld
lib=../../Source/Releases/libTwinbeam_pic32mz.a
rt=../../Source/llvmʳᵗ³.cpp
boot=../../Bootloader/Releases/bootloader_mz_39e78938.hex
cc=$tools/clang-10
ld=$tools/lld
# For some versions of llvm the executable above is named `ld.lld`.

if [[ -n "$verbose" ]]; then
  echo "Compiling $fullfilename"
fi

objectfile="${fname}.o"
binary="${fname}_mzda"

echo "fullfilename=${fullfilename}"
echo "fname=${fname}"
echo "objectfile=${objectfile}"
echo "binary=${binary}"

$cc @ccargs_mz -o $objectfile -DSHA1GIT=`git log -1 '--pretty=format:%h'` -c "$fullfilename"
$cc @ccargs_mz -o rtllvm.o -c $rt
$ld -T $script -o $binary $objectfile rtllvm.o $lib
$glue/llvm2pic32 -b $boot $binary > "${fname}.hex"
# 'llvm2pic32 -s' not used.
rm $binary

if [[ -n "$dryrun" ]]; then
  echo "Dry-run. No installable created."
  exit 0
fi

# Start the simulator/debugger with %prompt> pdb myprogram.hex
function debug
{
  if [[ -n "$simulator" ]]; then
    $pdb -s "${filename}.hex"
# ~/Projects/Monitor/Apps/bin/mdb setup_mzda_simulator 2>/dev/null
  else
    $pdb "${filename}.hex"
# ~/Projects/Monitor/Apps/bin/mdb setup_mzda_target 2>/dev/null
  fi
}

