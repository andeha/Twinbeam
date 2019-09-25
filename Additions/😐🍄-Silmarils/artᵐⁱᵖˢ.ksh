#!/usr/bin/env /bin/ksh

# The script is 'read' by 'a shell' and a binary is 'loaded' followed by 
# 'executed'. Following Unix, for details on execution, enter 'man dyld' at 
# prompt for details.

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
      if [[ -s $fullfilename ]]; then
        # `printf` and UTF-8/Unicode broken in 'printf $fullfilename'
        # `basename` and UTF-8/Unicode broken in 'filename=$(basename "$fullfilename")'
        fname="${filename%.*}"
        ext="${filename##*.}"
      else
        echo "unknown option or file: $1"
        usage
        exit 1
      fi
      ;;
  esac
  shift
done

tools=~/Projects/mips-tools/9.0.0/
glue=~/Projects/mips-tools
MDBPATH=/Applications/microchip/mplabx/v5.20/mplab_platform/bin/
PIC32DEVICE=PIC32MZ2064DAB288
pdb=../../Sprinkle/pdb/pdb
script=../../pic32rt/pic32one.ld
lib=../../Source/Releases/libTwinbeam_pic32mz.a
rt=../../Source/llvmʳᵗ³.cpp
cc=$tools/clang-9

# echo $fullfilename
# echo $fname
# echo $ext

if [[ -n "$verbose" ]]; then
  echo "Compiling $fullfilename"
fi

objectfile="${fname}.o"
$cc @ccargs_mz -o $objectfile -c "${fullfilename}"
$cc @ccargs_mz -o llvmʳᵗ³.o -c $rt
$tools/ld.lld -T $script -o $fname $objectfile llvmʳᵗ³.o $lib

$glue/llvm2pic32 -b pic32mz.hex $fname 
# [-s] not used

if [[ -n "$dryrun" ]]; then
  exit 0
fi

# %prompt> pdb myprogram.hex
function debug
{
  if [[ -n "$simulator" ]]; then
    $pdb -s "$filename" ".hex"
# ~/Projects/Monitor/Apps/bin/mdb setup_mzda_simulator 2>/dev/null
  else
    $pdb "$filename" ".hex"
# ~/Projects/Monitor/Apps/bin/mdb setup_mzda_target 2>/dev/null
  fi
}

