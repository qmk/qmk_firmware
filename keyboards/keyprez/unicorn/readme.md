# Unicorn

Unicorn is a split 65% keyboard with an extra column on the right side. 
It has support for optional hot swap sockets and a rotary encoder on the right side.

* Keyboard Maintainer: [Keyprez](https://github.com/keyprez)
* Hardware Supported: *Pro micro compatible controllers*
* Hardware Availability: *TBA*

Make example for this keyboard (after setting up your build environment):

    make keyprez/unicorn:default

Flashing example for this keyboard:

    make keyprez/unicorns:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the Enter key while holding down the right fn key
