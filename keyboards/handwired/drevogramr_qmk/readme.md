# Drevo Gramr QMK

![Drevo Gramr 84](https://i.imgur.com/SeMa7B5.jpg)

Drevo Gramr 84 rewired with Arduino (Pro) Micro. Firmware utilizes onboard 74HC595 shift registers for key matrix scanning and onboard LEDs for backlighting. Rewiring schematics can be found [here](https://imgur.com/a/eKutsbr), original keyboard controller should be removed from PCB. Schematics of stock board is [here](https://imgur.com/a/vPOPcIC).

* Keyboard Maintainer: [MAD](https://github.com/wwwMADwww)
* Hardware Supported: ATMega32U4, Drevo Gramr 84 with PCB labeled as `TB-ZT-S84LED-01-V03 2015-06-12`.
* Hardware Availability: AliExpress, Amazon

## Bootloader

Enter the bootloader in 3 ways:

* **Physical reset button**: On the Arduino board either briefly press the Reset button or short Reset pin to ground.
* **Keycode in layout**: Press the key mapped to `RESET` if it is available.
* **Key combination**: Press `Left Shift` + `Right Shift` + `B`.

## Build and flash

Make example for this keyboard (after setting up your build environment):

    make drevogramr_qmk:default

Flashing example for this keyboard:

    make drevogramr_qmk:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
