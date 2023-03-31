# GeonWorks Frog Mini PCB firmware

![FM_image](https://i.imgur.com/mhCsc6Mh.jpg)

The Frog Mini is a 60% keyboard designed by GeonWorks, with PCB by Gondolindrim.

Two PCB variants are offered: FM-S (solderable) and FM-H (hotswap with Kailh sockets).

* Keyboard Maintainer: [Gondolindrim](https://github.com/gondolindrim)
* Hardware Availability: proprietary PCB sold by [Geon.Works](https://geon.works/)
* Website: [GeonWorks](https://geon.works/pages/frog-mini)

## How to flash

### Enter bootloader

### Release Alpha:

The DFU state in the bootloader can be accessed in 2 ways:

* **Bootmagic reset**: hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: press the button on the back of the PCB
* **Keycode in layout**: press the key mapped to `QK_BOOT` if it is available (ESC key at layer 1 in the default layout)

### Release Beta:

The DFU state in the bootloader can be accessed in 3 ways:

* **Bootmagic reset**: hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: press the button on the back of the PCB, for at least five seconds
* **Keycode in layout**: press the key mapped to `QK_BOOT` if it is available (ESC key at layer 1 in the default layout)

## Compile firmware

### FM-S (solderable)

After accessing the DFU state in your PCB, build the default layout using:

    make geonworks/frogmini/fms:default

### FM-H (hotswap)

After accessing the DFU state in your PCB, build the default layout using:

    make geonworks/frogmini/fmh:default

Then download the resulting binary `*bin` file using `dfu-util` or QMK Toolbox.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
