# Littlefoot LX

![littlefoot_lx](https://i.imgur.com/0WhgT5yh.jpeg)

The Littlefoot LX is a premium, integrated pcb version of the Littlefoot by The_Royal. 

* Keyboard Maintainer: [tominabox1](https://github.com/tominabox1)
* Hardware Supported: Littlefoot LX integrated ATMega32u4
* Hardware Availability: https://tachfactory.bigcartel.com

There are two versions of this PCB:
    Rev1 is the PCB that shipped with the group buy run by RPMorrison on Tach Factory. These PCBs can be identified by the bodge wire on column 4.
    Rev2 is the PCB available after this group buy.

Make example for this keyboard (after setting up your build environment):

    make tominabox1/littlefoot_lx:default

Flashing example for this keyboard:

    make tominabox1/littlefoot_lx:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
