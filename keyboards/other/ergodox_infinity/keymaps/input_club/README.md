# Input Club ErgoDox Infinity Layout

A basic ErgoDox layout that duplicates the default Input Club layout

## Features

Base Layers

- QWERTY
- Function Keys
- Numpad

## Building and flashing

1. Put your board in DFU mode with either the button on the bottom, or with a software key in your current firmware
2. Flash left half:
    ```bash
    make ergodox_infinity:input_club:dfu-util
    ```
3. Flash right half:
    ```bash
    make ergodox_infinity:input_club:dfu-util MASTER=right
    ```
