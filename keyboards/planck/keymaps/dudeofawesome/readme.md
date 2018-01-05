# DudeOfAwesome's Planck Layout

A basic Planck layout with simultaneous RGB and audio support.

![Planck Layout](https://i.imgur.com/2p1TEEH.png)

## Features

- Base Layers
  - QWERTY
  - Workman
  - Dvorak
- Audio
- WS2812b RGB backlight

## Building and flashing

1. Put your board in DFU mode with either the button on the bottom, or with a software key in your current firmware
1. Flash:
    ```bash
    $ make make planck/rev4:dudeofawesome:dfu
    ```
