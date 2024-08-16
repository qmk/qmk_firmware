# Handwired 20keyPad v1

![20KeyPad](https://i.imgur.com/wV9lJPd.jpeg)

A 20 Key (4x5) Macropad that could be reprogramed to suite your need, it has got 3 layars, an all the needed files are included (QMK files, 3D printables files, Buttons lables...). [More info on my github](https://github.com/smrini/QMK-20keyPad)

-   Keyboard Maintainer: [Said Mrini](https://github.com/smrini).
-   Personal Website: www.saidmrini.com

## Hardware Supported:

You can use the RP2040zero or any other microcontrollerfrom the same series (RP2040).
You cant use a PCB, because the space is a bit tight, So you will have to hand wire everything.

## Hardware Availability:

-   MicroController: [rp2040zero](https://es.aliexpress.com/item/1005006051130777.html?spm=a2g0o.order_list.order_list_main.5.1808194dhetDF1&gatewayAdapt=glo2esp)
-   Diodes:[1N4148](https://es.aliexpress.com/item/1005006127068810.html?spm=a2g0o.order_list.order_list_main.105.1808194dhetDF1&gatewayAdapt=glo2esp)
-   3D files: [Printables](https://www.printables.com/model/841830-qmk-20keymacropad)

### Make example for this keyboard (after setting up your build environment):

    make handwired/20keypad/v1:default

### Flashing example for this keyboard:

    make handwired/20keypad/v1:default:flash

### Attention:

    You can compile and use the code as it is as long as you are using the same microcontroller and the same pins used in the schematic.

    just download the files, open QMK MSYS and use this command: qmk flash -kb handwired/20keypad/v1 -km main
    You can modify the code and layers to whatever it suits you.

    if you desided to use a different pins, you mast change the PinOuts on the info.json file.
    if you desided to use a different MicroController, you mast change some related information on the info.json file.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Getting into bootloader:

-   **Physical reset button**: there are 2 buttons on the back of the PCB - press and hold the Boot button, don't leave it yet, press the reset button one time, after you leave it, remove your hand from the boot button.
-   **Keycode in layout**: Press and hold the 3rd key from left on the top row then press the last key on the same row. The LED will blink 3 times, then hold in red, till the flash is complete

## Useful Resources:

-   [keykodes list](https://docs.qmk.fm/#/keycodes)
-   [Matrix and hand wiring](https://docs.qmk.fm/#/hand_wire)
-   [more about info.json file](https://github.com/qmk/qmk_firmware/blob/master/docs/reference_info_json.md)
-   [More about the Keymap.c file](https://github.com/qmk/qmk_firmware/blob/master/docs/keymap.md)
-   [RGB Light](https://docs.qmk.fm/#/feature_rgblight)
-   [Command Line](https://github.com/qmk/qmk_firmware/blob/master/docs/cli_commands.md)
