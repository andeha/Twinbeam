/*  Helloworld for Twinbeam. */

#include <Twinbeam.h>
#include <mips.hpp>
#include <pic32mz.hpp>
#include <stable.hpp>

extern "C"
void
Isr()
{
    switch (🔎IRQ()) {
    case Coretimer: break; // Core Timer Interrupt
    case Coresoftware0: break; // Core Software Interrupt 0
    case Realtimeclock: break; // Real Time Clock
    }
}

extern "C"
void
mips_general_exception()
{
    switch ((🔎Cause() & 0b1111100)>>2) {
    case 4: break; // Load from illegal address
    case 5: break; // Store to illegal address
    case 6: break; // Bus error on instruction fetch
    case 7: break; // Bus error on data reference
    case 8: break; // Syscall
    case 9: break; // Break instruction executed
    }
}

Context ctx;
auto stdout = ^(char utf8) { putch(utf8); };
auto stdin = ^{ return getutf8(); };
auto alloc = ^(__builtin_int_t bytes) { return malloc(bytes); };

int
main(
  int argc,
  const char *argv[]
)
{
    
#ifdef __MZ__
    mz_init();
#endif
    
    InitUART();
    
    printf("Hello World (%s)\xA\xA", SHA1GIT);
    
    while (1) { putch('X'); }
    
    return 0;
}
