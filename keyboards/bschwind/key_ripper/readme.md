# key_ripper

A 75-key keyboard which has a similar layout to a MacBook keyboard, and sacrifices
the right shift key to keep a compact size. Based on the RP2040 microcontroller.

![key_ripper](https://imgur.com/pL26kVSh.png)
![key_ripper](https://imgur.com/FnvZREyh.png)
![key_ripper](https://imgur.com/xe8wImMh.png)

* Keyboard Maintainer: [Brian Schwind](https://github.com/bschwind)
* Hardware Supported: The key-ripper PCB
* Hardware Availability: You can find production files in the [releases](https://github.com/bschwind/key-ripper/releases) page used for ordering from JLCPCB.

Make example for this keyboard (after setting up your build environment):

    make bschwind/key_ripper:default

Flashing example for this keyboard:

    make bschwind/key_ripper:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the Escape key and plug in the keyboard
* **Physical reset button**: Hold down the USB BOOT button on the PCB, and briefly press the RESET button on the PCB.
