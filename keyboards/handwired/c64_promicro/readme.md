# c64 promicro

*C64 keyboard wired to a pro micro USB board*

<img src="https://i.imgur.com/kAepQeL.jpeg" alt="c64_promicro Top" width="50%">

**C64 ProMicro keyboard** is featured on:
[![Hackaday](https://img.shields.io/badge/Featured%20on-Hackaday-black?logo=hackaday&logoColor=white)](https://hackaday.com/2025/12/09/keebin-with-kristina-the-one-with-the-c64-keyboard/)

* Keyboard Maintainer: [jeanpihet](https://github.com/jeanpihet)
* Hardware Supported: promicro
* Hardware Availability: [Sparkun Pro Micro](https://www.sparkfun.com/pro-micro-5v-16mhz.html)

Keyboard matrix from http://sta.c64.org/cbm64kbdlay.html

Mod for Shift Lock remapped to Mouse & Fn mode: rewire key from col[7], row[1] (Red/White wire) to row[8] (Black wire), cf. pics below.

## Wiring
Mapping of C64 keyboard to Arduino ProMicro pins

|C64 kbd pin | Arduino pin | Arduino port pin |
|---         | ---         | ---              |
| *Rows*     |
| 20         | 2  - SDA    | PD1              |
| 19         | 3  - SCL    | PD0              |
| 18         | 4  - A6     | PD4              |
| 17         | 5           | PC6              |
| 16         | 6  - A7     | PD7              |
| 15         | 7           | PE6              |
| 14         | 8  - A8     | PB4              |
| 13         | 9  - A9     | PB5              |
| 3          | 1  - RX     | PD2              |
| *Columns*  |
| 12         | 10 - A10    | PB6              |
| 11         | 16 - MOSI   | PB2              |
| 10         | 14 - MISO   | PB3              |
| 9          | 15 - SCLK   | PB1              |
| 8          | 18 - A0     | PF7              |
| 7          | 19 - A1     | PF6              |
| 6          | 20 - A2     | PF5              |
| 5          | 21 - A3     | PF4              |
| 4          | N/C         |                  |
| 2          | N/C         |                  |
| 1          | 0  - TX     | PD3              |
|            |

## Wiring pics

Bottom:

<img src="https://i.imgur.com/d9vpBy1.jpeg" alt="c64_promicro Bottom" width="50%">


Wiring:

<img src="https://i.imgur.com/k9sUKNM.jpeg" alt="c64_promicro Wiring" width="50%">

Shift lock mod details:

<img src="https://i.imgur.com/vbdzYq9.jpeg" alt="c64_promicro Shift Lock Mod" width="50%">

## Build and flash
Make example for this keyboard (after setting up your build environment):
```
    qmk compile -kb handwired/c64_promicro -km full
```

Flashing example for this keyboard:
```
    qmk flash -kb handwired/c64_promicro -km full
```


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the INST/DEL key (at (0,0) in the matrix) and plug in the keyboard
* **Physical reset button**: Briefly press twice the reset button on the back of the PCB - this has to be soldered to the board
