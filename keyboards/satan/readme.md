# Satan GH60

A clone of the GH60 60% keyboard, with full backlighting support.

Keyboard Maintainer: QMK Community  
Hardware Supported: Satan GH60 PCB  
Hardware Availability: https://www.1upkeyboards.com/shop/controllers/gh60-satan-pcb/

Make example for this keyboard (after setting up your build environment):

    make satan:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## RGB Underglow (WS2812B LED Strip)

This board also supports underglow with a slight mod.

Connect the DIN pad of the LED strip to PE2 on the ATmega32U4, like so:

![controller](https://i.imgur.com/9vyRBoT.jpg)

Then connect VCC and GND to pins 1 and 6 at the bottom of the PCB:

![power](https://i.imgur.com/pHMZHLP.jpg)

## ISP Header

If you want to flash another bootloader (such as QMK-DFU), or can't get into the bootloader in the first place, the row of pins at the bottom can be used to ISP flash the board:

| 1 |  2 | 3 |  4 |   5 | 6 |  7 |
|---|----|---|----|-----|---|----|
|VCC|MISO|SCK|MOSI|RESET|GND|*NC*|
