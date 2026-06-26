# YMDK CV11

![YMDK cv11](https://github.com/agordon/qmk-vial-ymdk-cv11/blob/master/photos/retail-photo.jpg)

*Cheap and awesome 11 keys keypad, commonly called "CV11".
It has 10 keys + 1 Rotary Encoder, and 11 RGB LEDs.*

* Keyboard Maintainer: QMK Community
* Hardware Supported: STM32F103CTB6 - See [here](https://github.com/agordon/qmk-vial-ymdk-cv11) for lots of hardware/software details.
* Hardware Availability: Search for "CV11" on most retail websites ( [YMDK](https://ymdkey.com/products/cv11-11-key-mini-mechanical-keyboard-wired-hot-swap-rgb-knob-pla-3d-printed-case-supports-vial-macro-for-gaming-office?) [AMAZON](https://www.amazon.ca/YMDK-CV11-Mini-Mechanical-Keyboard/dp/B0FH2F2WH8/) [AliExpress](https://www.aliexpress.com/item/1005009409867322.html) ).

## Build

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb ymdk/cv11 -km default

This will create `ymdk_cv11_default.uf2` file.

1. Press and hold the rotary encoder button, and plug the USB keybapd
2. This will boot then keypad into DFU/Bootloader mode.
3. A USB Mass Storage "drive" named `MT.KEY` will appear
4. Copy the new `UF2` to this drive.
5. Replug the USB Keypad - it will boot the new QMK firmware.

> **NOTE:** You can absolutely brick this keyboard if you upload a wrong/buggy
> UF2 firmware. Use at your own risk.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools)
and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide)
for more information. Brand new to QMK? Start with our [Complete Newbs
Guide](https://docs.qmk.fm/#/newbs).

## Midi Keypad

This keypad can be easily made into MIDI keypad (e.g. for QLAB control,
as a cheap open-source alternative to [Go Box Prime](https://www.teamsound.nyc/store/gbp)).

Build with:

    qmk compile -kb ymdk/cv11 -km midi

This will create `ymdk_cv11_midi.uf2` file. Upload it with the same method
explained above.

## Bootloader

There is only *one* way to enter the DFU/Bootloader mode:

* **Bootmagic reset**: Press and hold down the Rotary Encoder button and plug in the keyboard.

You can change the keymap to assign a `QK_BOOT` to one of the keys
as an additional way to enter the bootloader (default keymaps does not have
such key assigned).

There is **no** physical button to enter dfu/bootloader mode (only one physical
RST button on the PCB. Hence - if you use wrong/buggy firmware, you will be
locked out of the DFU/Bootloader - effectively bricking your device unless
you have additional hardware (ST-Link programmer).

See [here](https://github.com/agordon/qmk-vial-ymdk-cv11#bootloader) to learn
more technical details about the bootloader, and
[here](https://github.com/agordon/qmk-vial-ymdk-cv11#troubleshooting) for
unbricking methods (which require special hardware).
