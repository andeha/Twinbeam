/*  Uart.cpp | Symbols on-a-line. */

#include <Twinbeam.h>

/* Compile with: ./artᵐⁱᵖˢ.ksh Uart */

#include <pic32rt/mips.hpp>
#include <pic32rt/pic32mz.hpp>
#include <pic32rt/pic32mzda.hpp>
#include <pic32rt/stable.hpp>

int
main(
  int argc,
  const char * argv[]
)
{  InitMZDAStarterBoard();
    print("Hello from inside on the other side! 🖋😐\n");
    /* See --<Additions>--<Fossilate.h>{WaitTerminal} for details on:
      auto ping = ^(bool &stop) { print("."); };
again:
      char32_t uc;
      int y = WaitTerminal(100, 10, ping, &uc);
      if (y) { goto unagain; } else { 📨😐 } */
    while (1) { ; }
unagain:
    print("timed out, possibly failed\n");
    return 0;
}

/* 🏁 ⚑ */
