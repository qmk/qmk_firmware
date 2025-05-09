# rm_fullsize

![rm_full](https://i.imgur.com/k61zEtah.jpg)

A fullsized keyboard with multiple layout options and a big knob.  The case is manchined out of 6061 Aluminum by Rucker Machine in the USA.

* Keyboard Maintainer: [Rucker Machine](https://github.com/RuckerMachine)
* Hardware Supported: RM Fullsized PCB, RP2040 controller
* Hardware Availability: [RM Fullsized](https://www.rmkeebs.com/product/rm-fullsized/)

Make example for this keyboard (after setting up your build environment):

    make rmkeebs/rm_fullsize:default

Flashing example for this keyboard:

    make rmkeebs/rm_fullsize:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Escape key) and plug in the keyboard
* **Physical reset button**: Hold down the button on the back of the PCB labeled BOOTLOADER, then press and hold the button labeled RESET for 3 seconds, then release both buttons. 
