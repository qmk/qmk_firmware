# tg4x

![tg4x](https://imgur.com/gallery/OM9EhMF)

The dirt cheap 40%

Keyboard Maintainer: [mythosmann](https://github.com/mythosmann)  
Hardware Supported: tg4x pcb, pro micro  
Hardware Availability: https://github.com/mythosmann/tg4x

Make example for this keyboard (after setting up your build environment):

    make tg4x:default_ansi for 6.25u spacebar
    make tg4x:default_ansi_split for split spacebar
    make tg4x:default for tg3 mod

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Command to flash dfu bootloader avrdude.exe -c usbtiny -p m32u4 -P usb -U flash:w:"tg4x_default_split_ansi_production.hex":a -U lfuse:w:0x5E:m -U hfuse:w:0xD9:m -U efuse:w:0xC3:m -U lock:w:0x3F:m
avrdude.exe -p atmega32u4 -c stk500v1 -b 19200 -U flash:w:"Q:\bootloader_atmega32u4_1_0_0.hex":i -P COM27 -U efuse:w:0xC3:m -U hfuse:w:0xD9:m -U lock:w:0x3F:m
avrdude -c avrisp -P COM27 -p atmega32u4 -U flash:w:"Q:\bootloader_atmega32u4_1_0_0.hex":i
