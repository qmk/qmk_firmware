# Pathfinder the keyboard matrix finder

Pathfinder is a general-purpose keyboard matrix reverse engineering tool and itself qmk keyboard firmware.

A multimeter is usually used to determine the matrix of the keyboard. But there are people who don't want to get intimate with PCBs. (That's me!) This code is the firmware to figure out the matrix of the keyboard, which is not normally registered in QMK.

* Keyboard Maintainer: [caffeinism](https://github.com/caffeinism)
* Hardware Supported: STM32F103
* Hardware Availability: 

Make example for this keyboard (after setting up your build environment):

    make caffeinism/pathfinder:default

Flashing example for this keyboard:

    make caffeinism/pathfinder:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

This is an easy process in a few steps.

1. Select the appropriate MCU and BOOTLOADER from rules.mk.
2. In config.h, enter the appropriate pin list you want to test. Unfortunately, qmk only supports up to 32 pins.
3. Specify the appropriate LOOP_TIMEOUT in config.h. The keyboard runs the main loop and returns to the bootloader after this time. Prevents your keyboard from becoming a brick!
4. Do ```qmk compile -kb caffeinism/pathfinder -km default``` and ```qmk flash -kb caffeinism/pathfinder -km default```.
5. After running ```qmk console```, connect the keyboard, there may be some keys that blink by default. In this case, remove those pins from MATRIX_ALL_PINS.

![blink](https://i.imgur.com/alf1zVv.png)
![target](https://i.imgur.com/n0E5YPC.png)
![delete](https://i.imgur.com/dvOLccN.png)

7. Run again ```qmk compile -kb caffeinism/pathfinder -km default```, ```qmk flash -kb caffeinism/pathfinder -km default``` and ```qmk console```.
8. And press the key! You can easily find your matrix.

![result](https://i.imgur.com/AYYvLxJ.png)

---

The following is an explanation of how the code is also commented on.
```
        We're going to try to find the culprit.
        Let's look at an example matrix.

           A1 A2 A3 B1 B2 B3
        A1 X  ?  ?  ?  ?  ?
        A2 ?  X  ?  ?  ?  ?
        A3 ?  ?  X  ?  ?  ?
        B1 ?  ?  ?  X  ?  ?
        B2 ?  ?  ?  ?  X  ?
        B3 ?  ?  ?  ?  ?  X

        We find a switch that goes into "?".
        Any pin can be an input or an output.

        For example, let's say a real keyboard has the following matrix:
           A1 A3
        B1 a  b
        B2 c  d

        Here's what the matrix looks like when you press each key

           A1 A2 A3 B1 B2 B3
        A1 X  ?  ?  ?  ?  ?
        A2 ?  X  ?  ?  ?  ?
        A3 ?  ?  X  ?  ?  ?
        B1 a  ?  b  X  ?  ?
        B2 c  ?  d  ?  X  ?
        B3 ?  ?  ?  ?  ?  X

        Haha we can infer the shape of the matrix from this.
 ```
 
## Bootloader

Just wait LOOP_TIMEOUT ms.
