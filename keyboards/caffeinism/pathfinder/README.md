# Pathfinder the keyboard matrix finder

Pathfinder is a general-purpose keyboard matrix reverse engineering tool and itself qmk keyboard firmware.

A multimeter is usually used to determine the matrix of the keyboard. But there are people who don't want to get intimate with PCBs. (That's me!) This code is the firmware to figure out the matrix of the keyboard, which is not normally registered in QMK.

This is an easy process in a few steps.

1. Select the appropriate MCU and BOOTLOADER from rules.mk.
2. In config.h, enter the appropriate pin list you want to test. Unfortunately, qmk only supports up to 32 pins.
3. Specify the appropriate LOOP_TIMEOUT in config.h. The keyboard runs the main loop and returns to the bootloader after this time. Prevents your keyboard from becoming a brick!
4. Do ```qmk compile -kb caffeinism/pathfinder -km default``` and ```qmk flash -kb caffeinism/pathfinder -km default```.
5. After running ```qmk console```, connect the keyboard, there may be some keys that blink by default. In this case, remove those pins from MATRIX_ALL_PINS.
![blink](https://i.imgur.com/WzTPGI2.png)
![target](https://i.imgur.com/5GH7Wur.png)
![delete](https://i.imgur.com/EySItgD.png)
7. Run again ```qmk compile -kb caffeinism/pathfinder -km default```, ```qmk flash -kb caffeinism/pathfinder -km default``` and ```qmk console```.
8. And press the key! You can easily find your matrix.
![result](https://i.imgur.com/LOhpZiB.png)

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
