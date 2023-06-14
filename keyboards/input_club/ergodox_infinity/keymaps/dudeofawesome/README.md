# DudeOfAwesome's ErgoDox Infinity Layout

A basic ErgoDox layout with Planck-like tri-layer support.

![ErgoDox Layout](https://i.imgur.com/ae0Phzb.png)

## Features

- Base Layers
    - QWERTY
    - Workman
    - Dvorak
    - Colemak
- Planck-like tri-layer
- In-progress gaming layer
- Numpad layer
    ![numpad layer](https://i.imgur.com/oHDYpzf.png)
- LCD colors are linked together, like the default KLL firmware

## Building and flashing

1. Put your board in DFU mode with either the button on the bottom, or with a software key in your current firmware
1. Flash left half:
    ```bash
    $ make ergodox_infinity:dudeofawesome:dfu-util
    ```
1. Flash right half:
    ```bash
    $ make ergodox_infinity:dudeofawesome:dfu-util MASTER=right
    ```
