# Steezy60

A 60% PCB with a ton of layout options for SMK and Alps switches

More info: https://geekhack.org/index.php?topic=103531.0

* Keyboard Maintainer: [4pplet](https://github.com/4pplet)
* Hardware Supported: Steezy60 Rev A and B
* Hardware Availability: https://4pplet.com/products/steezy60

Make example for this keyboard (after setting up your build environment):

    make 4pplet/steezy60/rev_a:default
    make 4pplet/steezy60/rev_b:default

Flashing example for this keyboard:

    make 4pplet/steezy60/rev_a:default:flash
    make 4pplet/steezy60/rev_b:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down Escape and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB or short the reset header
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
