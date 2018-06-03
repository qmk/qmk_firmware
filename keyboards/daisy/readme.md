<<<<<<< HEAD
Daisy keyboard firmware
======================

This is a QMK port for the Daisy a 40% keyboard produced by KPRepublic. The board is available here: http://tinyurl.com/yc26lq22
This is my first port to QMK so apologies if it is a little rough around the edges.

## Quantum MK Firmware

For more info on this firmware (and how to make it your own), head over to [qmk.fm](http://qmk.fm).

## Building

Download or clone the whole firmware and navigate to the
keyboards/daisy folder. Once your dev env is setup, you'll be able to
type `make` to generate your .hex - you can then use atmel FLIP/avrdude
to install the resulting .hex file, or have the `make` process install
it using DFU.

### Default

To build with the default keymap, simply run `make daisy:default` from the root directory (i.e. two levels above this file).

### Other Keymaps
=======
# Daisy

A 40% keyboard kit sold by KPRepublic.

Keyboard Maintainer: westfoxtrot (https://github.com/westfoxtrot)  
Hardware Supported: Daisy PCB Rev.1, Daisy PCB Rev.2  
Hardware Availability: http://tinyurl.com/yc26lq22

Make example for this keyboard (after setting up your build environment):

    make daisy:default

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.


# Other Keymaps


The "default" keymap included is the layout I personally use on the Daisy and the one I have found the most comfortable.

A printable picture showing this layout is available here: https://imgur.com/9mSF0yf


```
$ make daisy:[default|<name>]
```


# Bootloader

I personally had issues with the bootloader on my Daisy PCB and was unable to flash a firmware to the board after the first time. I replaced the bootloader with the one available in the repository at ../../util/bootloader_atmega32u4_1_0_0.hex
