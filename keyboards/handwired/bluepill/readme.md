
# BluePill handwired

Keyboards using a BluePill controller (generic Chinese STM32F103C8T6) and based on the [KC64 of Xydane](https://github.com/Xydane/qmk_firmware).

Keyboard Maintainer: [FPazos](https://github.com/fpazos), but I hope to leave the project in better hands.  
Hardware Supported: Bluepill STM32F103C8T6  
Hardware Availability: Everywhere

Make example for BluePill70 (after setting up your build environment):

    make handwired/bluepill/bluepill70:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Read everything before using it.

## Introduction

First of all thanks to [Xydane](https://github.com/Xydane) at [GeekHack](https://geekhack.org/) for his advice and his repository, without it you couldn't be reading this.

That's was an attempt to create a firmware using an STM32F103C8T6, and in a "future", also developing a revision for split keyboards. But...
As I'm mainly a web developer I didn't even get to debug the controller, not to speak about ChibiOS. So I just structured everything, created a working 70% layout and leave the project to someone with more knowledge and patience.

## Resistor fix

If you want to use the Bluepill USB port, it's very likely that you need to solder a 1.8 kΩ between PA12 and 3.3V. That depends on the PC's motherboard but I needed, more info [here](https://wiki.stm32duino.com/index.php?title=Blue_Pill).

## No bootloader

Neither Xydane or I used the bootloader, the code for it is commented and you can use it if you want. I didn't achieve to run it and just used a serial programmer (FTDI, ST-LINK).

## Adding layouts and revisions

If you want to create new layouts just add them to the keymaps folder. If you prefer to develop a more complex revision just copy the bluepill70 folder, rename it and create a new keymap in /keymap.c (I tried to divide the project even more but it didn't worked).

## Pinout

That's the pinout;

        A5  A15   A10   A9  A8  B15  B14  B13   B12  B11  B10  B1   B0      A7      A6      
    B9  ESC| F1 | F2 | F3 | F4 | F5 | F6 | F7 | F8 | F9 | F10| F11| F12| PSC| PGU| PGD
    B8  GRA| 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 0  | '  | ¡  |   BCKS  | DEL
    B7  TAB| Q  | W  | E  | R  | T  | Y  | U  | I  | O  | P  | `  | +  |         | HOM
    B6  CAP| A  | S  | D  | F  | G  | H  | J  | K  | L  | Ñ  | ´  | Ç  |   ENTER | END
    B5  LSI| <  | Z  | X  | C  | V  | B  | N  | M  | ,  | .  | -  |   RSHIF | UP | FNT
    A4  LCT| WIN| ALT|               ESPACE             | ALG| FN | RCT| LEF| DOW| RIG

And the wiring:
ISO  
![Wiring](https://i.imgur.com/ZCaxVzs.jpg)
ANSI  
![Wiring](https://i.imgur.com/dBUJCdD.jpg)

It also uses:  
PC13: Caps Lock led.

Backlight dual color leds, my version is for common anode that's more common, for leds with common anode just replace the palSetPad with palClearPad and viceversa.  
PA1: Backlight color A.  
PA0: Backlight color B.
