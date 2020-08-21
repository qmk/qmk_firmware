## Flashing Keyboard

1. Install `dfu` tools:

    brew tap osx-cross/avr
    brew install avr-libc
    brew install dfu-programmer

2. Move to this directory.
3. Hit the reset button on the keyboard.
4. run `make dfu`.

## The Keymap

This keymap is designed for a rev3 Planck Keyboard.

The default layer is QWERTY. The raise layer has a ten key on the right
and common programming punctuation on the left. The lower layer provides the
rest of the symbols, mostly mapped with the ten key numbers.

The normal right shift key uses the `MT` macro to trigger Enter on tap and right
shift when held.
