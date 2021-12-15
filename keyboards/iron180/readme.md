# Iron180 QMK firmware folder

![iron180](https://i.imgur.com/zHcZoxa.png)

## Introduction

This is the QMK Firmware repository for the Iron180 PCB, a keyboard designed by [Smith and Rune](https://smithrune.com/) and PCB designed by [Gondolindrim](http://github.com/Gondolindrim).

The Iron180 PCB is a F13 TKL PCB with ALPS switches support. It also supports in-switch single-color LEDs and a multi-layout design for default or 7U bottom row, ISO layout, split backspace and right shift.

As of november 2021, the Group Buy of Iron180 is already over and extras were not sold yet. See the [GB page](https://geekhack.org/index.php?topic=109513) for more information.

## How to flash

### Enter bootloader

The DFU state in the bootloader can be accessed in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard with the key pressed;
* **Physical reset button**: press the button on the front of the PCB, next to caps lock, for at least five seconds;
* **Keycode in layout**: Press the key mapped to `RESET` if it is available (ESCAPE key in layer 1 of the default layout);

## Compile firmware and flash

To build the default layout for this keyboard (after setting up your build environment), use:

    make iron180:default

Then, after accessing the DFU state, use a tool like `dfu-util` or the QMK Toolbox to download that firmware into your PCB. To directly compile-and-flash the PCB after it is put into a DFU state, use

    make iron180:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
