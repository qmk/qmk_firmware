kinesis-advantage keyboard firmware
======================

This directory is called alvicstep because https://github.com/alvicstep did the heavy work and took the photos in the doc directory.
alvicstep did NOT do anything related to the QMK implementation, so don't bug him/her. 

There are other ways of replacing the CPU in the kinesis, this one uses jumper wires from the Teensy to the original DIP socket


## Kinesis specific information
This is a port of https://github.com/alvicstep/tmk_keyboard, 
which is a fork of https://github.com/wjanssens/tmk_keyboard, 
which is based on work from https://github.com/chrisandreae/keyboard-firmware

If you replace the kinesis CPU as described in the doc folder, then this code should allow you to use QMK. 
I've tested with a Teensy 2++, remember to change the CPU if you use a 32u4 instead. 

Not yet implemented: 
- Kinesis EEProm reading or writing
- Audio - this should be simple if we remove hardcoded pins from audio.h and switch to E7



## Quantum MK Firmware

For the full Quantum feature list, see [the parent readme.md](/doc/readme.md).

## Building

Download or clone the whole firmware and navigate to the keyboards/kinesis-advantage folder. Once your dev env is setup, you'll be able to type `make` to generate your .hex - you can then use the Teensy Loader to program your .hex file. 

Depending on which keymap you would like to use, you will have to compile slightly differently.

### Default

To build with the default keymap, simply run `make`.

### Other Keymaps

Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create a folder with the name of your keymap in the keymaps folder, and see keymap documentation (you can find in top readme.md) and existant keymap files.

To build the firmware binary hex file with a keymap just do `make` with `keymap` option like:

$ make keymap=[default|jack|<name>]

Keymaps follow the format **__keymap.c__** and are stored in folders in the `keymaps` folder, eg `keymaps/my_keymap/`
