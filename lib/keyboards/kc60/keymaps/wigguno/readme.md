Wigguno's KC60 Layout
======================

## Quantum MK Firmware
For the full Quantum feature list, see [the parent readme.md](/readme.md).

## Changes from default QMK layout
The default QMK layout for KC60 does not have a function layer. It also has the bootloader-mode reset key bound. This keymap fixes both of these by adding a sensible function layer (including moving the reset key onto it, far away from the FN key).

### Changes from the default KC60 layout
The default KC60 layout is good, but it was missing media keys. I've added previous, play/pause and next. I've also removed some of the keys from the function layer I didn't use.

### Build
To enable NKRO you must be in the keymaps/wigguno directory when running make.
