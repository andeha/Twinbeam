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
    case Coretimer: break;
    case Coresoftware0: break;
    case Realtimeclock: break;
    }
}

extern "C"
void
mips_general_exception()
{
    switch ((🔎Cause() & 0b1111100)>>2) {
    case 4: printf("Load from illegal address"); break;
    case 5: printf("Store to illegal address"); break;
    case 6: printf("Bus error on instruction fetch"); break;
    case 7: printf("Bus error on data reference"); break;
    case 8: printf("Syscall"); break;
    case 9: printf("Break instruction executed"); break;
    }
}

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
