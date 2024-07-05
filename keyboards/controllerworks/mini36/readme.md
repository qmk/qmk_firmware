# mini36

![mini36](https://i.imgur.com/JwhiE9ll.png)
![mini36PCB](https://i.imgur.com/6NjZ8Cql.jpg)

*A pre-built, low profile, split mechanical keyboard with 36 keys based on the RP2040 processor*

* Keyboard Maintainer: [Kevin Gee](https://github.com/controller-works)
* Hardware Supported: *mini36 split ergonomic keyboard*
* Hardware Availability: *https://controller.works/products/mini36-low-profile-ergonomic-keyboard* Hardware is available as pre-built units only.

Make example for this keyboard (after setting up your build environment):

```sh
    make controllerworks/mini36:default
```

Flashing example for this keyboard:

```sh
    make controllerworks/mini36:default:flash
```
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Features
- Highly integrated design with microcontroller, USB and TRRS connectors, and OLED all integrated on the main board with no secondary modules
- RP2040 processor by Raspberry Pi Foundation running at 130 MHz with 16MB flash memory
- CNC milled aluminum case with only 8mm thickness
- "PCB art" shine through back plate with gold surface finish
- 128x32 OLED on each keyboard half
- 36 per-key RGB LEDs and 12 backlight RGB LEDS are individually addressable
- ESD and over-current protection on USB and TRRS connectors
- Reset and boot tactile switches
- USB C host connection
- Hot swap connectors for Kailh Chocolate PG1350 switches
- Chocolate key spacing (18mm horizontal x 17mm vertical) 
## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the upper left key on the left hand keyboard half or the upper right key on the right hand keyboard half while plugging in USB
* **Physical reset button**: Press the RST button twice, rapidly
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available