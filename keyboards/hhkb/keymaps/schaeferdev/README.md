 # QMK HHKB Keymap: schaeferdev

This is my QMK keymap for the Happy Hacking Keyboard Pro 2 alternate controller made by Hasu.


## Movement Layer

The main difference from the Default layer is the introduction of a Movement layer than can be used by holding the right command button. This layer enables to move the mouse and scroll using Page up and Page down. Additionally it allows to use Arrow-keys in VIM-like fashion on hjkl.

I prefer this movement to the default HHKB FN layer as  it allows all my fingers to remain on the home row.

## Minor Changes

- swapped Y and Z (as I am German and used to the different order).
- changed position of Delete Key
- both ` and ~


## Setup (for macOS)
```bash
brew tap osx-cross/avr
brew install avr-gcc
brew install dfu-programmer
```


## Flashing

```bash
make clean
make hhkb:schaeferdev:dfu
```


## Troubleshooting
For some reason I ran into the issue that my CMD key no longer recognized. I am not entirely sure what caused this but the problem occured regardless of the layout I flashed (was also broken for the default hhkb layout). I was able to fix this issue by resetting EEPROM of the keyboard. The easiest way to do this is probably to use the QMK Toolbox.
