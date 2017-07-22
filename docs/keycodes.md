# Overview

When defining a [keymap](keymap.md) each key needs a valid key definition.

This page documents the symbols that correspond to keycodes that are available to you in QMK.

## Basic keycodes (`0x00` - `0xFF`)

[Basic keycodes](basic_keycodes.md) in QMK are based on [HID Usage Keyboard/Keypad Page(0x07)](http://www.usb.org/developers/hidpage/Hut1_12v2.pdf) with following exceptions:

* `KC_NO` = 0 for no action
* `KC_TRNS` = 1 for layer transparency
* internal special keycodes in the `0xA5-DF` range (tmk heritage).

## Quantum keycodes (`0x0100` - `0xFFFF`)

[Quantum keycodes](quantum_keycodes.md) allow for easier customisation of your keymap than the basic ones provide, without having to define custom actions.
