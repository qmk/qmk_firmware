# KMAC PAD

![kmac_pad](https://i.imgur.com/4P1ybgNl.jpg)

KMAC PAD is a num pad keyboard.
It can be used independently, but can also be used by connecting with KMAC keyboard case.

* Keyboard Maintainer: [talsu](https://github.com/talsu)
* Hardware Supported: KMAC PAD
* Hardware Availability: [KBDMania](http://www.kbdmania.net/xe/news/5232321)

Make example for this keyboard (after setting up your build environment):

    make kbdmania/kmac_pad:default
    
Flashing example for this keyboard:

    make kbdmania/kmac_pad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

The PCB is hardwired to run the bootloader if the key at the `FN` position (the only key in first row) is held down when connecting the keyboard.

## PCB

![Imgur](https://i.imgur.com/ML66cvfl.jpg)
![Imgur](https://i.imgur.com/Kr2Wdtkl.jpg)

### Switch Pins

The FN key in the `Row 0` is directly connected to the E2 pin.   
The rest of the rows below that use MATRIX. (`Row 1 ~ Row 5`)
| Row   | Pin                    |
|:-----:| ---------------------- |
| 0     | x (Not in Matrix)      |
| 1     | D0                     |
| 2     | D1                     |
| 3     | D2                     |
| 4     | D3                     |
| 5     | D5                     |

| Column | Pin                   |
|:------:| --------------------- |
| 0      | C7                    |
| 1      | C6                    |
| 2      | B6                    |
| 3      | B5                    |

### Backlight Pins

There are 2 pins for backlight.

The LED of the FN key uses pin `B3`.
All other keys are connected to the `B1` pin.
