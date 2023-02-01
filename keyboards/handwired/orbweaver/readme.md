# orbweaver

This firmware is for a Razer Orbweaver Chroma keypad, modded to replace the stock MCU
with an Elite Pi RP2040 microcontroller. Mod instructions can be found on [geekhack](https://geekhack.org/index.php?topic=119396.0).

The firmware controls a 6x5 key matrix (4x5 keypad + 6 additional keys
on the thumb pad and up to 4 additional keys added by user). It also controls a
IS31FL3731 RGB Matrix controller (on the Chroma model) via I2C interface. This requires
a single I2C Driver with 20 common anode RGB LEDs. I found that the I2C clock speed must
be slowed down to 100 kHz for the IS31 chip to keep up (the default for RP2040 seems to
be 400 kHz unless specified otherwise).  

The default key map (layer 0) is a generic layer based on the original Razer defaults. 
You can change or add layers as needed, and change static colors in keymap.c

Many thanks to bomtarnes, Drashna, Dasky, sigprof, and casuanoob for helpful discussions
and coding suggestions and snippets.

* Keyboard Maintainer: [a_marmot](https://github.com/a-marmot)
* Hardware Supported: RP2040 + IS31FL3731
* Hardware Availability: [https://geekhack.org/index.php?topic=119396.0](https://geekhack.org/index.php?topic=119396.0)

Make example for this keyboard (after setting up your build environment):

    make handwired/orbweaver:default

Flashing example for this keyboard:

    make handwired/orbweaver:default:flash
    

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* Press and hold the upper left hand key on the main keyboard while you plug in the USB.
* Press and release both reset buttons on the top of the RP2040 inside the modded unit. 
