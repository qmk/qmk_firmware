# Keychron C3 Pro

![Keychron C3 Pro](https://i.imgur.com/b4FTJsf.jpg)

A customizable 87% keyboard.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Keychron C3 Pro RGB
* Hardware Availability: [Keychron](https://www.keychron.com/)

Make example for this keyboard (after setting up your build environment):

    make keychron/c3_pro/ansi/rgb:default 

Flashing example for this keyboard:

    make keychron/c3_pro/ansi/rgb:default:flash

## bootloader

Enter the bootloader in two ways:

* **Bootmagic reset**: Hold down the key located at *K00*, commonly programmed as *Esc* while plugging in the keyboard.
* **Physical reset button**: Briefly press the RESET button under the spacebar.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## VIA

Choosing the VIA keymap will enable VIA and the layout json is [here](via_json/c3_pro_ansi_rgb.json).

## Considerations

This does not implement the Siri/Cortana key `KC_SIRI` or the Screenshot `KC_SNAP` key.

## Looking for C3 Pro Red?

Try Keychron's repository with red [here](https://github.com/Keychron/qmk_firmware/tree/playground/keyboards/keychron/c3_pro/).
