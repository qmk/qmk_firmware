# JotPad16

![JotPad16](https://i.imgur.com/RwmqWuS.jpg)

A ortholinear keypad (4x4) made by jotix.

Keyboard Maintainer: [jotix](https://github.com/jotix)  
Hardware Supported: Arduino Pro Micro  

### Arduino Pro Micro Pinout

| rows        | 0  | 1  | 2   | 3   |
|-------------|----|----|-----|-----|
| arduino pin | 10 | 16 | RXI | TX0 |
| qmk pin     | B6 | B2 | D2  | D3  |

| columns     | 0  | 1  | 2  | 3  |
|-------------|----|----|----|----| 
| arduino pin | 9  | 8  | 14 | 15 |
| qmk pin     | B5 | B4 | B3 | C3 |

|             | QMK led   | Backlight |
|-------------|-----------|-----------|
| Arduino pin | 7         | 6         |
| qmk pin     | E6        | D7        |

### Compiling the Firmware

Make example for this keyboard (after setting up your build environment):

    make handwired/jotpad16:default

### The Default Keymap

![Default Keymap](https://i.imgur.com/VJZcFRN.jpg)

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


