S65-x keyboard firmware
======================
DIY 65% keyboard from Sentraq.

## S65X Resources
- [Sentraq page](https://sentraq.com/collections/group-buys/products/gb-s65-x-rgb-diy-kit?variant=39246723914)

## Flashing your keyboard
The recommended programs for flashing your keyboard are [Atmel FLIP](http://www.atmel.com/tools/FLIP.aspx) (Windows) and [dfu-programmer](http://dfu-programmer.sourceforge.net/) (Linux/Windows).

[QMK Firmware Flasher](https://github.com/qmk/qmk_firmware_flasher/releases) may work, as the S65-X keyboard uses the ATMega32U4 microcontroller, but it is untested. Use at your own risk.

**Programming the firmware (Windows)**

1. download and install FLIP (http://www.atmel.com/tools/FLIP.aspx)
2. connect the keyboard, press the program button on the underside of the board (S1) and wait until it enumerates (you'll hear the "disconnect" and "connect" sound)
3. go to device manager, find the atmega32u4 chip and click "update driver"
4. choose location manually: folder named "usb" inside the installation directory of FLIP
5. once the driver is installed, run flip
6. Device -> Select: choose ATMega32U4
7. Settings -> Communication -> USB, FLIP should show the signature at this point (58 1E 95 87)
8. File -> Load HEX file: choose the hex firmware: <firmware>.hex
9. click "Run"
10. after programming is done, disconnect the device from USB and connect again.


**Programming the firmware (Linux/Mac)**

1. Download and install/compile/unpack dfu-programmer from http://dfu-programmer.sourceforge.net/.
2. Issue the following commands in the command prompt after connecting the device and pressing the programming button (S1). You may need root permissions or udev rules to do that.
  1. `sudo dfu-programmer atmega32u4 erase`
  2. `sudo dfu-programmer atmega32u4 flash <firmware>.hex`
  3. `sudo dfu-programmer atmega32u4 start`
3. The keyboard should start working. If it doesn't, reconnect the cable.

## Building the firmware

To build the firmware binary hex file with a keymap just do `make` with a keymap like this:

    $ make default

For a more detailed explanation of the build process and the environment setup, see the ["Getting Started" section](/readme.md#getting-started).

## Keymaps

Currently only an ANSI keymap is provided, hopefully others will contribute theirs.

### 0  Initial explanations
The █████ blocks on the layouts hides the switch positions that do not exist physically on the PCB. If you feel like hacking the keyboard and adding new keys, those are the positions that can be used. You'll have to modify the [keymap_common.h](keymap_common.h) file for that.

The ▒▒▒▒▒ blocks hides switch positions not used on this particular layout, but they do exist on the PCB.


### 1  [Standard - ANSI (default layout)](keymaps/default/keymap.c)

#### 1.0 Default layer
    ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
    │ ESC │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  -  │  =  │▒▒▒▒▒│BKSPC│DEL  │
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │ TAB │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │  [  │  ]  │  \  │▒▒▒▒▒│END  │
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │CAPSL│  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │  ;  │  '  │▒▒▒▒▒│ENTER│▒▒▒▒▒│PG_UP│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │LSHFT│▒▒▒▒▒│  Z  │  X  │  C  │  V  │  B  │  N  │  M  │  ,  │  .  │  /  │▒▒▒▒▒│RSHFT│ UP  │PG_DN│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │LCTRL│L_ALT│L_GUI│█████│█████│█████│ SPC │█████│█████│█████│R_ALT│ FN0 │ APP │LEFT │DOWN │RIGHT│
    └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
#### 1.1 Fn layer
    ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
    │GRAVE│ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │▒▒▒▒▒│▒▒▒▒▒│     │
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │     │ _AL │ Up  │     │     │     │     │     │PGUP │PGDWN│PRTSC│SCLCK│PAUSE│     │▒▒▒▒▒│     │
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │     │Left │Down │Right│     │     │Left │Down │ Up  │Right│     │     │▒▒▒▒▒│     │▒▒▒▒▒│     │
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │     │▒▒▒▒▒│_UL  │     │     │     │     │     │     │Home │ End │     │▒▒▒▒▒│Vol+ │▒▒▒▒▒│     │
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │     │     │     │█████│█████│█████│     │█████│█████│█████│     │     │Mute │Vol- │Play │     │
    └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘

