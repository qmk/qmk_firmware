# WhirlwindFX ElementV2

![WhirlwindFX ElementV2](https://i.imgur.com/Etso6Ni.png)

A full-size (100%) mechanical keyboard with RGB lighting.

* Keyboard Maintainer: [Aedan Mills](https://github.com/aedanmills)
* Hardware Supported: WhirlwindFX ElementV2
* Hardware Availability: [WhirlwindFX](https://www.whirlwindfx.com/products/element)

Make example for this keyboard (after setting up your build environment):

    make whirlwind_fx_element:default

Flashing example for this keyboard:

    make whirlwind_fx_element:default:flash

## Bootloader

Enter the bootloader by pressing and holding the reset button on the back of the PCB while plugging in the keyboard. You will have to remove the key caps to access the screws to disassemble the keyboard and access the button.

Don't forget to backup the original firmware before proceeding by using the following dfu-util command with the keyboard in bootloader mode:

    dfu-util --list # Check that the keyboard is listed in DFU mode
    dfu-util -a 0 -U backup.bin -s 0x08000000 # Save backup as backup.bin

After flashing with QMK, BootMagic can be used to enter the bootloader by holding ESC while plugging in the keyboard.


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
