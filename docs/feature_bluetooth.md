# Bluetooth

## Bluetooth Functionality

This requires [some hardware changes](https://www.reddit.com/r/MechanicalKeyboards/comments/3psx0q/the_planck_keyboard_with_bluetooth_guide_and/?ref=search_posts), but can be enabled via the Makefile. The firmware will still output characters via USB, so be aware of this when charging via a computer. It would make sense to have a switch on the Bluefruit to turn it off at will.

<!-- FIXME: Document bluetooth support more completely. -->

## Bluetooth Keycodes

This is used when multiple keyboard outputs can be selected. Currently this only allows for switching between USB and Bluetooth on keyboards that support both.

|Name      |Description                                   |
|----------|----------------------------------------------|
|`OUT_AUTO`|Automatically switch between USB and Bluetooth|
|`OUT_USB` |USB only                                      |
|`OUT_BT`  |Bluetooth only                                |
