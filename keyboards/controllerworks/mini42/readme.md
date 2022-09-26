# mini42

![mini42](https://i.imgur.com/xrSKhqR.png)

*A pre-built, low profile, split mechanical keyboard based on the RP2040 processor*

* Keyboard Maintainer: [Kevin Gee](https://github.com/controller-works)
* Hardware Supported: *mini42 split ergonomic keyboard*
* Hardware Availability: *https://controller.works/products/mini42-low-profile-ergonomic-keyboard* Hardware is available as pre-built units only.

Make example for this keyboard (after setting up your build environment):

```sh
    make controllerworks/mini42:default
```

Flashing example for this keyboard:

```sh
    make controllerworks/mini42:default:flash
```
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Features
- Highly integrated design with microcontroller, USB and TRRS connectors, and OLED all integrated on the main board with no secondary modules
- RP2040 processor by Raspberry Pi Foundation running at 130 MHz with 16MB flash memory
- CNC milled aluminum case with only 8mm thickness
- "PCB art" shine through back plate with gold surface finish
- 128x32 OLED on each keyboard half
- 42 per-key RGB LEDs and 12 backlight RGB LEDS are individually addressable
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

## Pin Assignment
| Name   | Pin  |  Left Row | Left Column | Right Row | **Right Column |
|--------|------|-----------|-------------|-----------|--------------|
| LED    | GP0  |           |             |           |              |
| DATA   | GP1  |           |             |           |              |
| DATA2* | GP28 |           |             |           |              |
| KEY0   | GP2  | 0         | 0           | 4         | 0            |
| KEY1   | GP3  | 0         | 1           | 4         | 1            |
| KEY2   | GP4  | 0         | 2           | 4         | 2            |
| KEY3   | GP5  | 0         | 3           | 4         | 3            |
| KEY4   | GP6  | 0         | 4           | 4         | 4            |
| KEY5   | GP7  | 0         | 5           | 4         | 5            |
| KEY6   | GP8  | 1         | 0           | 5         | 0            |
| KEY7   | GP9  | 1         | 1           | 5         | 1            |
| KEY8   | GP10 | 1         | 2           | 5         | 2            |
| KEY9   | GP11 | 1         | 3           | 5         | 3            |
| KEY10  | GP12 | 1         | 4           | 5         | 4            |
| KEY11  | GP13 | 1         | 5           | 5         | 5            |
| KEY12  | GP14 | 2         | 0           | 6         | 0            |
| KEY13  | GP15 | 2         | 1           | 6         | 1            |
| KEY14  | GP16 | 2         | 2           | 6         | 2            |
| KEY15  | GP17 | 2         | 3           | 6         | 3            |
| KEY16  | GP18 | 2         | 4           | 6         | 4            |
| KEY17  | GP19 | 2         | 5           | 6         | 5            |
| KEY18  | GP20 | 3         | 0           | 7         | 0            |
| KEY19  | GP21 | 3         | 1           | 7         | 1            |
| KEY20  | GP22 | 3         | 2           | 7         | 2            |
| SDA    | GP24 |           |             |           |              |
| SCL    | GP25 |           |             |           |              |

\*DATA2 on production units, not connected on prototype units

\** Right Column numbers run right (pinky position) to left (thumb position)