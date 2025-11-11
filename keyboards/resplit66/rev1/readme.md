# ReSplit66

![resplit66](imgur.com image replace me!)

ReSplit66 is a split orthogonal keyboard with 66 keys build with reversible PCBs:

- Each side use the same PCBs where keys, diodes, leds connectors can be places in both faces.
- Each side has two plates, the mainboard and the optionnal RGB leds boards.
- A wire jumper on mainboard is used to set left or right side.
- Master/slave connection use I2C and slave use SDA to generate IRQ on the master.


* Keyboard Maintainer: [David Girault](https://github.com/dfgweb)
* Hardware Supported: [RESPLIT66_V1](https://gitlab.com/dgirault/resplit66)
* Hardware Availability: DIY

Make example for this keyboard (after setting up your build environment):

    make resplit66:default

Flashing example for this keyboard:

    make resplit66:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **BOOT_SW**: Hold button on the side of the keyboard while plug in the keyboard
* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
