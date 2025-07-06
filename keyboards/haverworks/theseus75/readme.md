# Haverworks Theseus75

![Theseus75 v1 PCB](https://imgur.com/N81LsCO.png)

The Theseus75 is a 75% row-staggered split keyboard with a macro column and rotary encoders on both sides. Each half features a dual-role USB-C port and integrated USB hub, allowing the unused port to act as a USB-C 2.0 High-Speed host for connecting a numpad, mouse, flash drive, security key, mobile phone, or similar device.

> [!NOTE]
> Up to 5V at 1.5A can be supplied, depending on negotiations with the host.

* Keyboard Maintainers: [Moritz Plattner](https://github.com/ebastler), [Alex Havermale](https://github.com/haversnail)
* Hardware Supported: Haverworks Theseus75 v1 PCBs (hot-swap and solder)
* Hardware Availability: [Group buy](https://haver.works/theseus75)

Make example for this keyboard (after setting up your build environment):

    make haverworks/theseus75:default

Flashing example for this keyboard:

    make haverworks/theseus75:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in two ways:

* **Physical reset button**: Hold the <kbd>Reset</kbd>/<kbd>Flash</kbd> button on the back of the PCB for approximately one second (instructions are also included on the PCB)
* **Bootmagic reset**:
    * **Left half**: Hold down the first key to the right of the encoder (<kbd>Esc</kbd> by default) and plug in the keyboard
    * **Right half**: Hold down the first key to the left of the encoder (<kbd>Print Screen</kbd> by default) and plug in the keyboard
