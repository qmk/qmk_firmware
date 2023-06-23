# Aurora Sweep's Debug Keymap

Due to the complex layer setup, the default keymap for the Aurora Sweep is relatively hard to debug.
This debug keymap should make that a lot easier.

## Keys

![Keys](https://raw.githubusercontent.com/splitkb/qmk_firmware/assets/aurora/sweep/keymaps/debug/keys.png)

The left side uses lowercase letters, the right side uses uppercase ones.

## Encoders

Encoders output a number of 0 to 3, depending on the installed position.
These correspond to the index used for custom encoder code.

The number is followed by either a `+` or a `-`, depending on the direction turned.

## LEDs

Both underglow and per-key RGB should be fading between red and off.

## OLEDs

Both the primary and secondary side should be filled with characters.
