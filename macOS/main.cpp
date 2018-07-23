//
//  main.cpp
//  Twinbeam for macOS Unittests
//

#include <Twinbeam/Twinbeam.h>

auto alloc = ^(__builtin_int_t bytes) { return malloc(bytes); };

int main(int argc, const char * argv[])
{
    RunUnitTests(argv[0]);
    return 0;
}
