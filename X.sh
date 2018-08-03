ninja -C Source -f build_macOS.ninja
ninja -C Source -f build_pic32mz.ninja
ninja -C macOS -f build_test.ninja
ninja -C Bootloader
ninja -C Examples/dbgout
ninja -C Examples/ledflash
ninja -C Examples/helloworld
ninja -C Examples/fpu
ninja -C Examples/bldc
ninja -C Examples/usb
ninja -C Examples/twinsh
ninja -C Examples/turbine
ninja -C Examples/flightcontroller
ninja -C Examples/😐/
ninja -C Additions -f build_macOS.ninja
