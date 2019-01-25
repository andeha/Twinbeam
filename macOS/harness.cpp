//
//  main.cpp
//  Unittests for Twinbeam on macOS
//

#include <Twinbeam.h>

#include <stdio.h>
uint8_t getutf8() { return (uint8_t)getc(stdin); }
void putch(uint8_t utf8) { putchar(utf8); }

auto Putch = ^(char utf8) { putch(utf8); };
auto Alloc = ^(__builtin_int_t bytes) { return malloc(bytes); };

int main(int argc, const char * argv[])
{
    RunUnitTests(argv[0]);
    return 0;
}
