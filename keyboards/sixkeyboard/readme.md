Techkeys SixKeyBoard
===

Keyboard Maintainer: QMK Community
Hardware Supported: Techkeys SixKeyBoard PCB
Hardware Availability: http://techkeys.us/collections/accessories/products/sixkeyboard

Make example for this keyboard (after setting up your build environment):

    make sixkeyboard-default

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.

## Hardware Info

The schematic is like this:

```
 switches       leds
,--+--+--.   ,--+--+--.
|C7|B7|B5|   |C6|B6|B4|
+--+--+--+   +--+--+--+
|D6|D1|D4|   |D5|D2|D3|
`--+--+--'   `--+--+--'
```

The LED on the bottom is `C4`. All 7 of the leds are turned on when the keyboard boots-up in the `sixkeyboard.c` file - backlight_enable is not required. The MCU is an Atmega16u2, so the flash memory is limited to 0x3000 bytes - the current setup uses just about all of that! I'm sure things can be opitimised a bit.

There is a jumper on the bottom of the board (next to the USB port) that serves as a reset button - I drilled a hole in my case to allow for quick access via a screwdriver/metal object.
