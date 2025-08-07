# Le Chiffre

![Le Chiffre](https://i.imgur.com/X1WsUmdh.png)

Le Chiffre (ironically, "the number" in French) is a 30% keyboard designed by tominabox1.  The purpose of the board is to provide an ergonomic platform supporting MX, Choc and Alps—for when one's wrists need a break.

As open source hardware, various revisions of the board exist. The original supports a run-of-the-mill .91" I2C OLED, EC11 rotary encoder and WS2812 RGB LED strip. Most versions also feature SMD footprints for underglow and indicator RGB LEDs.

Firmware support for several incompatible PCBs can be found in this repository. Examine your PCB to determine which firmware it uses before flashing.
* Rev 1 (atmega32u4, atmel-dfu)
  * The original.
* Rev 2 (atmega32u4, atmel-dfu)
  * Widely known as the "curly traces" version; notably sold by [P3D](https://p3dstore.com) with the Le Chiffre Plus case. (P3D's store page referred to this PCB version as "Rev 3".)
* HE (atmega32u4, atmel-dfu)
  * Created and sold by [Checker Boards](https://checkerboards.xyz). Uses MX hotswap sockets. No Choc or Alps support.
 
* Keyboard Maintainer: [TJ Campie](https://github.com/tominabox1)
* Hardware Supported: [Le Chiffre](https://github.com/tominabox1/Le-Chiffre-Keyboard), [Le Chiffre HE](https://github.com/npspears/Le-Chiffre_HE)
* Hardware Availability: Open source; PCBs are sometimes stocked by various keyboard vendors. Bring your own case.

Make example for this keyboard (after setting up your build environment):

    make tominabox1/le_chiffre/rev1:default
    make tominabox1/le_chiffre/rev2:default
    make tominabox1/le_chiffre/he:default

Flashing example for this keyboard:

    make tominabox1/le_chiffre/rev1:default:flash
    make tominabox1/le_chiffre/rev2:default:flash
    make tominabox1/le_chiffre/he:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard. This will also clear EEPROM, so it is a good first step if the keyboard is misbehaving.
* **Physical reset**: Press the central button on the underside of the PCB.
* **Keycode in layout**: There is no key mapped to `QK_BOOT` in the pre-created keymaps, but you may assign this key in any keymaps you create.

## Flashing

After entering the bootloader through one of the three methods above, the keyboard will appear as an Atmel DFU device. It can be flashed using the QMK CLI or QMK Toolbox.
