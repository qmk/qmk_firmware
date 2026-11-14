# MonacoKeys MK65MX

65% MX keyboard from [MonacoKeys](https://monacokeys.de) by [quark-works](https://github.com/quark-works)

![monacokeys/mk65mx](https://i.imgur.com/QTEHzNi.png)

* Keyboard Maintainer: [MonacoKeys](https://github.com/monacokeys)
* Hardware Supported: MK65MX (RP2040)
* Hardware Availability: [MonacoKeys](https://monacokeys.de/en/products/mk65mx-65-mechanical-keyboard-pcb)

Make example for this keyboard (after setting up your build environment):

    make monacokeys/mk65mx:default

Flashing example for this keyboard:

    make monacokeys/mk65mx:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard. This also clears the EEPROM.
* **Boot button**: Hold the BOOT button on the PCB while plugging in the keyboard. There's no reset button.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` (Fn+Right in the default keymap)
